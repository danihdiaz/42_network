from zone import Zone, NormalZone, PriorityZone, RestrictedZone, BlockedZone
from connection import Connection
from network import Network
import re
from exceptions import ParseError


def parser(filepath: str) -> Network:
    try:
        f = open(filepath)
    except FileNotFoundError:
        raise ParseError(0, "File doesn't exist")
    except PermissionError:
        raise ParseError(0, "Permission denied for this file")
    except IsADirectoryError:
        raise ParseError(0, "This is a directory, not a file")
    with f:
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
            try:
                key, value = clean_line.split(":", 1)
            except ValueError:
                raise ParseError(
                    nb, "Bad syntax: format must be 'str: something'")
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
    if "-" in hub:
        raise ParseError(
            line, "Hyphen character '-' and spaces not allowed in zone names")
    try:
        int_x, int_y = int(x), int(y)
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
    if len(parts) not in (1, 2):
        raise ParseError(line, "Only 1 block of metadata allowed")
    if len(parts) == 2:
        metadata = extract_metadata(line, parts[1])
        for meta_key in metadata.keys():
            if meta_key not in allowed_keys:
                raise ParseError(line, f"Key '{meta_key}' not valid")
        zone_type = metadata.get("zone", zone_type)
        if zone_type not in zone_classes.keys():
            raise ParseError(
                line, f"Invalid value '{zone_type}' for zone type")
        color = metadata.get("color", color)
        try:
            max_drones = int(metadata.get("max_drones", max_drones))
            if max_drones <= 0 and key != "start_hub" and key != "end_hub":
                raise ValueError
        except ValueError:
            raise ParseError(line, "max_drones only accepts positive integers")
    if key == "start_hub":
        if network.start is not None:
            raise ParseError(line, "'start_hub' already defined")
        new_zone: Zone = NormalZone(hub, int_x, int_y, color,
                                    network.nb_drones)
        network.add_zone(new_zone, line)
        network.start = hub
    elif key == "end_hub":
        if network.end is not None:
            raise ParseError(line, "'end_hub' already defined")
        if zone_type == "blocked":
            raise ParseError(
                line, "end_hub can't be blocked, for obvious reasons")
        new_zone = zone_classes[zone_type](
            hub, int_x, int_y, color, network.nb_drones)
        network.add_zone(new_zone, line)
        network.end = hub
    else:
        new_zone = zone_classes[zone_type](
            hub, int_x, int_y, color, max_drones)
        network.add_zone(new_zone, line)


def parse_connection_line(line: int, value: str, network: Network) -> None:
    parts = value.split("[")
    zone_pairs = parts[0].strip().split("-")
    if len(zone_pairs) != 2:
        raise ParseError(
            line, "A connection must have a single 'zone-zone' format")
    max_link = 1
    if len(parts) not in (1, 2):
        raise ParseError(line, "Only 1 block of metadata allowed")
    if len(parts) == 2:
        metadata = extract_metadata(line, parts[1])
        if len(metadata) > 1:
            raise ParseError(
                line, "max_link_capacity must have a single "
                "'max_link_capacity=int' format"
            )
        if len(metadata) == 1 and "max_link_capacity" not in metadata.keys():
            raise ParseError(
                line, "Only max_link_capacity allowed for connections")
        if metadata:
            try:
                max_link = int(metadata["max_link_capacity"])
                if max_link <= 0:
                    raise ValueError
            except ValueError:
                raise ParseError(
                    line, "max_link only accepts positive integers")
    if (zone_pairs[0] not in network.zones
            or zone_pairs[1] not in network.zones):
        raise ParseError(line, "One or both given zones don't exist")
    connection = Connection((zone_pairs[0], zone_pairs[1]), max_link)
    network.add_connection(connection, line)


def extract_metadata(line: int, metadata: str) -> dict[str, str]:
    if "]" not in metadata:
        raise ParseError(line, "Closing bracket ']' missing")
    if "]" in metadata:
        if metadata.count("]") > 1:
            raise ParseError(line, "Too many closing brackets ']'")
        if not metadata.endswith("]"):
            raise ParseError(
                line, "Line must end with the closing bracket ']'")
    if "=" not in metadata:
        if metadata.replace(" ", "").replace("]", "") != "":
            raise ParseError(line, "only 'str=str' format allowed")
        else:
            return {}
    else:
        pairs = re.findall(r"(\w+)=(-?\w+)", metadata)
        if not pairs:
            raise ParseError(line, "only 'str=str' format allowed")
        final_dict = dict(pairs)
        pairs_len = sum(len(k) + len(v) for k, v in pairs)
        new_part = metadata.replace("=", "").replace(" ", "").replace("]", "")
        if pairs_len != len(new_part):
            raise ParseError(line, "only 'str=str' format allowed")
    return final_dict
