from pydantic import BaseModel


class CGramField(BaseModel):
    name: str
    type: str
    is_ctype: bool
    is_pointer: bool


class CGramType(BaseModel):
    name: str
    dependencies: list[str]
    fields: list[CGramField]
