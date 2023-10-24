class UnknownDependencyError(Exception):
    """Raised when a dependency is not found in the dependency graph."""

    def __init__(self, type_name: str, dependency: str):
        self.type_name = type_name
        self.dependency = dependency

        super().__init__(f"Type '{type_name}' depends on unknown type '{dependency}'")
