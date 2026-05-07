#!/usr/bin/env python3

class Plant:
    def __init__(self, name, height, age):
        self.name = name
        self._height = height
        self._days_old = age

    def show(self):
        print(f"{self.name}: {self._height:.1f}cm, {self._days_old} days old")

    def set_height(self, height):
        if height < 0:
            print(f"{self.name}: Error, height can't be negative")
            print("Height update rejected")
        else:
            self._height = height
            print(f"Height updated: {self._height}cm")

    def set_age(self, age):
        if age < 0:
            print(f"{self.name}: Error, age can't be negative")
            print("Age update rejected")
        else:
            self._days_old = age
            print(f"Age updated: {self._days_old} days")


rose = Plant("Rose", 15, 10)

if __name__ == "__main__":
    print("=== Garden Security System ===")
    print("Plant created: ", end="")
    rose.show()
    print()
    rose.set_height(25)
    rose.set_age(30)
    print()
    rose.set_height(-5)
    rose.set_age(-12)
    print()
    print("Current state:", end=" ")
    rose.show()
