#!/usr/bin/env python3

import sys

def parseo() -> dict:
	inventario = {}
	try:
		for i in range(1, len(sys.argv)):
			check_parts = sys.argv[i].split(":")
			if len(check_parts) != 2:
				print(f"Error - invalid parameter '{sys.argv[i]}'")
				continue
			elif len(check_parts) == 2:
				if check_parts[0] in inventario:
					print(f"Redundant item '{check_parts[0]}' - discarding")
					continue
				
	except:
		pass

if __name__ == "__main__":
	parseo()
