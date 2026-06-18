#!/usr/bin/env python3

import sys


def main() -> None:
    if len(sys.argv) != 2:
        print("Usage: ft_stream_management.py <file>\n")
        return
    else:
        print("=== Cyber Archives Recovery & Preservation ===")
        print(f"Accesing file '{sys.argv[1]}'")
        content = None
        try:
            file = open(sys.argv[1], "r")
            content = file.read()
            print("---\n")
            print(f"{content}\n")
            print("---")
            file.close()
            print(f"File '{sys.argv[1]}' closed.\n")
        except (FileNotFoundError, PermissionError) as e:
            sys.stderr.write(
                f"[STDERR] Error opening file '{sys.argv[1]}': {e}\n")
            return
        if content:
            print("Transform data:\n---\n")
            lines = []
            new_lines = content.split("\n")
            for line in new_lines:
                lines.append(f"{line}#")
            new_content = "\n".join(lines)
            print(f"{new_content}\n\n---")
            print("Enter new file name (or empty): ", end="")
            sys.stdout.flush()
            new_name = sys.stdin.readline().strip("\n")
            if new_name == "":
                print("Not saving data.")
            else:
                try:
                    print(f"Saving data to '{new_name}'")
                    new_file = open(f"{new_name}", "w")
                    new_file.write(f"{new_content}\n")
                    new_file.close()
                    print(f"Data saved in file '{new_name}'.\n")
                except PermissionError as e:
                    sys.stderr.write(
                        f"[STDERR] Error opening file '{sys.argv[1]}': {e}\n")


if __name__ == "__main__":
    main()
