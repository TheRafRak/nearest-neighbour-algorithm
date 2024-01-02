#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <iomanip> 

struct Point {
    char name;
    double x, y;
    
    bool operator==(const Point& other) const {
        return name == other.name;
    }
};

double distance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

int main() {
    int numPoints;
    std::cout << "Enter the number of points: ";
    std::cin >> numPoints;

    std::vector<Point> points;
    
    for (int i = 0; i < numPoints; i++) {
        Point point;
        std::cout << "Enter the name of the point: ";
        std::cin >> point.name;
        std::cout << "Enter the coordinate x: ";
        std::cin >> point.x;
        std::cout << "Enter the coordinate y: ";
        std::cin >> point.y;
        points.push_back(point);
    }

    char startPointName;
    std::cout << "Enter the name of the starting point: ";
    std::cin >> startPointName;

    Point start;
    for (const Point& p : points) {
        if (p.name == startPointName) {
            start = p;
            break;
        }
    }

    std::vector<Point> tour;
    tour.push_back(start);

    while (tour.size() < points.size()) {
        double minDist = std::numeric_limits<double>::max();
        Point nearestPoint;

        for (const Point& p : points) {
            if (std::find(tour.begin(), tour.end(), p) == tour.end() && p.name != start.name) {
                double dist = distance(tour.back(), p);
                if (dist < minDist) {
                    minDist = dist;
                    nearestPoint = p;
                }
            }
        }

        tour.push_back(nearestPoint);
    }

    tour.push_back(start);

    double totalDistance = 0.0;
    for (size_t i = 0; i < tour.size() - 1; i++) {
        totalDistance += distance(tour[i], tour[i + 1]);
    }

    std::cout << "The shortest route: ";
    for (const Point& p : tour) {
        std::cout << p.name << " ";
    }
    std::cout << "\nRoute length: " << std::fixed << std::setprecision(2) << totalDistance << std::endl;

    return 0;
}