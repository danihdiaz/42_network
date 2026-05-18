#!/usr/bin/env python3

import sys


def arg_proc() -> list[int]:
    scores = []
    for i in range(1, len(sys.argv)):
        try:
            scores.append(int(sys.argv[i]))
        except ValueError:
            print(f"Invalid parameter: '{sys.argv[i]}'")
    return scores


def calc_stats(scores: list[int]) -> None:
    if not scores:
        print("No scores provided. Usage: python3 "
              "ft_score_analytics.py <score1> <score2> ..."
              )
    else:
        avg_score = int(sum(scores) / len(scores))
        scr_range = max(scores) - min(scores)
        print(f"Total players: {len(scores)}")
        print(f"Average score: {avg_score}")
        print(f"Total score: {sum(scores)}")
        print(f"High score: {max(scores)}")
        print(f"Low score: {min(scores)}")
        print(f"Score range: {scr_range}")


def main() -> None:
    print("=== Player Score Analytics ===")
    scores = arg_proc()
    if scores:
        print(f"Scores processed: {scores}")
    calc_stats(scores)


if __name__ == "__main__":
    main()
