from typing import List, Tuple
import time
import spatial_index
from spatial_index import Quadtree, KDTree, BruteForce, Point


class DataManager:
    def __init__(self) -> None:
        self.points = []
        self.quadtree = Quadtree(xmin=0.0, ymin=0.0, xmax=100.0, ymax=100.0)
        self.kdtree = KDTree()
        self.bruteforce = BruteForce()

    def generate_points(
        self,
        num_points: int,
    ) -> List[Point]:
        self.points = spatial_index.generate_synthetic_data(
            num_points=num_points, xmin=0, xmax=100, ymin=0, ymax=100
        )
        self.quadtree = Quadtree(xmin=0, ymin=0, xmax=100, ymax=100)
        self.quadtree.build(self.points)
        self.kdtree = KDTree()
        self.kdtree.build(self.points)
        self.bruteforce = BruteForce()
        self.bruteforce.build(points=self.points)
        return self.points

    def range_query(
        self,
        startx: float,
        starty: float,
        endx: float,
        endy: float,
        structure_type: str,
    ) -> Tuple[List[Point], float]:
        time_taken = 0
        points = []
        if structure_type == "quadtree":
            start_time = time.perf_counter()
            points = self.quadtree.range_query(
                startx=startx, starty=starty, endx=endx, endy=endy
            )
            end_time = time.perf_counter()
        elif structure_type == "kdtree":
            start_time = time.perf_counter()
            points = self.kdtree.range_query(
                startx=startx, starty=starty, endx=endx, endy=endy
            )
            end_time = time.perf_counter()
        elif structure_type == "bruteforce":
            print("HERE")
            start_time = time.perf_counter()
            points = self.bruteforce.range_query(
                startx=startx, starty=starty, endx=endx, endy=endy
            )
            end_time = time.perf_counter()
            print("HERE1")
        time_taken = (end_time - start_time) * 10**6
        return points, time_taken

    def knn_query(
        self,
        queryx: float,
        queryy: float,
        k: int,
        structure_type: str,
    ) -> Tuple[List[Point], float]:
        time_taken = 0
        points = []
        if structure_type == "quadtree":
            start_time = time.perf_counter()
            points = self.quadtree.knn_query(queryx=queryx, queryy=queryy, k=k)
            end_time = time.perf_counter()
        elif structure_type == "kdtree":
            start_time = time.perf_counter()
            points = self.kdtree.knn_query(queryx=queryx, queryy=queryy, k=k)
            end_time = time.perf_counter()
        elif structure_type == "bruteforce":
            start_time = time.perf_counter()
            points = self.bruteforce.knn_query(queryx=queryx, queryy=queryy, k=k)
            end_time = time.perf_counter()
        time_taken = (end_time - start_time) * 10**6
        return points, time_taken
