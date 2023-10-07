from pydantic import BaseModel
from typing import List

from .point import PointModel


class RangeQueryRequest(BaseModel):
    startx: float
    starty: float
    endx: float
    endy: float
    structure_type: str


class RangeQueryResponse(BaseModel):
    points: List[PointModel]
    time_taken: int
