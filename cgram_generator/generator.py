from logging import getLogger

import jinja2

from cgram_generator import models

ctype = models.CGramCType

logger = getLogger(__name__)

environment = jinja2.Environment(
    loader=jinja2.FileSystemLoader("templates"),
    autoescape=True,
    keep_trailing_newline=True,
    trim_blocks=True,
    lstrip_blocks=True,
)
type_template = environment.get_template("type.h.jinja2")
types_file_template = environment.get_template("types.h.jinja2")
parser_template = environment.get_template("parser.c.jinja2")

TYPES_TO_PARSER_FUNCTIONS: dict[ctype, str] = {
    ctype(name="int64_t"): "_cgram_parse_int",  # type: ignore
    ctype(name="int64_t", pointer_deepness=1): "_cgram_parse_int_array",  # type: ignore
    ctype(name="double"): "_cgram_parse_double",  # type: ignore
    ctype(name="char", pointer_deepness=1): "_cgram_parse_string",  # type: ignore
    ctype(name="char", pointer_deepness=2): "_cgram_parse_string_array",  # type: ignore
    ctype(name="bool"): "_cgram_parse_bool",  # type: ignore
}


def generate_cgram_type(type: models.CGramType, api: models.CGramAPI) -> str:
    return type_template.render(type=type, api=api)


def generate_cgram_types(api: models.CGramAPI) -> dict[str, str]:
    generated = {type.name: generate_cgram_type(type, api) for type in api.types}
    logger.info("Generated %d types", len(generated))
    return generated


def generate_types_file(api: models.CGramAPI) -> str:
    return types_file_template.render(api=api)


def generate_cgram_parser(type: models.CGramType, api: models.CGramAPI) -> str:
    logger.debug("Generating parser for type '%s'", type.name)
    fields: list[models.CGramParserField] = []

    for field in type.fields:
        logger.debug("Processing field '%s'", field.name)
        parser_function = TYPES_TO_PARSER_FUNCTIONS.get(field.type, "")
        if not parser_function:
            if not field.type.cgram_type:
                raise ValueError(f"Cannot find parser function for type '{field.type}'")
        fields.append(
            models.CGramParserField(
                name=field.name,
                type=field.type,
                parser_function=parser_function,
                required=field.required,
            )
        )
    parser_type = models.CGramParserType(
        name=type.name,
        dependencies=type.dependencies,
        fields=fields,
    )

    return parser_template.render(type=parser_type, api=api)


def generate_cgram_parsers(api: models.CGramAPI) -> dict[str, str]:
    generated = {type.name: generate_cgram_parser(type, api) for type in api.types}
    logger.info("Generated %d parsers", len(generated))
    return generated
