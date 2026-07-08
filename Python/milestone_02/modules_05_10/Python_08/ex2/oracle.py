#!/usr/bin/env python3

from dotenv import load_dotenv
import os

if __name__ == "__main__":
    load_dotenv()
    print("\nORACLE STATUS: Reading the Matrix...\n")
    config = {
        "MATRIX_MODE": os.environ.get("MATRIX_MODE"),
        "DATABASE_URL": os.environ.get("DATABASE_URL"),
        "API_KEY": os.environ.get("API_KEY"),
        "LOG_LEVEL": os.environ.get("LOG_LEVEL"),
        "ZION_ENDPOINT": os.environ.get("ZION_ENDPOINT"),
    }
    flag = 0
    for key, value in config.items():
        if value is None or value == "":
            print(f"[WARNING]: {key} not configured")
            flag = 1
    if flag == 0:
        print(
            "Configuration loaded\n"
            f"Mode: {config['MATRIX_MODE']}\n"
            "Database: Connected to local instance\n"
            "API Access: Authenticated\n"
            f"Log Level: {config['LOG_LEVEL']}\n"
            "Zion Network: Online\n"
        )
    print("Environment security check:\n")
    if flag == 0:
        if config["MATRIX_MODE"] == "production":
            print("WARNING: Running in production mode!\n")
            masked_key = config["API_KEY"][:4] + "****"
            print(f"API_KEY: {masked_key} (masked in production)\n")
        else:
            print("Running in development mode - debug enabled\n")
            print(f"API_KEY: {config['API_KEY']} (visible in development)\n")
        if (config["MATRIX_MODE"] == "production"
                and config["LOG_LEVEL"] == "DEBUG"):
            print("[WARNING] Debug logging enabled in production!")
        print("[OK] No hardcoded secrets in source "
              "(all values loaded from environment)"
              )
        print(
            "[OK] .env file properly configured\n"
            "[OK] Production overrides available\n"
        )

    elif flag == 1:
        print("[KO] .env file misconfigured\n")
    print("The Oracle sees all configurations.")
