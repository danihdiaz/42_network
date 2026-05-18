#!/usr/bin/env python3

import math


def get_player_pos() -> tuple[float, float, float]:
    while True:
        try:
            raw = input("Enter new coordinates as floats"
                        " in format 'x, y, z': ")
            parts = raw.split(",")
            if len(parts) != 3:
                raise IndexError("Invalid syntax")
            for part in parts:
                try:
                    float(part)
                except ValueError as e:
                    print(f"Error on parameter '{part.strip()}': {e}")
                    raise ValueError
            coords = (float(parts[0]), float(parts[1]), float(parts[2]))
            return coords
        except IndexError as e:
            print(f"{e}")
        except ValueError:
            pass


def main() -> None:
    print("Get a first set of coordinates")
    cordnts = get_player_pos()
    print(f"Got a first tuple: {cordnts}")
    print(f"It includes: X={cordnts[0]}, Y={cordnts[1]}, Z={cordnts[2]}")
    dist = math.sqrt((cordnts[0]**2) +
                     (cordnts[1]**2) +
                     (cordnts[2]**2)
                     )
    print(f"Distance to center: {dist:.4f}")
    print("\nGet a second set of coordinates")
    second_cord = get_player_pos()
    sec_dist = math.sqrt((cordnts[0] - second_cord[0])**2 +
                         (cordnts[1] - second_cord[1])**2 +
                         (cordnts[2] - second_cord[2])**2
                         )
    print(f"Distance between the 2 sets of coordinates: {sec_dist:.4f}")


if __name__ == "__main__":
    main()
