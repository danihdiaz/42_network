#!/usr/bin/env python3
from ex0 import CreatureFactory, FlameFactory, AquaFactory
from ex1 import HealingCreatureFactory, TransformCreatureFactory
from ex2 import BattleStrategy, NormalStrategy, AggresiveStrategy, DefensiveStrategy


def battle(creatures: list[tuple[CreatureFactory, BattleStrategy]]) -> None:
    try:
        for i in range(len(creatures) - 1):
            factory, strategy = creatures[i]
            creature = factory.create_base()
            for j in range(i + 1, len(creatures)):
                print("\n* Battle *")
                opp_factory, opp_strategy = creatures[j]
                opp = opp_factory.create_base()
                creature.describe()
                print(" vs.")
                opp.describe()
                print(" now fight!")
                strategy.act(creature)
                opp_strategy.act(opp)
    except Exception as e:
        print(e)


def tournament(fighters: list[tuple[CreatureFactory, BattleStrategy]], name: str) -> None:
    print(name)
    pairs = [f"({type(f).__name__.replace('Factory', '')}+{type(s).__name__.replace('Strategy', '')})" for f, s in fighters]
    print(f" [ {', '.join(pairs)} ]")
    print("*** Tournament ***")
    print(f"{len(fighters)} opponents involved")
    battle(fighters)


if __name__ == "__main__":
    flamefac = FlameFactory()
    normalstr = NormalStrategy()
    healfac = HealingCreatureFactory()
    defstr = DefensiveStrategy()
    aggstr = AggresiveStrategy()
    fighters = [(flamefac, normalstr), (healfac,  defstr)]
    tournament(fighters, "Tournament 0 (basic)")
    print()
    fighterr = [(flamefac, aggstr), (healfac,  defstr)]
    tournament(fighterr, "Tournament 1 (error)")
    print()
    aquafac = AquaFactory()
    transfac = TransformCreatureFactory()
    fightmul = [(aquafac, normalstr), (healfac,  defstr), (transfac, aggstr)]
    tournament(fightmul, "Tournament 2 (multiple)")