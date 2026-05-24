from .dark_spellbook import dark_spell_allowed_ingredients

def validate_ingredients(ingredients: str) -> str:
    ing_list = ingredients.split(",")
    allowed = dark_spell_allowed_ingredients()
    for ing in ing_list:
        for igr in allowed:
            if igr.lower() == ing.lower():
                return f"{ingredients} - VALID"
    else:
        return f"{ingredients} - INVALID"