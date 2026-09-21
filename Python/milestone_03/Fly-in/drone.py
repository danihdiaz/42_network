from collections import deque


class Drone:
    def __init__(self, drone_id: int, current_zone: str, route: deque[str],
                 in_transit: bool = False, delivered: bool = False):
        self.drone_id = drone_id
        self.current_zone = current_zone
        self.in_transit = in_transit
        self.route = route
        self.delivered = delivered
