#!/usr/bin/env python3

import sys


def main() -> None:
    if len(sys.argv) != 2:
        print("Usage: ft_ancient_text.py <file>\n")
    else:
        print("=== Cyber Archives Recovery ===")
        print(f"Accesing file '{sys.argv[1]}'")
        try:
            file = open(sys.argv[1], "r")
            content = file.read()
            print("---\n")
            print(f"{content}\n")
            print("---")
            file.close()
            print(f"File '{sys.argv[1]}' closed.\n")
        except (FileNotFoundError, PermissionError) as e:
            print(f"Error opening file '{sys.argv[1]}': {e}\n")

if __name__ == "__main__":
    main()
