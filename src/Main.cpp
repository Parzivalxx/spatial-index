#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Function to generate synthetic 2D point cloud data
//std::vector<Point> generateSyntheticData(int numPoints, double xMin, double xMax, double yMin, double yMax) {
//    std::vector<Point> data;
//    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed the random number generator
//
//    for (int i = 0; i < numPoints; ++i) {
//        Point point;
//        point.x = (static_cast<double>(std::rand()) / RAND_MAX) * (xMax - xMin) + xMin;
//        point.y = (static_cast<double>(std::rand()) / RAND_MAX) * (yMax - yMin) + yMin;
//        data.push_back(point);
//    }
//
//    return data;
//}

int main() {
    int numPoints = 1000;
    double xMin = 0.0;
    double xMax = 100.0;
    double yMin = 0.0;
    double yMax = 100.0;

    //std::vector<Point> syntheticData = generateSyntheticData(numPoints, xMin, xMax, yMin, yMax);

    //// Optionally, you can write the data to a file
    //std::ofstream outFile("synthetic_data.txt");
    //if (outFile.is_open()) {
    //    for (const Point& point : syntheticData) {
    //        outFile << point.x << " " << point.y << "\n";
    //    }
    //    outFile.close();
    //}
    //else {
    //    std::cerr << "Unable to open the output file." << std::endl;
    //    return 1;
    //}

    // Visualize the data in your preferred way (e.g., plotting library)
    // ...

    return 0;
}
