from main import app
from datastructs.DataManager import DataManager
from models import GeneratePointsRequest, GeneratePointsResponse, PointModel


data_manager = DataManager()


@app.post("/generate_points", response_model=GeneratePointsResponse)
async def generate_points(request_data: GeneratePointsRequest) -> GeneratePointsRequest:
    points = data_manager.generate_points(num_points=request_data.num_points)
    return {"points": [PointModel(x=point.x, y=point.y) for point in points]}
