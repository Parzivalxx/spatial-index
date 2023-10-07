from pydantic import BaseModel
from typing import List

from .point import PointModel


class KnnQueryRequest(BaseModel):
    queryx: float
    queryy: float
    k: int
    structure_type: str


class KnnQueryResponse(BaseModel):
    points: List[PointModel]
    time_taken: int
