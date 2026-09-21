class Connection:
    def __init__(self, zones: tuple[str, str], max_link_capacity: int = 1):
        self.zones = zones
        self.max_link_capacity = max_link_capacity
        self.occupants: set[int] = set()
