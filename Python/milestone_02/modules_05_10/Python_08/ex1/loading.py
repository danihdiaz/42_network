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
    import matplotlib
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
        print(
            f"[OK] matplotlib ({matplotlib.__version__}) - Visualization ready")
try:
    def data_gen() -> pd.DataFrame:
        data = np.random.randn(1000)
        df = pd.DataFrame(data, columns=["value"])
        print("\nAnalyzing matrix data...")
        print("Processing 1000 data points...")
        return df
except AttributeError:
    pass

try:
    def png_gen(df: pd.DataFrame) -> None:
        print("Generating visualization...")
        plt.hist(df["value"])
        plt.savefig("matrix_analysis.png")
except AttributeError:
    pass

if __name__ == "__main__":
    print("\nLOADING STATUS: Loading programs...\n")
    dependency_checker()
    try:
        df = data_gen()
        png_gen(df)
        print("\nAnalysis complete!")
        print("Results saved to: matrix_analysis.png")
    except Exception:
        print("\nERROR: Run 'pip install -r requirements.txt' or 'poetry install' "
              "to install the necessary dependencies"
              )
