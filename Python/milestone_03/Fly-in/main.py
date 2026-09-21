#!/usr/bin/env python3

from network import Network
from parser import parser
from exceptions import ParseError
import sys
from scheduler import Scheduler

if __name__ == "__main__":
    try:
        network = parser("map_test.txt")
    except ParseError as e:
        print(e)
        sys.exit(1)

    print(f"nb_drones: {network.nb_drones}")
    print(f"start: {network.start}")
    print(f"end: {network.end}")

    print("\n--- zones ---")
    for name, zone in network.zones.items():
        print(f"{name}: {type(zone).__name__} x={zone.x} y={zone.y} "
              f"color={zone.color} max_drones={zone.max_drones}")

    print("\n--- connections ---")
    for name, conns in network.connections.items():
        print(f"{name}: {[c.zones for c in conns]} "
              f"(cap={[c.max_link_capacity for c in conns]})")

    scheduler = Scheduler(network)
    print("\n--- drones ---")
    for drone in scheduler.drones.keys():
        print(f"Drone ID: {drone}")
