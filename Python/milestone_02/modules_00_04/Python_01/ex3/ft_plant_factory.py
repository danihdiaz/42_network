#!/usr/bin/env python3

class Plant:
    def __init__(self, name: str, height: int, age: int) -> None:
        self.name = name
        self.height = height
        self.days_old = age

    def show(self) -> None:
        print(f"{self.name}: {self.height:.1f}cm, {self.days_old} days old")


rose = Plant("Rose", 25, 30)
oak = Plant("Oak", 200, 365)
cactus = Plant("Cactus", 5, 90)
sunflower = Plant("Sunflower", 80, 45)
fern = Plant("Fern", 15, 120)

if __name__ == "__main__":
    print("=== Plant Factory Output ===")
    plants = [rose, oak, cactus, sunflower, fern]
    for plant in plants:
        print("Created: ", end="")
        plant.show()
