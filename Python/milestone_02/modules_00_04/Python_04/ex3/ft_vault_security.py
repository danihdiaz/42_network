#!/usr/bin/env python3

def secure_archive(name: str, action: str = "r", content: str = "") -> tuple[bool, str]:
    try:
        if action == "r":
            with open(f"{name}", "r") as file:
                fcontent = file.read()
            return True, f"{fcontent}"
        elif action == "w":
            with open(f"{name}", "w") as newfile:
                ncontent = newfile.write(f"{content}")
            return True, "'Content successfully written to file'"
    except (PermissionError, FileNotFoundError) as err:
        return False, f"{err}"


def main() -> None:
    print("=== Cyber Archives Security ===\n")
    print("Using 'secure archive' to read from a nonexistent file:")
    print(secure_archive("/non/existing/file"))
    print("\nUsing 'secure archive' to read from an inaccessible file:")
    print(secure_archive("/etc/shadow"))
    print("\nUsing 'secure archive' to read from a regular file:")
    print(secure_archive("ancient_fragment.txt"))
    print("\nUsing 'secure archive' to write previous content to a new file:")
    print(secure_archive("new_file.txt", "w", "Hola que tal\n"))


if __name__ == "__main__":
    main()
