#!/usr/bin/env python3

from abc import ABC, abstractmethod
from typing import Any


class DataProcessor(ABC):
    def __init__(self) -> None:
        self._data: list[str] = []
        self._counter: int = 0

    @abstractmethod
    def validate(self, data: Any) -> bool:
        pass
    
    @abstractmethod
    def ingest(self, data: Any) -> None:
        pass
    
    def output(self) -> tuple[int, str]:
        return self._data.pop(0)


class NumericProcessor(DataProcessor):
    def __init__(self) -> None:
        super().__init__()
    
    def validate(self, data: Any) -> bool:
        if isinstance(data, (int, float)) or isinstance(data, list) and all(isinstance(x, (int, float)) for x in data):
            return True
        return False

    def ingest(self, data: Any) -> None:
        if not self.validate(data):
            raise ValueError("Improper numeric data")
        if isinstance(data, list):
            for item in data:
                self._data.append((self._counter, str(item)))
                self._counter += 1
        else:
            self._data.append((self._counter, str(data)))
            self._counter += 1


class TextProcessor(DataProcessor):
    def __init__(self) -> None:
        super().__init__()
    
    def validate(self, data: Any) -> bool:
        if isinstance(data, str) or isinstance(data, list) and all(isinstance(x, str) for x in data):
            return True
        else:
            return False
    
    def ingest(self, data: Any) -> None:
        if not self.validate(data):
            raise ValueError("Improper text data")
        if isinstance(data, list):
            for itm in data:
                self._data.append((self._counter, itm))
                self._counter += 1
        else:
            self._data.append((self._counter, itm))
            self._counter += 1
    
class LogProcessor(DataProcessor):
    def __init__(self) -> None:
        super().__init__()
    
    def validate(self, data: Any) -> bool:
        if isinstance(data, dict) and all(isinstance(x, str) and isinstance(y, str) for x, y in data.items()):
            return True
        elif isinstance(data, list) and all(isinstance(z, dict) and all(isinstance(x, str) and isinstance(y, str) for x, y in z.items()) for z in data):
            return True
        else:
            return False
    
    def ingest(self, data: Any) -> None:
        if not self.validate(data):
            raise ValueError("Improper log data")
        if isinstance(data, list):
            for item in data:
                values = list(item.values())
                self._data.append((self._counter, f"{values[0]}: {values[1]}"))
                self._counter += 1
        else:
                dvalues = list(data.values())
                self._data.append((self._counter, f"{dvalues[0]}: {dvalues[1]}"))
                self._counter += 1

def main() -> None:
    print("=== Code Nexus - Data Processor ===\n")
    print("Testing Numeric Processor")
    num = NumericProcessor()
    print(f" Trying to validate input '42': {num.validate(42)}")
    print(f" Trying to validate input 'Hello': {num.validate('Hello')}")
    print(" Test invalid ingestion of string 'foo' without prior validation:")
    try:
        num.ingest("foo")
    except ValueError as e:
        print(f" Got exception: {e}")
    print(" Processing data: [1, 2, 3, 4, 5]")
    print(" Extracting 3 values...")
    num.ingest([1, 2, 3, 4, 5])
    for _ in range(3):
        rank, value = num.output()
        print(f" Numeric value {rank}: {value}")
    print("\nTesting Text Processor...")
    txt = TextProcessor()
    print(f" Trying to validate input '42': {txt.validate(42)}")
    print(" Processing data: ['Hello', 'Nexus', 'World']")
    txt.ingest(['Hello', 'Nexus', 'World'])
    print(" Extracting 1 value...")
    trank, tvalue = txt.output()
    print(f" Text value {trank}: {tvalue}")
    print("\nTesting Log Processor...")
    log = LogProcessor()
    print(f" Trying to validate input '42': {log.validate(42)}")
    print(" Processing data: [{'log_level': 'NOTICE', 'log_message': 'Connection to server'}, {'log_level': 'ERROR', 'log_message': 'Unauthorized access!!'}]")
    log.ingest([{'log_level': 'NOTICE', 'log_message': 'Connection to server'}, {'log_level': 'ERROR', 'log_message': 'Unauthorized access!!'}])
    print(" Extracting 2 values...")
    for _ in range(2):
        lrank, lvalue = log.output()
        print(f" Log entry {lrank}: {lvalue}")


if __name__ == "__main__":
    main()