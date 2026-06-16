import sys

def parse_config(filepath: str) -> dict:
	"""Parse the maze configuration file.

    Args:
        filepath: Path to the configuration file.

    Returns:
        A dictionary with the parsed and validated configuration.

    Raises:
        FileNotFoundError: If the file does not exist.
		SyntaxError: If the syntax is not KEY=VALUE.
    """
	config = {}
	try:
		with open(filepath, "r") as f:
			for line in f:
				try:
					if line.startswith("#") or line == "\n" :
						continue
					else:
						if "=" not in line:
							raise SyntaxError("Bad syntax")
						else:
							key, value = line.split("=", 1)
							key = key.strip()
							value = value.strip()
							config[key] = value
				except SyntaxError as e:
					print(e)
					return
	except FileNotFoundError as er:
		print(er)
		return
	return config


def dict_validation(config: dict[str, str]) -> dict:
	"""Validate the dictionary elements from parse_config.

	Args: 
		config: Already parsed dictionary.
	
	Returns:
		A dictionary ready for the generator to use.
	
	Raises:
		ValueError: If a required key is missing or has an invalid value.
	"""
	if config is None:
		sys.exit(1)
	required_keys = ["WIDTH", "HEIGHT", "ENTRY", "EXIT", "OUTPUT_FILE", "PERFECT"]
	try:
		for rkeys in required_keys:
			for keys in config:
				if rkeys == keys:
					break
			


if __name__ == "__main__":
	configuration = parse_config(sys.argv[1])
	if configuration is not None:
		print(dict_validation(configuration))

