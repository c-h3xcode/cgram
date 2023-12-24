from pydantic import BaseModel


class HashableModel(BaseModel):
    def __hash__(self: "HashableModel") -> int:
        return hash((type(self),) + tuple(self.__dict__.values()))


class CGramCType(HashableModel):
    name: str
    pointer_deepness: int = 0
    cgram_type: bool = False


class CGramField(HashableModel):
    name: str
    type: CGramCType
    required: bool


class CGramType(HashableModel):
    name: str
    dependencies: list[str]
    fields: list[CGramField]


class CGramMethod(HashableModel):
    name: str
    dependencies: list[str]
    returns: CGramCType
    fields: list[CGramField]


class CGramAPI(HashableModel):
    version: str
    release_date: str
    changelog: str
    types: list[CGramType]
    methods: list[CGramMethod]


# -- Parser --


class CGramParserField(HashableModel):
    name: str
    type: CGramCType
    parser_function: str
    to_json_function: str
    required: bool


class CGramParserType(HashableModel):
    name: str
    dependencies: list[str]
    fields: list[CGramParserField]
