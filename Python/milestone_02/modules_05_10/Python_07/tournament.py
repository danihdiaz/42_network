#!/usr/bin/env python3
from ex0 import CreatureFactory, FlameFactory, AquaFactory
from ex2 import BattleStrategy, NormalStrategy, AggresiveStrategy, DefensiveStrategy


def battle(creatures: list[tuple[CreatureFactory, BattleStrategy]]) -> None:
    print("* Battle *")
    try:
        for i in range(len(creatures)):
            factory, strategy = creatures[i]
            creature = factory.create_base()
            creature.describe()
            strategy.act(creature)
            for j in range(i + 1, len(creatures)):
                opp_factory, opp_strategy = creatures[j]
                opp = opp_factory.create_base()
                opp_strategy.act(opp)
        