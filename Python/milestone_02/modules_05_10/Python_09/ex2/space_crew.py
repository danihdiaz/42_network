#!/usr/bin/env python3

from pydantic import BaseModel, ValidationError, model_validator, Field
from enum import Enum
from datetime import datetime


class Rank(Enum):
    cadet = "cadet"
    officer = "officer"
    lieutenant = "lieutenant"
    captain = "captain"
    commander = "commander"


class CrewMember(BaseModel):
    member_id: str = Field(min_length=3, max_length=10)
    name: str = Field(min_length=2, max_length=50)
    rank: Rank
    age: int = Field(ge=18, le=80)
    specialization: str = Field(min_length=3, max_length=30)
    years_experience: int = Field(ge=0, le=50)
    is_active: bool = True


class SpaceMission(BaseModel):
    mission_id: str = Field(min_length=5, max_length=15)
    mission_name: str = Field(min_length=3, max_length=100)
    destination: str = Field(min_length=3, max_length=50)
    launch_date: datetime
    duration_days: int = Field(ge=1, le=3650)
    crew: list[CrewMember] = Field(min_length=1, max_length=12)
    mission_status: str = "planned"
    budget_millions: float = Field(ge=1.0, le=10000.0)

    @model_validator(mode='after')
    def validator(self) -> 'SpaceMission':
        if not self.mission_id.startswith("M"):
            raise ValueError("Mission ID must start with M")
        commander = False
        captain = False
        for member in self.crew:
            if member.rank is Rank.captain:
                captain = True
            if member.rank is Rank.commander:
                commander = True
        if commander is False and captain is False:
            raise ValueError(
                "Mission must have at least one Commander or Captain")
        if self.duration_days > 365:
            experienced_members = 0
            for member in self.crew:
                if member.years_experience > 5:
                    experienced_members += 1
            if experienced_members < (len(self.crew) / 2):
                raise ValueError("Long missions need 50% experienced crew")
        for member in self.crew:
            if member.is_active is False:
                raise ValueError("All crew members must be active")
        return self


if __name__ == "__main__":
    print("Space Mission Crew Validation")
    print("=========================================")
    print("Valid Mission Created:")
    sarah = CrewMember(
        member_id="SC001",
        name="Sarah Connor",
        rank=Rank.commander,
        age=44,
        specialization="Mission Command",
        years_experience=20
    )
    john = CrewMember(
        member_id="JS002",
        name="John Smith",
        rank=Rank.lieutenant,
        age=37,
        specialization="Navigation",
        years_experience=12
    )
    alice = CrewMember(
        member_id="AJ003",
        name="Alice Johnson",
        rank=Rank.officer,
        age=32,
        specialization="Engineering",
        years_experience=9
    )
    crew_members = [sarah, john, alice]
    valid_ms = SpaceMission(
        mission_id="M2024_MARS",
        mission_name="Mars Colony Establishment",
        destination="Mars",
        launch_date=datetime.fromisoformat("2024-02-18T12:00:00"),
        duration_days=900,
        crew=crew_members,
        budget_millions=2500.0
    )
    print(f"Mission: {valid_ms.mission_name}")
    print(f"ID: {valid_ms.mission_id}")
    print(f"Destination: {valid_ms.destination}")
    print(f"Launch date: {valid_ms.launch_date}")
    print(f"Duration: {valid_ms.duration_days} days")
    print(f"Budget: ${valid_ms.budget_millions}M")
    print(f"Crew size: {len(valid_ms.crew)}")
    print("Crew members:")
    for member in crew_members:
        print(f"- {member.name} ({member.rank.value}) -"
              f" {member.specialization}")
    print("\n=========================================")
    print("Expected validation error:")
    try:
        tony = CrewMember(
            member_id="TT001",
            name="Tony Thompson",
            rank=Rank.cadet,
            age=44,
            specialization="Mission Command",
            years_experience=4
        )
        mike = CrewMember(
            member_id="MM002",
            name="Michael Morris",
            rank=Rank.lieutenant,
            age=37,
            specialization="Navigation",
            years_experience=5
        )
        holly = CrewMember(
            member_id="HH003",
            name="Holly Holmes",
            rank=Rank.officer,
            age=32,
            specialization="Engineering",
            years_experience=9
        )
        ronda = CrewMember(
            member_id="RR003",
            name="Ronda Rousey",
            rank=Rank.officer,
            age=50,
            specialization="Communications",
            years_experience=25,
        )
        bad_crew_members = [tony, mike, holly, ronda]
        invalid_ms = SpaceMission(
            mission_id="M2024_PLUTO",
            mission_name="Pluto Terrain Discovery",
            destination="Pluto",
            launch_date=datetime.fromisoformat("2024-02-18T12:00:00"),
            duration_days=900,
            crew=bad_crew_members,
            budget_millions=2500.0
        )
    except ValidationError as e:
        for error in e.errors():
            loc = error['loc'][0] if error['loc'] else "Validator error"
            print(f"{loc}: {error['msg'].replace('Value error, ', '')}")
