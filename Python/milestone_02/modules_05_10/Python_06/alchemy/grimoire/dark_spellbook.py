from .dark_validator import validate_ingredients

def dark_spell_allowed_ingredients() -> list[str]:
    return ["bats", "frogs", "arsenic", "eyeball"]


def dark_spell_record(spell_name: str, ingredients: str) -> str:
    if validate_ingredients(ingredients) == f"{ingredients} - VALID":
        return f"Spell recorded: {spell_name} ({validate_ingredients(ingredients)})"