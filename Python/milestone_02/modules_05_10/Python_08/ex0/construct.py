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
        print("WARNING: You're in the global environment!")
        print("The machines can see everything you install.\n")
        print("To enter the construct, run:")
        print("python -m venv matrix_env")
        print("source matrix_env/bin/activate # On Unix")
        print(r"matrix_env\Scripts\activate  # On Windows")
        print("\nThen run this program again.")
    else:
        env = sys.prefix.split("/")
        print(f"Virtual Environment: {env[-1]}")
        print(f"Environment path: {sys.prefix}\n")
        print("SUCCESS: You're in an isolated environment!")
        print("Safe to install packages without affecting\nthe global system.")
        print("\nPackage installation path:")
        print(sys.path[-1])


if __name__ == "__main__":
    display()
