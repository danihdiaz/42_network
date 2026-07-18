#!/usr/bin/env python3

from collections.abc import Callable
from functools import wraps
import time
import random


def spell_timer(func: Callable) -> Callable:
    @wraps(func)
    def wrapper(*args, **kwargs):
        print(f"Casting {func.__name__}")
        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()
        time_result = end - start
        print(f"Spell completed in {time_result:.3f} seconds")
        return result
    return wrapper


@spell_timer
def test_timer(spell: str) -> str:
    time.sleep(0.15)
    return f"Result: {spell.capitalize()} cast!"


def power_validator(min_power: int) -> Callable:
    def decorator(func: Callable) -> Callable:
        @wraps(func)
        def wrapper(*args, **kwargs):
            if args[-1] >= min_power:
                result = func(*args, **kwargs)
                return result
            else:
                return "Insufficient power for this spell"
        return wrapper
    return decorator


@power_validator(min_power=10)
def test_power_validator(spell: str, power: int) -> str:
    return f"{spell} casted with power {power}"


def retry_spell(max_attempts: int) -> Callable:
    def decorator(func: Callable) -> Callable:
        @wraps(func)
        def wrapper(*args, **kwargs):
            attempt = 1
            while True:
                try:
                    result = func(*args, **kwargs)
                    return result
                except Exception:
                    if attempt <= max_attempts:
                        print(
                            "Spell failed, retrying... "
                            f"(attempt {attempt}/{max_attempts})"
                        )
                        attempt += 1
                    else:
                        return ("Spell casting failed "
                                f"after {max_attempts} attempts"
                                )
        return wrapper
    return decorator


@retry_spell(max_attempts=3)
def test_retry(spell: str, power: int) -> str:
    if random.random() < 0.7:
        raise Exception
    else:
        return f"{spell.capitalize()} casted with power {power}"


class MageGuild:
    def __init__(self, name: str):
        self.name = name

    @staticmethod
    def validate_mage_name(name: str) -> bool:
        if len(name) >= 3:
            spaceless = name.replace(" ", "")
            if spaceless.isalpha():
                return True
            else:
                return False
        else:
            return False

    @power_validator(min_power=10)
    def cast_spell(self, spell_name: str, power: int) -> str:
        return f"Succesfuly cast {spell_name.capitalize()} with {power} power"


if __name__ == "__main__":
    print("\n==== Testing Decorator Mastery ====\n")
    test_powers = [9, 21, 22, 7]
    spell_names = ['fireball', 'darkness', 'blizzard', 'freeze']
    mage_names = ['Jordan', 'Morgan Freeman',
                  'Nova', 'Kai Smith', 'Riley', 'Sage']
    invalid_names = ['Jo', 'A', 'Alex123', 'Test@Name']
    print("     Testing spell timer...\n")
    print(test_timer(random.choice(spell_names)), "\n")
    print(test_timer(spell=random.choice(spell_names)), "\n")
    print("     Testing power validator...\n")
    print(test_power_validator(random.choice(spell_names).capitalize(), 12))
    print(test_power_validator(random.choice(spell_names).capitalize(), 7))
    print("\n     Testing retry spell...\n")
    print(test_retry(random.choice(spell_names), 15))
    print("\n     Testing MazeGuild...")
    print(MageGuild.validate_mage_name(f"{random.choice(mage_names)}"))
    print(MageGuild.validate_mage_name(f"{random.choice(invalid_names)}"))
    my_mage = MageGuild(f"{random.choice(mage_names)}")
    print(my_mage.cast_spell(random.choice(spell_names), 15))
    print(my_mage.cast_spell(random.choice(spell_names), 7))
