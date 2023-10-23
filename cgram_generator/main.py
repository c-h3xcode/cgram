import sys
import argparse
import json

from cgram_generator import models


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("input", type=str, help="Input file")

    args = parser.parse_args(argv)

    with open(args.input, "r") as f:
        data = json.load(f)

    