#!/usr/bin/env python3

import sys


def parseo() -> dict[str, int]:
    inventario = {}
    try:
        if len(sys.argv) == 1:
            raise ValueError("No parameters provided")
        for i in range(1, len(sys.argv)):
            check_parts = sys.argv[i].split(":")
            if len(check_parts) != 2:
                print(f"Error - invalid parameter '{sys.argv[i]}'")
                continue
            elif len(check_parts) == 2:
                if check_parts[0] in inventario:
                    print(f"Redundant item '{check_parts[0]}' - discarding")
                    continue
                else:
                    try:
                        int(check_parts[1])
                        inventario[f"{check_parts[0]}"] = int(check_parts[1])
                    except ValueError as e:
                        print(f"Quantity error for '{check_parts[0]}': {e}")
    except ValueError as e:
        print(e)
        sys.exit(1)
    return inventario


def main(invent: dict[str, int]) -> None:
    if invent is None:
        return
    print(f"Got inventory: {invent}")
    print(f"Item list: {list(invent.keys())}")
    print(
        f"Total quantity of the {len(invent.keys())} "
        f"items: {sum(invent.values())}"
    )
    for key, value in invent.items():
        print(
            f"Item {key} represents "
            f"{round(value * 100 / sum(invent.values()), 1)}%"
        )
    most_item = max(invent, key=lambda k: invent[k])
    least_item = min(invent, key=lambda k: invent[k])
    print(f"Item most abundant: {most_item} with quantity {invent[most_item]}")
    print(f"Item least abundant: {least_item} "
          f"with quantity {invent[least_item]}"
          )
    invent["magic_item"] = 1
    print(f"Updated inventory: {invent}")


if __name__ == "__main__":
    print("=== Inventory System Analysis ===")
    invnt = parseo()
    main(invnt)
