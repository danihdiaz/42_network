#!/usr/bin/env python3

class Plant:
    def __init__(self, name: str, height: int | float, age: int) -> None:
        self.name = name
        self.height = height
        self.days_old = age
        self._stats = Plant.Stats()

    def show(self) -> None:
        print(f"{self.name}: {self.height:.1f}cm, {self.days_old} days old")
        self._stats.show_count += 1

    def grow(self) -> None:
        self.height += 8
        self._stats.grow_count += 1

    def age(self) -> None:
        self.days_old += 1
        self._stats.age_count += 1

    @staticmethod
    def older_than_year(age: int) -> bool:
        return age > 365

    @classmethod
    def create_anonymous(cls) -> "Plant":
        return cls("Unknown plant", 0, 0)

    class Stats:
        def __init__(self) -> None:
            self.grow_count = 0
            self.age_count = 0
            self.show_count = 0

        def display(self, name: str) -> None:
            print(f"[statistics for {name}]")
            print(
                f"Stats: {self.grow_count} grow, {self.age_count} age, "
                f"{self.show_count} show"
            )


class Flower(Plant):
    def __init__(self, name: str, height: int, age: int, color: str) -> None:
        super().__init__(name, height, age)
        self.color = color
        self.has_bloomed = False

    def bloom(self) -> None:
        self.has_bloomed = True

    def show(self) -> None:
        super().show()
        print(f" Color: {self.color}")
        if self.has_bloomed is False:
            print(f" {self.name} has not bloomed yet")
        else:
            print(f" {self.name} is blooming beautifully!")


class Seed(Flower):
    def __init__(self, name: str, height: int, age: int, color: str) -> None:
        super().__init__(name, height, age, color)
        self.seeds = 0

    def bloom(self) -> None:
        super().bloom()
        self.seeds += 42

    def grow(self) -> None:
        super().grow()
        self.height += 22

    def age(self) -> None:
        super().age()
        self.days_old += 19

    def show(self) -> None:
        super().show()
        print(f" Seeds: {self.seeds}")


class Tree(Plant):
    def __init__(self, name: str, height: int,
                 age: int, trunk_diameter: int) -> None:
        super().__init__(name, height, age)
        self.trunkdmtr = trunk_diameter
        self._stats: "Tree.Stats" = Tree.Stats()

    def produce_shade(self) -> None:
        print(f"[asking the {self.name.lower()} to produce shade]")
        print(
            f"Tree {self.name} now produces a shade of {self.height:.1f}cm "
            f"long and {self.trunkdmtr:.1f}cm wide."
        )
        self._stats.shade_count += 1

    def show(self) -> None:
        super().show()
        print(f" Trunk diameter: {self.trunkdmtr:.1f}cm")

    class Stats(Plant.Stats):
        def __init__(self) -> None:
            super().__init__()
            self.shade_count = 0

        def display(self, name: str) -> None:
            super().display(name)
            print(f" {self.shade_count} shade")


class Vegetable(Plant):
    def __init__(self, name: str, height: int | float,
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
sunflower = Seed("Sunflower", 80, 45, "yellow")


def display_stats(plant: Plant) -> None:
    plant._stats.display(plant.name)


if __name__ == "__main__":
    print("=== Garden statistics ===")
    print("=== Check year-old")
    print(f"Is 30 days more than a year? -> {Plant.older_than_year(30)}")
    print(f"Is 400 days more than a year? -> {Plant.older_than_year(400)}")
    print("\n=== Flower")
    rose.show()
    display_stats(rose)
    rose.grow()
    rose.bloom()
    print("[asking the rose to grow and bloom]")
    rose.show()
    display_stats(rose)
    print("\n=== Tree")
    oak.show()
    display_stats(oak)
    oak.produce_shade()
    display_stats(oak)
    print("\n=== Seed")
    sunflower.show()
    display_stats(sunflower)
    sunflower.bloom()
    sunflower.grow()
    sunflower.age()
    print("[make sunflower grow, age and bloom]")
    sunflower.show()
    display_stats(sunflower)
    print("\n=== Anonymous")
    anonymous = Plant.create_anonymous()
    anonymous.show()
    display_stats(anonymous)
