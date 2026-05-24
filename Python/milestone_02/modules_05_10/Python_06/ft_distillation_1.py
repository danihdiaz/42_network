#!/usr/bin/env python3

from alchemy import strength_potion, heal

def main() -> None:
    print("=== Distillation 1 ===")
    print("Using: 'import alchemy' structure to access potions")
    print(f"Testing strength potion: {strength_potion()}")
    print(f"Testing heal alias: {heal()}")


if __name__ == "__main__":
    main()