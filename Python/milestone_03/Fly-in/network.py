from zone import Zone
from connection import Connection
from exceptions import ParseError

class Network:
    def __init__(self, nb_drones: int):
        self.nb_drones = nb_drones
        self.zones: dict[str, Zone] = {}
        self.start = None
        self.end = None
        self.connections: dict[str, list[Connection]] = {}

    def add_zone(self, zone: Zone, line: int) -> None:
        if zone.name in self.zones:
            raise ParseError(line, "Zone duplicated")
        self.zones[zone.name] = zone

    def add_connection(self, connection: Connection, line: int) -> None:
        for item in self.connections.get(connection.zones[0], []):
            if set(item.zones) == set(connection.zones):
                raise ParseError(line, "Connection already exists")
        self.connections.setdefault(connection.zones[0], []).append(connection)
        self.connections.setdefault(connection.zones[1], []).append(connection)
