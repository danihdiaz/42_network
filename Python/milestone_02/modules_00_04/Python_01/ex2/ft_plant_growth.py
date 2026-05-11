#!/usr/bin/env python3

class Plant:
    def __init__(self, name: str, height: int | float, age: int) -> None:
        self.name = name
        self.height = height
        self.days_old = age

    def show(self) -> None:
        print(f"{self.name}: {self.height:.1f}cm, {self.days_old} days old")

    def grow(self) -> None:
        self.height += 0.8

    def age(self) -> None:
        self.days_old += 1


rose = Plant("Rose", 25, 30)

if __name__ == "__main__":
    print("=== Garden Plant Growth ===")
    rose.show()
    total_growth = 0.0
    for i in range(1, 8):
        print(f"=== Day {i} ===")
        rose.grow()
        rose.age()
        rose.show()
        total_growth += 0.8
    print(f"Growth this week: {total_growth:.1f}cm")
