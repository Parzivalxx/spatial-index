from pydantic import BaseModel


class PointModel(BaseModel):
    x: float
    y: float
