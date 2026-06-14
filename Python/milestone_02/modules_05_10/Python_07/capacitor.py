#!/usr/bin/env python3

from ex1 import HealingCreatureFactory, TransformCreatureFactory


if __name__ == "__main__":
    print("Testing Creature with healing capability")
    print(" base:")
    healfactory = HealingCreatureFactory()
    sprouty = healfactory.create_base()
    sprouty.describe()
    print(sprouty.attack())
    print(sprouty.heal())
    print(" evolved:")
    bloomy = healfactory.create_evolved()
    bloomy.describe()
    print(bloomy.attack())
    print(bloomy.heal())
    print("\nTesting Creature with transform capability")
    print(" base:")
    transfactory = TransformCreatureFactory()
    shiftie = transfactory.create_base()
    shiftie.describe()
    print(shiftie.attack())
    print(shiftie.transform())
    print(shiftie.attack())
    print(shiftie.revert())
    print(" evolved:")
    morphy = transfactory.create_evolved()
    morphy.describe()
    print(morphy.attack())
    print(morphy.transform())
    print(morphy.attack())
    print(morphy.revert())
