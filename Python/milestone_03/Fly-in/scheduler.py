from network import Network
from drone import Drone
from collections import deque


class Scheduler:
    def __init__(self, network: Network):
        self.network = network
        self.drones: dict[int, Drone] = {}
        start = network.start
        assert start is not None
        for i in range(1, network.nb_drones + 1):
            drone = Drone(i, start, deque())
            self.drones[i] = drone
            self.network.zones[start].occupants.add(drone.drone_id)
        self.current_turn = 0
        self.reservation_table: dict[tuple[str, int], int] = {}

    def run(self) -> None:
        while not all(drone.delivered for drone in self.drones.values()):
            has_moved: set[int] = set()
            for drone in self.drones.values():
                if drone.in_transit:
                    drone.current_zone = drone.route[0]
                    drone.route.popleft()
                    drone.in_transit = False
                    self.network.zones[drone.current_zone].occupants.add(drone.drone_id)
                    self.reservation_table[drone.current_zone, self.current_turn] -= 1
                    if drone.current_zone == self.network.end:
                        drone.delivered = True
                    has_moved.add(drone.drone_id)
            self.clear_connections()
            for drone in self.drones.values():
                if not drone.in_transit and not drone.delivered and drone.drone_id not in has_moved:
                    pass
            self.clear_connections()
            self.current_turn += 1

    def try_move_normal(self, drone: Drone) -> bool:
        target = drone.route[0]
        current = drone.current_zone
        for conn in self.network.connections[current]:
            if current in conn.zones and target in conn.zones:
                if (len(conn.occupants) < conn.max_link_capacity
                        and len(self.network.zones[target].occupants) < self.network.zones[target].max_drones):
                    conn.occupants.append(self.current_turn)
                    self.network.zones[target].occupants.add(drone.drone_id)
                    self.network.zones[current].occupants.remove(
                        drone.drone_id)
                    drone.current_zone = target
                    drone.route.popleft()
                    return True
        return False

    def try_move_restricted(self, drone: Drone) -> bool:
        target = drone.route[0]
        trgt_zone = self.network.zones[target]
        current = drone.current_zone
        arrival_turn = self.current_turn + 1
        reserv_key = (target, arrival_turn)
        reserved = self.reservation_table.get(reserv_key, 0)
        for conn in self.network.connections[current]:
            if current in conn.zones and target in conn.zones:
                if (len(conn.occupants) < conn.max_link_capacity
                        and len(trgt_zone.occupants) + reserved < trgt_zone.max_drones):
                    conn.occupants.append(arrival_turn)
                    self.reservation_table[reserv_key] = reserved + 1
                    self.network.zones[current].occupants.remove(
                        drone.drone_id)
                    drone.in_transit = True
                    return True
        return False

    def clear_connections(self) -> None:
        unique_conns = {conn for conns in self.network.connections.values()
                        for conn in conns}
        for conn in unique_conns:
            conn.occupants = [
                turn for turn in conn.occupants if turn != self.current_turn]
