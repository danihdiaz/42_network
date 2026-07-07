#!/usr/bin/env python3

from pydantic import BaseModel, Field, ValidationError
import datetime
from typing import Optional


class SpaceStation(BaseModel):
    station_id: str = Field(min_length=3, max_length=10)
    name: str = Field(max_length=50)
    crew_size: int = Field(ge=1, le=20)
    power_level: float = Field(ge=0.0, le=100.0)
    oxygen_level: float = Field(ge=0.0, le=100.0)
    last_maintenance: datetime.datetime
    is_operational: bool = True
    notes: Optional[str] = Field(default=None, max_length=200)


def main() -> None:
    print("Space Station Data Validation")
    print("======================================")
    try:
        my_station = SpaceStation(
            station_id="ISS001",
            name="International Space Station",
            crew_size=6,
            power_level=85.5,
            oxygen_level=92.3,
            last_maintenance=datetime.datetime.now()
        )
    except Exception as e:
        print(f"{e}: Parameter misconfigured")
        return
    print("Valid station created:")
    print(f"ID: {my_station.station_id}")
    print(f"Name: {my_station.name}")
    print(f"Crew: {my_station.crew_size} people")
    print(f"Power: {my_station.power_level}%")
    print(f"Last maintenance: {my_station.last_maintenance}")
    print(f"Oxygen: {my_station.oxygen_level}%")
    if my_station.is_operational is True:
        print("Status: Operational\n")
    else:
        print("Status: Not operational\n")
    print("======================================")
    print("Expected validation error:")
    try:
        my_station = SpaceStation(
            station_id="ISS00ewqrfdsfasdfasfsd1",
            name="International Space Station",
            crew_size=24,
            power_level=85.5,
            oxygen_level=92.3,
            last_maintenance=datetime.datetime.now(),
        )
    except ValidationError as e:
        for error in e.errors():
            print(f"{error['loc'][0]}: {error['msg']}")
        return


if __name__ == "__main__":
    main()
