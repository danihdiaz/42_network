#!/usr/bin/env python3

class GardenError(Exception):
    def __init__(self, message="Unknown garden error"):
        super().__init__(message)


class PlantError(GardenError):
    def __init__(self, message="Unknown plant error"):
        super().__init__(message)


class WaterError(GardenError):
    def __init__(self, message="Unknown water error"):
        super().__init__(message)


def catch_plant_err():
    try:
        print("Testing PlantError...")
        raise PlantError("The tomato plant is wilting!")
    except PlantError as err:
        print(f"Caught PlantError: {err}\n")


def catch_water_err():
    try:
        print("Testing WaterError...")
        raise WaterError("Not enough water in the tank!")
    except WaterError as err:
        print(f"Caught WaterError: {err}\n")


def catch_garden_err():
    print("Testing catching all garden errors...")
    try:
        raise PlantError("The tomato plant is wilting!")
    except GardenError as err:
        print(f"Caught GardenError: {err}")
    try:
        raise WaterError("Not enough water in the tank!")
    except GardenError as err:
        print(f"Caught GardenError: {err}\n")


if __name__ == "__main__":
    print("=== Custom Garden Errors Demo ===\n")
    catch_plant_err()
    catch_water_err()
    catch_garden_err()
    print("All custom error types work correctly!")
