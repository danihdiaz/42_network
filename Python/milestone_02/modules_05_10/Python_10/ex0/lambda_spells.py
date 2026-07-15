#!/usr/bin/env python3

def artifact_sorter(artifacts: list[dict]) -> list[dict]:
    return sorted(artifacts, key=lambda artifact: artifact["power"],
                  reverse=True)


def power_filter(mages: list[dict], min_power: int) -> list[dict]:
    return list(filter(lambda mage: mage["power"] >= min_power, mages))


def spell_transformer(spells: list[str]) -> list[str]:
    return list(map(lambda spell: "* "+spell+" *", spells))


def mage_stats(mages: list[dict]) -> dict:
    max_power = max(mages, key=lambda mage: mage["power"])
    min_power = min(mages, key=lambda mage: mage["power"])
    avg = round(sum(map(lambda mage: mage["power"], mages)) / len(mages), 2)
    final_dict = {"max_power": max_power["power"],
                  "min_power": min_power["power"], "avg_power": avg}
    return final_dict


if __name__ == "__main__":
    artifacts = [{'name': 'Crystal Orb', 'power': 74, 'type': 'weapon'},
                 {'name': 'Fire Staff', 'power': 63, 'type': 'accessory'},
                 {'name': 'Lightning Rod', 'power': 66, 'type': 'relic'},
                 {'name': 'Shadow Blade', 'power': 70, 'type': 'accessory'}]
    mages = [{'name': 'Phoenix', 'power': 90, 'element': 'lightning'},
             {'name': 'Luna', 'power': 95, 'element': 'lightning'},
             {'name': 'Casey', 'power': 64, 'element': 'ice'},
             {'name': 'Ash', 'power': 76, 'element': 'earth'},
             {'name': 'Rowan', 'power': 81, 'element': 'shadow'}]
    spells = ['meteor', 'shield', 'lightning', 'tsunami']
    print("\nTesting artifact sorter...")
    new_artifacts = artifact_sorter(artifacts)
    for i in range(len(new_artifacts) - 1):
        print(f"{new_artifacts[i]['name']} ({new_artifacts[i]['power']})"
              f" comes before {new_artifacts[i+1]['name']} "
              f"({new_artifacts[i+1]['power']})"
              )
    print("\nTesting power filter...")
    filtered_mages = power_filter(mages, 78)
    print("Mages with enough power:")
    for mage in filtered_mages:
        print(f"{mage['name']}, power {mage['power']}")
    print("\nTesting spell transformer...")
    print(" | ".join(spell_transformer(spells)))
    print("\nTesting mage stats...")
    stats = mage_stats(mages)
    print(f"Max power: {stats['max_power']}")
    print(f"Min power: {stats['min_power']}")
    print(f"Average power: {stats['avg_power']}")
