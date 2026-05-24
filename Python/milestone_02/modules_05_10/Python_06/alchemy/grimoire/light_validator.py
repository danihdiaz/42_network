def validate_ingredients(ingredients: str) -> str:
    from .light_spellbook import light_spell_allowed_ingredients
    ing_list = ingredients.split(",")
    allowed = light_spell_allowed_ingredients()
    for ing in ing_list:
        for igr in allowed:
            if igr.lower() == ing.lower():
                return f"{ingredients} - VALID"
    else:
        return f"{ingredients} - INVALID"