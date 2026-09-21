from typing import Optional


class Zone:
    def __init__(self, name: str, x: int, y: int, color: Optional[str] = None,
                 max_drones: int = 1):
        self.name = name
        self.x = x
        self.y = y
        self.color = color
        self.max_drones = max_drones
        self.occupants: set[int] = set()


class NormalZone(Zone):
    move_cost = 1


class PriorityZone(Zone):
    move_cost = 1


class RestrictedZone(Zone):
    move_cost = 2


class BlockedZone(Zone):
    pass
