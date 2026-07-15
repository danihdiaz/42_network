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


def power_amplifier(base_spell: Callable, multiplier: int) -> Callable:
    def amplified_spell(target: str, power: int) -> str:
        return base_spell(target, power * multiplier)
    return amplified_spell


def conditional_parameter(target: str, power: int) -> bool:
    valid_targets = ['Dragon', 'Goblin', 'Wizard', 'Knight']
    if target not in valid_targets or power < 0:
        return False
    else:
        return True


def conditional_caster(condition: Callable, spell: Callable) -> Callable:
    def check_spell(target: str, power: int) -> str:
        if condition(target, power):
            return spell(target, power)
        else:
            return "Spell fizzled"
    return check_spell


def spell_sequence(spells: list[Callable]) -> Callable:
    def list_spells(target: str, power: int) -> list[str]:
        new_list = []
        for spell in spells:
            result = spell(target, power)
            new_list.append(result)
        return new_list
    return list_spells


if __name__ == "__main__":
    print("\n======== Testing higher order functions ========")
    print("\nTesting spell combiner...")
    combined = spell_combiner(lightning, heal)
    print(f"{combined('Dragon', 24)[0]}, {combined('Dragon', 24)[1]}")
    print("\nTesting power amplifier...")
    amplified = power_amplifier(fireball, 5)
    print(amplified("Goblin", 20))
    print("\nTesting conditional caster...")
    checked = conditional_caster(conditional_parameter, shield)
    print(checked("Goblin", 25))
    print("Testing conditional caster error...")
    print(checked("Dwarf", -3))
    print("\nTesting spell sequence...")
    spells = [shield, lightning, fireball, heal]
    listed_spells = spell_sequence(spells)
    print(listed_spells("Wizard", 30))
