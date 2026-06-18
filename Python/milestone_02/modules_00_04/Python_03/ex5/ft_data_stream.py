#!/usr/bin/env python3

from typing import Generator
import random


players = ["alice", "bob", "charlie", "dylan"]
actions = ["run", "eat", "sleep", "grab", "move", "climb", "swim"]


def gen_event() -> Generator[tuple[str, str], None, None]:
    while True:
        yield (random.choice(players), random.choice(actions))


def consume_event(
    prelist: list[tuple[str, str]]
) -> Generator[tuple[str, str], None, None]:
    while True:
        item_to_cons = random.choice(prelist)
        prelist.remove(item_to_cons)
        yield item_to_cons


def main() -> None:
    print("=== Game Data Stream Processor ===")
    gen = gen_event()
    for i in range(1000):
        playr_action = next(gen)
        print(
            f"Event {i}: Player {playr_action[0]}"
            f"did action {playr_action[1]}"
        )
    list_ten = []
    for _ in range(10):
        list_ten.append(next(gen))
    print(f"Built list of 10 events: {list_ten}")
    event = consume_event(list_ten)
    for _ in range(10):
        print(f"Got event from list: {next(event)}")
        print(f"Remains in list: {list_ten}")


if __name__ == "__main__":
    main()
