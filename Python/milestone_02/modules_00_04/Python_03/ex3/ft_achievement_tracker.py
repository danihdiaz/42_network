#!/usr/bin/env python3

import random

achievements = [
    'Crafting Genius',
    'Strategist',
    'World Savior',
    'Speed Runner',
    'Survivor',
    'Master Explorer',
    'Treasure Hunter',
    'Unstoppable',
    'First Steps',
    'Collector Supreme',
    'Untouchable',
    'Sharp Mind',
    'Boss Slayer',
    'Hidden Path Finder'
]


def gen_player_achievements() -> set[str]:
    nbr_achv = random.randint(1, 14)
    player_achievements = set(random.sample(achievements, nbr_achv))
    return player_achievements


def main() -> None:
    print("=== Achievement Tracker System ===\n")
    Alice = gen_player_achievements()
    print(f"Player Alice: {Alice}")
    Bob = gen_player_achievements()
    print(f"Player Bob: {Bob}")
    Charlie = gen_player_achievements()
    print(f"Player Charlie: {Charlie}")
    Dylan = gen_player_achievements()
    print(f"Player Dylan: {Dylan}\n")
    print(f"All distinct achievements: {Alice.union(Bob, Charlie, Dylan)}\n")
    print(f"Common achievements: {Alice.intersection(Bob, Charlie, Dylan)}\n")
    print(f"Only Alice has: {Alice.difference(Bob, Charlie, Dylan)}")
    print(f"Only Bob has: {Bob.difference(Alice, Charlie, Dylan)}")
    print(f"Only Charlie has: {Charlie.difference(Alice, Bob, Dylan)}")
    print(f"Only Dylan has: {Dylan.difference(Alice, Charlie, Bob)}\n")
    print(f"Alice is missing: {set(achievements).difference(Alice)}")
    print(f"Bob is missing: {set(achievements).difference(Bob)}")
    print(f"Charlie is missing: {set(achievements).difference(Charlie)}")
    print(f"Dylan is missing: {set(achievements).difference(Dylan)}")


if __name__ == "__main__":
    main()
