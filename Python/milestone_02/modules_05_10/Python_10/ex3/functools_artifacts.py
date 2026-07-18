#!/usr/bin/env python3

from collections.abc import Callable
from functools import reduce, partial, lru_cache, singledispatch
from operator import add, mul
from typing import Any


def spell_reducer(spells: list[int], operation: str) -> int:
    valid_operations = {'add': add, 'multiply': mul, 'max': max, 'min': min}
    if operation not in valid_operations.keys():
        raise ValueError(f"Error: '{operation}' is not a valid operation")
    if not spells:
        return 0
    function = valid_operations[operation]
    result = reduce(function, spells)
    return result


def enchant(power: int, element: str, target: str) -> str:
    return f"{target} is enchanted with {element} at power {power}"


def partial_enchanter(base_enchantment: Callable) -> dict[str, Callable]:
    enchants = {}
    fire_enchant = partial(base_enchantment, power=50, element='Fire')
    water_enchant = partial(base_enchantment, power=50, element='Water')
    wind_enchant = partial(base_enchantment, power=50, element='Wind')
    enchants["Fire"] = fire_enchant
    enchants["Water"] = water_enchant
    enchants["Wind"] = wind_enchant
    return enchants


@lru_cache
def memoized_fibonacci(n: int) -> int:
    if n <= 1:
        return n
    return memoized_fibonacci(n - 1) + memoized_fibonacci(n - 2)


def spell_dispatcher() -> Callable[[Any], str]:
    @singledispatch
    def process(value) -> str:
        return "Unknown spell type"

    @process.register
    def _(value: int):
        return f"Damage spell: {value} damage"

    @process.register
    def _(value: str):
        return f"Enchantment: {value}"

    @process.register
    def _(value: list):
        return f"Multi-cast: {len(value)} spells"
    return process


if __name__ == "__main__":
    print("\n==== Testing functools artifacts ====\n")
    spell_powers = [29, 26, 33, 11, 20, 49]
    operations = ['add', 'multiply', 'max', 'min']
    fibonacci_tests = [15, 20, 10]
    print("Testing spell reducer...")
    print(f"Sum: {spell_reducer(spell_powers, 'add')}")
    print(f"Product: {spell_reducer(spell_powers, 'multiply')}")
    print(f"Max: {spell_reducer(spell_powers, 'max')}")
    print(f"Min: {spell_reducer(spell_powers, 'min')}")
    print(" Testing unknown operation:")
    try:
        print(f"Max: {spell_reducer(spell_powers, 'ma')}")
    except ValueError as e:
        print(e)
    print("\nTesting partial enchanter...")
    enchant_dict = partial_enchanter(enchant)
    for value in enchant_dict.values():
        print(value(target='Sword'))
    print("\nTesting memoized fibonacci...")
    print(f"Fib(0): {memoized_fibonacci(0)}")
    print(f"Fib(1): {memoized_fibonacci(1)}")
    print(f"Fib(10): {memoized_fibonacci(10)}")
    print(memoized_fibonacci.cache_info())
    print(f"Fib(10): {memoized_fibonacci(10)}")
    print(memoized_fibonacci.cache_info())
    print(f"Fib(15): {memoized_fibonacci(15)}")
    print(memoized_fibonacci.cache_info())
    print("\nTesting spell dispatcher...")
    dispatcher = spell_dispatcher()
    print(dispatcher(42))
    print(dispatcher('fireball'))
    print(dispatcher(['heal', 'fireball', 'shield']))
    print(dispatcher(23.5))
