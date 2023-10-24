from typing import Any

from cgram_generator import models

ctype = models.CGramCType

TYPES_TO_CTYPES = {
    "Integer": ctype(name="int64_t", pointer_deepness=0, cgram_type=False),
    "Float": ctype(name="double", pointer_deepness=0, cgram_type=False),
    "Boolean": ctype(name="bool", pointer_deepness=0, cgram_type=False),
    "String": ctype(name="char", pointer_deepness=1, cgram_type=False),
}


def convert_type_to_ctype(type: str) -> ctype:
    if type.startswith("Array of "):
        print("Detected array type", type)
        name = type[len("Array of "):]
        actual_type = convert_type_to_ctype(name).model_copy()
        actual_type.pointer_deepness += 1
        return actual_type

    if type in TYPES_TO_CTYPES:
        print("Detected default type", type)
        return TYPES_TO_CTYPES[type]

    print("Detected custom type", type)
    return ctype(name=type, pointer_deepness=1, cgram_type=True)


def parse_api(api_spec: dict[str, Any]) -> models.CGramAPI:
    types: list[models.CGramType] = []

    for type_name, type_dict in api_spec.get("types", {}).items():
        fields: list[models.CGramField] = []
        dependencies: list[str] = []

        print("Processing type", type_name)
        for field in type_dict.get("fields", []):
            field_name = field["name"]
            field_type = convert_type_to_ctype(field["types"][0])

            if field_type.cgram_type:
                if field_type.name not in dependencies and field_type.name != type_name:
                    dependencies.append(field_type.name)

            fields.append(models.CGramField(name=field_name, type=field_type))

        types.append(models.CGramType(
            name=type_name, dependencies=dependencies, fields=fields
        ))

    return models.CGramAPI(
        version=api_spec["version"],
        release_date=api_spec["release_date"],
        changelog=api_spec["changelog"],
        types=types,
    )
