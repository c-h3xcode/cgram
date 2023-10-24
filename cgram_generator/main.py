import argparse
import json
import os


from cgram_generator.parser import parse_api
from cgram_generator.generator import generate_cgram_types, generate_types_file


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("input", type=str, help="Input file")
    parser.add_argument("output_dir", type=str, help="Output directory")

    args = parser.parse_args(argv)

    with open(args.input, "r") as f:
        data = json.load(f)

    api = parse_api(data)

    if not os.path.exists(os.path.join(args.output_dir, "types")):
        os.makedirs(os.path.join(args.output_dir, "types"))

    for type_name, source in generate_cgram_types(api).items():
        with open(os.path.join(args.output_dir, "types", f"{type_name}.h"), "w") as f:
            f.write(source)

    with open(os.path.join(args.output_dir, "types.h"), "w") as f:
        f.write(generate_types_file(api))

    return 0
