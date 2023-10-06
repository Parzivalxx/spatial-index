#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "BruteForce.h"
#include "KDTree.h"
#include "Quadtree.h"
#include "Point.h"
#include "Utils.h"
#include "SpatialIndex.h"

namespace py = pybind11;

PYBIND11_MODULE(spatial_index, m) {
    py::class_<SpatialIndex>(m, "SpatialIndex");

    py::class_<Point>(m, "Point")
        .def(py::init<double, double>())
        .def_readwrite("x", &Point::x)
        .def_readwrite("y", &Point::y);

    py::class_<BruteForce, SpatialIndex>(m, "BruteForce")
        .def(py::init<const std::vector<Point>&>())
        .def("range_query", &BruteForce::rangeQuery)
        .def("knn_query", &BruteForce::knnQuery);

    py::class_<KDTree, SpatialIndex>(m, "KDTree")
        .def(py::init<>())
        .def("build", &KDTree::build)
        .def("range_query", [](KDTree &self, double startX, double startY, double endX, double endY) {
            return self.rangeQuery(startX, startY, endX, endY);
        })
        .def("knn_query", &KDTree::knnQuery);

    py::class_<Quadtree, SpatialIndex>(m, "Quadtree")
        .def(py::init<double, double, double, double>())
        .def("build", &Quadtree::build)
        .def("range_query", &Quadtree::rangeQuery)
        .def("knn_query", &Quadtree::knnQuery);

    m.def("generate_synthetic_data", &generateSyntheticData);
}
