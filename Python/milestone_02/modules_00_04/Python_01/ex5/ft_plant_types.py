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


class Flower(Plant):
    def __init__(self, name: str, height: int, age: int, color: str) -> None:
        super().__init__(name, height, age)
        self.color = color
        self.has_bloomed = False

    def bloom(self) -> None:
        print(f"[asking the {self.name.lower()} to bloom]")
        self.has_bloomed = True

    def show(self) -> None:
        super().show()
        print(f" Color: {self.color}")
        if self.has_bloomed is False:
            print(f" {self.name} has not bloomed yet")
        else:
            print(f" {self.name} is blooming beautifully!")


class Tree(Plant):
    def __init__(self, name: str, height: int,
                 age: int, trunk_diameter: int) -> None:
        super().__init__(name, height, age)
        self.trunkdmtr = trunk_diameter

    def produce_shade(self) -> None:
        print(f"[asking the {self.name.lower()} to produce shade]")
        print(
            f"Tree {self.name} now produces a shade of "
            f"{self.height:.1f}cm long and {self.trunkdmtr:.1f}cm wide."
        )

    def show(self) -> None:
        super().show()
        print(f" Trunk diameter: {self.trunkdmtr:.1f}cm")


class Vegetable(Plant):
    def __init__(self, name: str, height: int,
                 age: int, harvest_season: str) -> None:
        super().__init__(name, height, age)
        self.harvest_season = harvest_season
        self.nutritional_value = 0

    def show(self) -> None:
        super().show()
        print(f" Harvest season: {self.harvest_season.capitalize()}")
        print(f" Nutritional value: {self.nutritional_value}")

    def age_and_grow(self, time: int) -> None:
        print(f"[make {self.name.lower()} grow and age for {time} days]")
        for i in range(time):
            super().age()
            self.height += 2.1
        self.nutritional_value += time


rose = Flower("Rose", 15, 10, "red")
oak = Tree("Oak", 200, 365, 5)
tomato = Vegetable("Tomato", 5, 10, "April")

if __name__ == "__main__":
    print("=== Garden Plant Types ===")
    print("=== Flower")
    rose.show()
    rose.bloom()
    rose.show()
    print()
    print("=== Tree")
    oak.show()
    oak.produce_shade()
    print()
    print("=== Vegetable")
    tomato.show()
    tomato.age_and_grow(20)
    tomato.show()
