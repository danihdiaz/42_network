#!/usr/bin/env python3

from collections.abc import Callable
from typing import Any


def mage_counter() -> Callable:
    count = 0

    def increase_count() -> int:
        nonlocal count
        count += 1
        return count
    return increase_count


def spell_accumulator(initial_power: int) -> Callable:
    def increase_power(increase: int) -> int:
        nonlocal initial_power
        initial_power += increase
        return initial_power
    return increase_power


def enchantment_factory(enchantment_type: str) -> Callable:
    def enchant_item(item_name: str) -> str:
        enchanted_item = f"{enchantment_type} {item_name}"
        return enchanted_item
    return enchant_item


def memory_vault() -> dict[str, Callable]:
    vault = {}

    def store(key: str, value: Any) -> None:
        vault[key] = value

    def recall(key: str) -> Any:
        if key not in vault.keys():
            return "Memory not found"
        else:
            return vault[key]
    return {'store': store, 'recall': recall}


if __name__ == "__main__":
    print("\n==== Testing Scope Mysteries ====\n")
    print("Testing mage count...")
    counter = mage_counter()
    for _ in range(3):
        print(counter(), end=", ")
    print(counter())
    second_counter = mage_counter()
    print("Trying another counter:")
    for _ in range(2):
        print(second_counter(), end=", ")
    print(second_counter())
    print("Trying first one again:")
    print(counter())
    print("\nTesting spell accumulator...")
    accumulator = spell_accumulator(100)
    print(f"Base 100, add 20: {accumulator(20)}")
    print(f"Base 100, add 30: {accumulator(30)}")
    second_accum = spell_accumulator(50)
    print(f"Base 50, add 20: {second_accum(20)}")
    enchantment_types = ['Windy', 'Dark', 'Radiant']
    items_to_enchant = ['Cloak', 'Staff', 'Ring', 'Sword']
    print("\nTesting enchantment factory...")
    for enchant in enchantment_types:
        enchantment = enchantment_factory(enchant)
        for item in items_to_enchant:
            print(f"* {enchantment(item)}", end=" ")
        print()
    print("\nTesting memory vault...")
    functions_dict = memory_vault()
    storator = functions_dict['store']
    recallator = functions_dict['recall']
    print("Store 'secret' = 42")
    storator('secret', 42)
    print(f"Recall 'secret': {recallator('secret')}")
    print(f"Recall 'unknown': {recallator('unknown')}")
