#!/usr/bin/env python3

import sys


def detect() -> bool:
    return sys.prefix != sys.base_prefix


def display() -> None:
    if detect() is True:
        print("\nMATRIX STATUS: Welcome to the construct\n")
    else:
        print("\nMATRIX STATUS: You're still plugged in\n")
    py_version = f"{sys.executable}.{sys.version_info.minor}"
    print(f"Current Python: {py_version}")
    if detect() is False:
        print("Virtual Environment: None detected\n")
    else:
        env = sys.prefix.split("/")
        print(f"Virtual Environment: {env[-1]}")
        print(f"Environment path: ")




if __name__ == "__main__":
    display()
