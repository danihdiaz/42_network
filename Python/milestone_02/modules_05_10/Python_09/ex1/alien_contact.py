#!/usr/bin/env python3

from pydantic import BaseModel, Field, ValidationError, model_validator
from enum import Enum
import datetime
from typing import Optional


class ContactType(Enum):
    radio = "radio"
    visual = "visual"
    physical = "physical"
    telepathic = "telepathic"


class AlienContact(BaseModel):
    contact_id: str = Field(min_length=5, max_length=15)
    timestamp: datetime.datetime
    location: str = Field(min_length=3, max_length=100)
    contact_type: ContactType
    signal_strength: float = Field(ge=0.0, le=10.0)
    duration_minutes: int = Field(ge=1, le=1440)
    witness_count: int = Field(ge=1, le=100)
    message_received: Optional[str] = Field(default=None, max_length=500)
    is_verified: bool = False

    @model_validator(mode='after')
    def validator(self) -> 'AlienContact':
        if not self.contact_id.startswith("AC"):
            raise ValueError("Contact ID must start with AC")
        if (self.contact_type is ContactType.physical
                and self.is_verified is False):
            raise ValueError("Physical contact reports must be verified")
        if (self.contact_type is ContactType.telepathic
                and self.witness_count < 3):
            raise ValueError(
                "Telepathic contact requires at least 3 witnesses")
        if self.signal_strength >= 7.0 and self.message_received is None:
            raise ValueError("Strong signals should include received messages")
        return self


if __name__ == "__main__":
    print("Alien Contact Log Validation")
    print("=======================================")
    print("Valid contact report:")
    try:
        valid_ac = AlienContact(
            contact_id="AC_2024_001",
            timestamp=datetime.datetime.fromisoformat("2024-01-15T10:30:00"),
            location="Area 51, Nevada",
            contact_type=ContactType.radio,
            signal_strength=8.5,
            duration_minutes=45,
            witness_count=5,
            message_received="'Greetings from Zeta Reticuli'",
        )
    except ValidationError as e:
        print(e)
    print(f"ID: {valid_ac.contact_id}")
    print(f"Type: {valid_ac.contact_type.value}")
    print(f"Location: {valid_ac.location}")
    print(f"Time: {valid_ac.timestamp}")
    print(f"Signal: {valid_ac.signal_strength}/10")
    print(f"Duration: {valid_ac.duration_minutes} minutes")
    print(f"Witnesses: {valid_ac.witness_count}")
    print(f"Message: {valid_ac.message_received}")
    print("\n========================================")
    print("Expected validation error:")
    try:
        invalid_ac = AlienContact(
            contact_id="AC_2024_001",
            timestamp=datetime.datetime.fromisoformat("2024-01-15T10:30:00"),
            location="Area 51, Nevada",
            contact_type=ContactType.telepathic,
            signal_strength=5.5,
            duration_minutes=45,
            witness_count=2,
        )
    except ValidationError as e:
        for error in e.errors():
            loc = error['loc'][0] if error['loc'] else "Validator error"
            print(f"{loc}: {error['msg'].replace('Value error, ', '')}")
