#!/usr/bin/env python3

import random

names = ["Alice", "bob", "Charlie", "dylan",
         "Emma", "Gregory", "john", "kevin", "Liam"]


def main() -> None:
    print("=== Game Data Alchemist ===\n")
    print(f"Initial list of players: {names}")
    cap_names = [n.capitalize() for n in names]
    print(f"New list with all names capitalized: {cap_names}")
    only_cap_names = [n for n in names if n == n.capitalize()]
    print(f"New list of capitalized names only: {only_cap_names}\n")
    score_dict = {nombre: random.randint(0, 999) for nombre in cap_names}
    print(f"Score dict: {score_dict}")
    scr_avg = sum(score_dict.values()) / len(score_dict.values())
    print(f"Score average is {round(scr_avg, 2)}")
    dict_avb_avg = {key: value for key,
                    value in score_dict.items() if value > scr_avg}
    print(f"High scores: {dict_avb_avg}")


if __name__ == "__main__":
    main()
