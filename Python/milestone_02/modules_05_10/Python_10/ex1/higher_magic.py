#!/usr/bin/env python3

from collections.abc import Callable


def fireball(target: str, power: int) -> str:
    return f"Fireball hits {target} for {power} damage"


def heal(target: str, power: int) -> str:
    return f"Heal restores {target} for {power} HP"


def shield(target: str, power: int) -> str:
    return f"Shield protects {target} with {power} defense"


def lightning(target: str, power: int) -> str:
    return f"Lightning strikes {target} for {power} damage"


def spell_combiner(spell1: Callable, spell2: Callable) -> Callable:
    def combined_spells(target: str, power: int) -> tuple:
        return (spell1(target, power), spell2(target, power))
    return combined_spells


if __name__=="__main__":
    combined = spell_combiner(lightning, heal)
    print(f"{combined('Dragon', 24)[0]}, {combined('Dragon', 24)[1]}")