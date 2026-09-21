from network import Network
from drone import Drone

class Scheduler:
    def __init__(self, network: Network):
        self.network: network
        self.drones: dict[int, Drone] = {}
        for i in range(1, network.nb_drones + 1):
            drone = Drone(i, network.start, [])
            self.drones[i] = drone