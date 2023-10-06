from pydantic import BaseModel
from typing import List

from .point import PointModel


class GeneratePointsRequest(BaseModel):
    num_points: int


class GeneratePointsResponse(BaseModel):
    points: List[PointModel]
