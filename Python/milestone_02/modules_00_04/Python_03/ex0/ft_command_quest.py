#!/usr/bin/env python3

import sys


def main() -> None:
    print("=== Command Quest ===")
    print("Program name: ft_command_quest.py")
    if len(sys.argv) > 1:
        print(f"Arguments received: {len(sys.argv)}")
        for i in range(1, len(sys.argv)):
            print(f"Argument {i}: {sys.argv[i]}")
    else:
        print("No arguments provided!")
    print(f"Total arguments: {len(sys.argv)}")


if __name__ == "__main__":
    main()
