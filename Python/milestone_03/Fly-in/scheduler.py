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
                    #lo que sea
            for drone in self.drones.values(): 
                if not drone.in_transit and not drone.delivered:
                    #lo que sea
            self.current_turn += 1
