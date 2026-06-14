#!/usr/bin/env python3

from ex0 import CreatureFactory, FlameFactory, AquaFactory


def test_factory(factory: CreatureFactory) -> None:
    print("Testing factory")
    factory_base = factory.create_base()
    factory_base.describe()
    print(factory_base.attack())
    factory_evolved = factory.create_evolved()
    factory_evolved.describe()
    print(factory_evolved.attack())


def test_battle(factory: CreatureFactory, opp: CreatureFactory) -> None:
    print("Testing battle")
    first_base = factory.create_base()
    first_base.describe()
    print(" vs.")
    opp_base = opp.create_base()
    opp_base.describe()
    print(" fight!")
    print(first_base.attack())
    print(opp_base.attack())


if __name__ == "__main__":
    flamefac = FlameFactory()
    aquafac = AquaFactory()
    test_factory(flamefac)
    print()
    test_factory(aquafac)
    print()
    test_battle(flamefac, aquafac)
