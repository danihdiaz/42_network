from network import Network
from drone import Drone
from collections import deque


class Scheduler:
    def __init__(self, network: Network):
        self.network = network
        self.drones: dict[int, Drone] = {}
        assert network.start is not None
        for i in range(1, network.nb_drones + 1):
            drone = Drone(i, network.start, deque())
            self.drones[i] = drone
        self.current_turn = 0
        self.reservation_table: dict[tuple[str, int], int] = {}

    def run(self) -> None:
        while not all(drone.delivered for drone in self.drones.values()):
            for drone in self.drones.values():
                if drone.in_transit:
                    pass
            for drone in self.drones.values():
                if not drone.in_transit and not drone.delivered:
                    pass
            clear_connections()
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
    current = drone.current_zone
    for conn in self.network.connections[current]:
        if current in conn.zones and target in conn.zones:
            if (len(conn.occupants) < conn.max_link_capacity
                    and len(self.network.zones[target].occupants) + self.reservation_table.get((target, current_turn + 1), 0) < self.network.zones[target].max_drones):
                conn.occupants.append(self.current_turn)
                key = (target, self.current_turn + 1)
                self.reservation_table[key] = self.reservation_table.get(key, 0) + 1
                self.network.zones[target].occupants.add(drone.drone_id)
                self.network.zones[current].occupants.remove(
                    drone.drone_id)
                return True
    return False

def clear_connections(self) -> None:
    unique_conns = {conn for conns in self.network.connections.values()
                    for conn in conns}
    for conn in unique_conns:
        conn.occupants = [
            turn for turn in conn.occupants if turn != self.current_turn]
