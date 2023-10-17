import pytest
from fastapi.testclient import TestClient

from src.main import app


@pytest.fixture
def client():
    return TestClient(app)

def test_generate_points(client):
    request_data = {
        "num_points": 10
    }

    response = client.post("/generate_points", json=request_data)

    assert response.status_code == 200

    data = response.json()
    assert "points" in data

def test_range_query(client):
    request_data = {
        "startx": 0,
        "starty": 0,
        "endx": 10,
        "endy": 10,
        "structure_type": "quadtree"
    }

    response = client.post("/range_query", json=request_data)

    assert response.status_code == 200

    data = response.json()
    assert "points" in data
    assert "time_taken" in data

def test_knn_query(client):
    request_data = {
        "queryx": 5,
        "queryy": 5,
        "k": 5,
        "structure_type": "quadtree"
    }

    response = client.post("/knn_query", json=request_data)

    assert response.status_code == 200

    data = response.json()
    assert "points" in data
    assert "time_taken" in data

