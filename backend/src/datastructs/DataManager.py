from typing import List
import spatial_index
from spatial_index import Quadtree, KDTree, BruteForce, Point


class DataManager:
    def __init__(
        self,
        xmin: float = 0,
        xmax: float = 100,
        ymin: float = 0,
        ymax: float = 100,
    ) -> None:
        self.points = []
        self.quadtree = Quadtree(xmin, ymin, xmax, ymax)
        self.kdtree = KDTree()
        self.bruteforce = BruteForce(self.points)

    def generate_points(
        self,
        num_points: int,
        xmin: float = 0,
        xmax: float = 100,
        ymin: float = 0,
        ymax: float = 100,
    ) -> List[Point]:
        self.points = spatial_index.generate_synthetic_data(
            num_points, xmin, xmax, ymin, ymax
        )
        self.quadtree = Quadtree(xmin, ymin, xmax, ymax)
        self.quadtree.build(self.points)
        self.kdtree = KDTree()
        self.kdtree.build(self.points)
        return self.points
