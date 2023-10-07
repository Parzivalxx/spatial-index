from fastapi import FastAPI, HTTPException

from datastructs.DataManager import DataManager
from models import (
    GeneratePointsRequest,
    GeneratePointsResponse,
    RangeQueryRequest,
    RangeQueryResponse,
    KnnQueryRequest,
    KnnQueryResponse,
    PointModel,
)


app = FastAPI()

data_manager = DataManager()


@app.post("/generate_points", response_model=GeneratePointsResponse)
async def generate_points(
    request_data: GeneratePointsRequest,
) -> GeneratePointsResponse:
    try:
        points = data_manager.generate_points(num_points=request_data.num_points)
        return GeneratePointsResponse(
            points=[PointModel(x=point.x, y=point.y) for point in points]
        )
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))


@app.get("/range_query", response_model=RangeQueryResponse)
async def range_query(request_data: RangeQueryRequest):
    try:
        points, time_taken = data_manager.range_query(
            startx=request_data.startx,
            starty=request_data.starty,
            endx=request_data.endx,
            endy=request_data.endy,
            structure_type=request_data.structure_type,
        )
        points = [PointModel(x=point.x, y=point.y) for point in points]
        return RangeQueryResponse(points=points, time_taken=int(time_taken))
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))


@app.get("/knn_query", response_model=KnnQueryResponse)
async def knn_query(request_data: KnnQueryRequest):
    try:
        points, time_taken = data_manager.knn_query(
            queryx=request_data.queryx,
            queryy=request_data.queryy,
            k=request_data.k,
            structure_type=request_data.structure_type,
        )
        points = [PointModel(x=point.x, y=point.y) for point in points]
        return KnnQueryResponse(points=points, time_taken=int(time_taken))
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))
