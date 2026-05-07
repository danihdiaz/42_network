#!/usr/bin/env python3

def garden_operations(operation_number: int) -> None:
    if operation_number == 0:
        int("abc")
    elif operation_number == 1:
        1 / 0
    elif operation_number == 2:
        open("/non/existing/file.txt")
    elif operation_number == 3:
        "abc" + 5
    else:
        print("Operation completed succesfully")
        return


def test_error_types() -> None:
    for i in range(5):
        try:
            print(f"Testing operation {i}...")
            garden_operations(i)
        except ValueError as er:
            print(f"Caught ValueError: {er}")
        except ZeroDivisionError as er:
            print(f"Caught ZeroDivisionError: {er}")
        except FileNotFoundError as er:
            print(f"Caught FileNotFoundError: {er}")
        except TypeError as er:
            print(f"Caught TypeError: {er}")


if __name__ == "__main__":
    print("=== Garden Error Types Demo ===")
    test_error_types()
    print("\nAll error types tested succesfully!")
