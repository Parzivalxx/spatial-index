import os
from setuptools import setup, Extension

cpp_source_files = [
    "Point.cpp",
    "Quadtree.cpp",
    "QuadtreeNode.cpp",
    "KDTree.cpp",
    "BruteForce.cpp",
    "ExportToPy.cpp",
]

ext_modules = [
    Extension(
        "spatial_index",
        sources=[os.path.join("../cpp/src", filename) for filename in cpp_source_files],
        include_dirs=["./.venv/Lib/site-packages/pybind11/include"],
    )
]

setup(
    name="spatial_index",
    version="1.0.0",
    ext_modules=ext_modules,
)
