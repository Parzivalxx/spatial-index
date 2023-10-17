from src.datastructs.DataManager import DataManager


def test_generate_points():
    data_manager = DataManager()
    num_points = 10

    points = data_manager.generate_points(num_points)

    assert len(points) == num_points

def test_range_query():
    data_manager = DataManager()
    data_manager.generate_points(100)

    startx, starty, endx, endy = 10, 10, 20, 20
    structure_type = "quadtree"

    points, time_taken = data_manager.range_query(startx, starty, endx, endy, structure_type)

    assert len(points) >= 0
    assert isinstance(time_taken, float)

def test_knn_query():
    data_manager = DataManager()
    data_manager.generate_points(100)

    queryx, queryy, k = 10, 10, 5
    structure_type = "quadtree"

    # Call the knn_query method
    points, time_taken = data_manager.knn_query(queryx, queryy, k, structure_type)

    assert len(points) >= 0
    assert isinstance(time_taken, float)
