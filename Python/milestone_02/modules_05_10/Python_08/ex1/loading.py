#!/usr/bin/env python3

try:
    import pandas as pd
except ModuleNotFoundError:
    pd = None

try:
    import numpy as np
except ModuleNotFoundError:
    np = None

try:
    import matplotlib.pyplot as plt
except ModuleNotFoundError:
    plt = None

def dependency_checker() -> None:
    print("Checking dependencies:")
    if pd is None:
        print("[KO] pandas not installed")
    else:
        print(f"[OK] pandas ({pd.__version__}) - Data manipulation ready")
    if np is None:
        print("[KO] numpy not installed")
    else:
        print(f"[OK] numpy ({np.__version__}) - Numerical computation ready")
    if plt is None:
        print("[KO] matplotlib not installed")
    else:
        print(f"[OK] matplotlib ({plt.__version__}) - Visualization ready")


def data_gen() -> pd.DataFrame:
    print("\nAnalyzing matrix data...")
    print("Processing 1000 data points...")
    data = np.random.randn(1000)
    df = pd.DataFrame(data, columns=["value"])
    return df


def png_gen(df: pd.DataFrame) -> None:
    


if __name__ == "__main__":
    print("\nLOADING STATUS: Loading programs...\n")
    dependency_checker()
    data_gen()