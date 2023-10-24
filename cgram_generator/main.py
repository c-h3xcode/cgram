import argparse
import json
import os
import logging
from importlib.metadata import version
import coloredlogs  # type: ignore

from cgram_generator.parser import parse_api
from cgram_generator.generator import generate_cgram_types, generate_types_file
from cgram_generator.checker import check_dependencies

logger = logging.getLogger(__name__)


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("input", type=str, help="Input file")
    parser.add_argument("output_dir", type=str, help="Output directory")
    parser.add_argument("--log-level", type=str, default="INFO", help="Log level")
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

    logger.info("Generating types")
    if not os.path.exists(os.path.join(args.output_dir, "types")):
        os.makedirs(os.path.join(args.output_dir, "types"))

    for type_name, source in generate_cgram_types(api).items():
        with open(os.path.join(args.output_dir, "types", f"{type_name}.h"), "w") as f:
            logger.debug("Writing type '%s' to file %s", type_name, f.name)
            f.write(source)

    with open(os.path.join(args.output_dir, "types.h"), "w") as f:
        logger.debug("Writing types.h to file %s", f.name)
        f.write(generate_types_file(api))

    logger.info("Done")

    return 0
