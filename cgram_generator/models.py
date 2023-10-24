from pydantic import BaseModel


class CGramCType(BaseModel):
    name: str
    pointer_deepness: int = 0
    cgram_type: bool


class CGramField(BaseModel):
    name: str
    type: CGramCType


class CGramType(BaseModel):
    name: str
    dependencies: list[str]
    fields: list[CGramField]


class CGramAPI(BaseModel):
    version: str
    release_date: str
    changelog: str
    types: list[CGramType]
