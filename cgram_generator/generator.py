import jinja2

from cgram_generator import models

# load template from type.h.jinja2 file
environment = jinja2.Environment(
  loader=jinja2.FileSystemLoader("templates"),
  autoescape=True,
  keep_trailing_newline=True
)
type_template = environment.get_template("type.h.jinja2")
types_file_template = environment.get_template("types.h.jinja2")


def generate_cgram_type(type: models.CGramType, api: models.CGramAPI) -> str:
    return type_template.render(type=type, api=api)


def generate_cgram_types(api: models.CGramAPI) -> dict[str, str]:
    return {type.name: generate_cgram_type(type, api) for type in api.types}


def generate_types_file(api: models.CGramAPI) -> str:
    return types_file_template.render(api=api)
