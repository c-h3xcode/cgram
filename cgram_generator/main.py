import argparse
import json
import os
import logging
from importlib.metadata import version
import coloredlogs  # type: ignore

from cgram_generator.parser import parse_api
from cgram_generator.generator import (
    generate_cgram_types,
    generate_types_file,
    generate_cgram_parsers,
)
from cgram_generator.checker import check_dependencies

logger = logging.getLogger(__name__)


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("input", type=str, help="Input file")
    parser.add_argument("headers_dir", type=str, help="Output directory for headers")
    parser.add_argument("parsers_dir", type=str, help="Output directory for parsers")
    parser.add_argument("--log-level", type=str, default="INFO", help="Log level")
    parser.add_argument(
        "--skip-headers", action="store_true", help="Skip headers generation"
    )
    parser.add_argument(
        "--skip-parsers", action="store_true", help="Skip parsers generation"
    )
    args = parser.parse_args(argv)

    coloredlogs.install(level=args.log_level)  # type: ignore

    logger.info("Running cgram-generator version %s", version("cgram_generator"))

    with open(args.input, "r") as f:
        logger.info("Reading input file %s", args.input)
        data = json.load(f)

    logger.info("Parsing API spec")
    api = parse_api(data)

    logger.info("Checking dependencies")
    check_dependencies(api)

    if not args.skip_headers:
        logger.info("Generating headers")
        if not os.path.exists(os.path.join(args.headers_dir, "types")):
            os.makedirs(os.path.join(args.headers_dir, "types"))

        for type_name, source in generate_cgram_types(api).items():
            with open(
                os.path.join(args.headers_dir, "types", f"{type_name}.h"), "w"
            ) as f:
                logger.debug("Writing type '%s' to file %s", type_name, f.name)
                f.write(source)

        with open(os.path.join(args.headers_dir, "types.h"), "w") as f:
            logger.debug("Writing types.h to file %s", f.name)
            f.write(generate_types_file(api))
    else:
        logger.warning("Skipping headers generation")

    if not args.skip_parsers:
        logger.info("Generating parsers")
        parsers = generate_cgram_parsers(api)

        if not os.path.exists(args.parsers_dir):
            os.makedirs(args.parsers_dir)

        for type_name, source in parsers.items():
            with open(os.path.join(args.parsers_dir, f"{type_name}.c"), "w") as f:
                logger.debug("Writing parser '%s' to file %s", type_name, f.name)
                f.write(source)
    else:
        logger.warning("Skipping parsers generation")

    logger.info("Done")

    return 0
