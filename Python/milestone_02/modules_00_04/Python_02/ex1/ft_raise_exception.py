#!/usr/bin/env python3

def input_temperature(temp_str: str) -> int:
    print(f"Input data is '{temp_str}'")
    tempt = int(temp_str)
    if tempt > 40:
        raise ValueError(f"{tempt}ºC is too hot for plants (max 40ºC)")
    elif tempt < 0:
        raise ValueError(f"{tempt}ºC is too cold for plants (min 0ºC)")
    else:
        print(f"Temperature is now {tempt}ºC\n")
        return tempt


def test_temperature() -> None:
    try:
        input_temperature("25")
    except Exception as ex:
        print(f"Caught input_temperature error: {ex}\n")
    try:
        input_temperature("abc")
    except Exception as ex:
        print(f"Caught input_temperature error: {ex}\n")
    try:
        input_temperature("100")
    except Exception as ex:
        print(f"Caught input_temperature error: {ex}\n")
    try:
        input_temperature("-50")
    except Exception as ex:
        print(f"Caught input_temperature error: {ex}\n")


if __name__ == "__main__":
    print("=== Garden Temperature Checker ===\n")
    test_temperature()
    print("All tests completed - program didn't crash!")
