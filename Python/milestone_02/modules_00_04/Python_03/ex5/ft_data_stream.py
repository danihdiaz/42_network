#!/usr/bin/env python3

from typing import Generator


players = ["alice", "bob", "charlie", "dylan"]
actions = ["run", "eat", "sleep", "grab", "move", "climb", "swim"]

def gen_event() -> Generator[tuple[str, str], None, None]:
	while True:
		yield 