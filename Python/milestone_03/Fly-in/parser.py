from zone import NormalZone, PriorityZone, RestrictedZone, BlockedZone
from connection import Connection
from network import Network
import re
from exceptions import ParseError


def parser(filepath: str) -> Network:
    with open(filepath) as f:
        first_line = f.readline()
        drones = first_line.split(":", 1)
        if len(drones) != 2 or drones[0].strip() != "nb_drones":
            raise ParseError(1, "First line format must be: 'nb_drones: int'")
        try:
            drone_nb = int(drones[1].strip())
            if drone_nb <= 0:
                raise ValueError
        except ValueError:
            raise ParseError(1, "nb_drones must be a positive integer")
        my_network = Network(drone_nb)
        handlers = {
            "start_hub": lambda nb, value, network: parse_hub_line(
                nb, "start_hub", value, network
            ),
            "end_hub": lambda nb, value, network: parse_hub_line(
                nb, "end_hub", value, network
            ),
            "hub": lambda nb, value, network: parse_hub_line(
                nb, "hub", value, network
            ),
            "connection": parse_connection_line,
        }
        for nb, line in enumerate(f, start=2):
            clean_line = line.strip()
            if clean_line.startswith("#") or not clean_line:
                continue
            key, value = clean_line.split(":", 1)
            key, value = key.strip(), value.strip()
            if key not in handlers:
                raise ParseError(nb, f"Invalid key: {key}")
            handlers[key](nb, value, my_network)
    if my_network.start is None or my_network.end is None:
        raise ParseError(0, "Start or end hub missing")
    return my_network


def parse_hub_line(line: int, key: str, value: str, network: Network) -> None:
    parts = value.split("[")
    try:
        hub, x, y = parts[0].split()
    except ValueError:
        raise ParseError(line, "Zone line must have format 'name x y'")
    try:
        x, y = int(x), int(y)
    except ValueError:
        raise ParseError(line, "Zone coordinates must be integers")
    zone_classes = {
        "normal": NormalZone,
        "restricted": RestrictedZone,
        "priority": PriorityZone,
        "blocked": BlockedZone,
    }
    allowed_keys = ["zone", "color", "max_drones"]
    zone_type = "normal"
    color = None
    max_drones = 1
    if len(parts) == 2:
        pairs = re.findall(r"(\w+)=(-?\w+)", parts[1])
        metadata = dict(pairs)
        pairs_len = sum(len(k) + len(v) for k, v in pairs)
        new_part = parts[1].replace("=", "").replace(" ", "").replace("]", "")
        if pairs_len != len(new_part):
            raise ParseError(line, "only 'str=str' format allowed")
        for meta_key in metadata.keys():
            if meta_key not in allowed_keys:
                raise ParseError(line, f"Key '{meta_key}' not valid")
        zone_type = metadata.get("zone", zone_type)
        if zone_type not in zone_classes.keys():
            raise ParseError(line, f"Invalid value '{zone_type}' for zone type")
        color = metadata.get("color", color)
        try:
            max_drones = int(metadata.get("max_drones", max_drones))
            if max_drones <= 0:
                raise ValueError
        except ValueError:
            raise ParseError(line, "max_drones only accepts positive integers")
    new_zone = zone_classes[zone_type](hub, x, y, color, max_drones)
    network.add_zone(new_zone, line)
    if key == "start_hub":
        network.start = hub
    elif key == "end_hub":
        network.end = hub


def parse_connection_line(line: int, value: str, network: Network) -> None:
    parts = value.split("[")
    zone_pairs = re.findall(r"(\w+)-(\w+)", value)
    if zone_pairs:
        pairs_sum = len(zone_pairs[0][0]) + len(zone_pairs[0][1])
    # short-circuit: if the first condition is True the second one is ignored, if we revert the conditions' order it would raise a NameError.
    if len(zone_pairs) != 1 or pairs_sum != len(parts[0].replace("-", "").strip()):
        raise ParseError(line, "A connection must have a single 'zone-zone' format")
    max_link = 1
    if len(parts) == 2:
        metadata = re.findall(r"(\w+)=(-?\w+)", parts[1])
        if metadata:
            meta_len = len(metadata[0][0]) + len(metadata[0][1])
            parts_len = len(parts[1].replace("=", "").replace(" ", "").replace("]", ""))
        if len(metadata) != 1 or metadata[0][0] != "max_link_capacity" or meta_len != parts_len:
            raise ParseError(line, "max_link must have a single 'max_link_capacity=int' format")
        try:
            max_link = int(metadata[0][1])
            if max_link <= 0:
                raise ValueError
        except ValueError:
            raise ParseError(line, "max_link only accepts positive integers")
    if zone_pairs[0][0] not in network.zones or zone_pairs[0][1] not in network.zones:
        raise ParseError(line, "One or both given zones don't exist")
    connection = Connection(zone_pairs[0], max_link)
    network.add_connection(connection, line)
