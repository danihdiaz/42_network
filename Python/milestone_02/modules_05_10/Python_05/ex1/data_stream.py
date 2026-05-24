#!/usr/bin/env python3

from abc import ABC, abstractmethod
from typing import Any


class DataProcessor(ABC):
    def __init__(self) -> None:
        self._data: list[tuple[int, str]] = []
        self._counter: int = 0
        self._name: str = ""

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
        self._name: str = "Numeric Processor"
    
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
        self._name: str = "Text Processor"

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
            self._data.append((self._counter, data))
            self._counter += 1
    
class LogProcessor(DataProcessor):
    def __init__(self) -> None:
        super().__init__()
        self._name: str = "Log Processor"
    
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


class DataStream():
    def __init__(self) -> None:
        self._processors: list[DataProcessor] = []
    
    def register_processor(self, proc: DataProcessor) -> None:
        self._processors.append(proc)
    
    def process_stream(self, stream: list[Any]) -> None:
        for data in stream:
            for proc in self._processors:
                if proc.validate(data) is True:
                    proc.ingest(data)
                    break
            else:
                print(f"DataStream error - Can't process element in stream: {data}")

    def print_processors_stats(self) -> None:
        print("== DataStream statistics ==")
        if not self._processors:
            print("No processor found, no data")
        else:
            for procs in self._processors:
                print(f"{procs._name}: total {procs._counter} items processed, remaining {len(procs._data)} on processor")

def main() -> None:
    print("=== Code Nexus - Data Stream ===\n")
    print("Initialize Data Stream...")
    data = DataStream()
    data.print_processors_stats()
    print(f"\nRegistering Numeric Processor\n")
    num = NumericProcessor()
    data.register_processor(num)
    print("Send first batch of data on stream: ['Hello world', [3.14, -1, 2.71], [{'log_level': 'WARNING', 'log_message': 'Telnet access! Use ssh instead'}, {'log_level': 'INFO', 'log_message': 'User wil isconnected'}], 42, ['Hi', 'five']]")
    data.process_stream(['Hello world', [3.14, -1, 2.71], [{'log_level': 'WARNING', 'log_message': 'Telnet access! Use ssh instead'}, {'log_level': 'INFO', 'log_message': 'User wil isconnected'}], 42, ['Hi', 'five']])
    data.print_processors_stats()
    print("\nRegistering other data processors")
    txt = TextProcessor()
    log = LogProcessor()
    data.register_processor(txt)
    data.register_processor(log)
    print("Sending the same batch again")
    data.process_stream(['Hello world', [3.14, -1, 2.71], [{'log_level': 'WARNING', 'log_message': 'Telnet access! Use ssh instead'}, {'log_level': 'INFO', 'log_message': 'User wil isconnected'}], 42, ['Hi', 'five']])
    data.print_processors_stats()
    print("\nConsume some elements from the data processors: Numeric 3, Text 2, Log 1")
    for _ in range(3):
        num.output()
    for _ in range(2):
        txt.output()
    log.output()
    data.print_processors_stats()

if __name__ == "__main__":
    main()