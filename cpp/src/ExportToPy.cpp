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
        .def(py::init<double, double>(), py::arg("x"), py::arg("y"))
        .def_readwrite("x", &Point::x)
        .def_readwrite("y", &Point::y);

    py::class_<BruteForce, SpatialIndex>(m, "BruteForce")
        .def(py::init<>())
        .def("build", &BruteForce::build, py::arg("points"))
        .def("range_query", &BruteForce::rangeQuery, py::arg("startx"), py::arg("starty"), py::arg("endx"), py::arg("endy"))
        .def("knn_query", &BruteForce::knnQuery, py::arg("queryx"), py::arg("queryy"), py::arg("k"));

    py::class_<KDTree, SpatialIndex>(m, "KDTree")
        .def(py::init<>())
        .def("build", &KDTree::build, py::arg("points"))
        .def("range_query", [](KDTree &self, double startX, double startY, double endX, double endY) {
            return self.rangeQuery(startX, startY, endX, endY);
        }, py::arg("startx"), py::arg("starty"), py::arg("endx"), py::arg("endy"))
        .def("knn_query", &KDTree::knnQuery, py::arg("queryx"), py::arg("queryy"), py::arg("k"));

    py::class_<Quadtree, SpatialIndex>(m, "Quadtree")
        .def(py::init<double, double, double, double>(), py::arg("xmin"), py::arg("ymin"), py::arg("xmax"), py::arg("ymax"))
        .def("build", &Quadtree::build, py::arg("points"))
        .def("range_query", &Quadtree::rangeQuery, py::arg("startx"), py::arg("starty"), py::arg("endx"), py::arg("endy"))
        .def("knn_query", &Quadtree::knnQuery, py::arg("queryx"), py::arg("queryy"), py::arg("k"));

    m.def("generate_synthetic_data", &generateSyntheticData,
        py::arg("num_points"),
        py::arg("xmin"),
        py::arg("xmax"),
        py::arg("ymin"),
        py::arg("ymax"));
}
