#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>

using namespace std;

using point2d = std::array<double, 2>;

inline point2d operator+(const point2d a, const point2d b){
    return {a[0] + b[0], a[1] + b[1]};
}

inline point2d operator*(const point2d a, const double b){
    return {a[0] * b, a[1] * b};
}

inline point2d operator-(const point2d a, const point2d b){
    return a + (b * -1.0);
}

inline point2d operator%(const point2d a, const point2d b){
    return {a[0] * b[0], a[1] * b[1]};
}

inline double operator*(const point2d a, const point2d b){
    auto r = a % b;
    return std::accumulate(r.begin(), r.end(), 0.0);
}

inline double length(const point2d a){
    return std::sqrt(a * a);
}

inline double length(const point2d a, const point2d b){ 
    return std::sqrt(a * b);
}

inline std::ostream& operator<<(std::ostream& o, const point2d a){
    o << a[0] << " " << a[1];
    return o;
}

point2d derivative(std::function<double(point2d)> f, point2d x, double d = 1.52588e-05){ 
    point2d dx = {d, 0.0}; 
    point2d dy = {0.0, d};

    return {
        (f(x+dx*0.5)-f(x-dx*0.5))/d,
        (f(x+dy*0.5)-f(x-dy*0.5))/d
    };
}

double minDistance(point2d v, point2d w, point2d p){
    pair<double, double> vw;
    vw.first = w[0] - v[0];
    vw.second = w[1] - v[1];

    pair<double, double> wp;
    wp.first = p[0] - w[0];
    wp.second = p[1] - w[1];

    pair<double, double> vp;
    vp.first = p[0] - v[0],
    vp.second = p[1] - v[1];

    double vw_wp, vw_vp;

    vw_wp = (vw.first * wp.first + vw.second * wp.second);
    vw_vp = (vw.first * vp.first + vw.second * vp.second);

    double reqAns = 0.0;

    if (vw_wp > 0) {
        double y = p[1] - w[1];
        double x = p[0] - w[0];
        reqAns = sqrt(x * x + y * y);
    } else if (vw_vp < 0) {
        double y = p[1] - v[1];
        double x = p[0] - v[0];
        reqAns = sqrt(x * x + y * y);
    } else {
        double x1 = vw.first;
        double y1 = vw.second;
        double x2 = vp.first;
        double y2 = vp.second;
        double mod = sqrt(x1 * x1 + y1 * y1);
        reqAns = abs(x1 * y2 - y1 * x2) / mod;
    }
    return reqAns;
}

int main(int argc, char** argv){

    point2d destination = {0.0, 0.0}; 
    point2d currentPosition = {10.0, 1.0}; 
    double velocity = 0.1;
    double acceleration = 0.1;

    std::vector<std::pair<point2d, double>> obstacles = {}; 

    obstacles.push_back({{2.4,3.8},(argc>1)?std::stod(argv[1]):1.0});
    obstacles.push_back({{10,-8},(argc>1)?std::stod(argv[1]):1.0}); 

    auto field = [&](point2d p) -> double { 
        double obstacleField = 0; 
        double distanceToObstacle = minDistance(obstacles[0].first, obstacles[1].first, p); 
        obstacleField += obstacles[0].second/ (distanceToObstacle*distanceToObstacle);
        return length(destination - p) + obstacleField;
    };

    point2d currentVelocity = {0.0, 0.0};


    for (int i = 0; i < 1000; i++) {
        point2d dp = derivative(field, currentPosition); 
        dp = dp * (1.0 / length(dp)); 
        dp = dp * acceleration; 

        currentVelocity = currentVelocity - dp;
        if (length(currentVelocity) > velocity) currentVelocity = (currentVelocity * (1.0 / (length(currentVelocity))))*velocity;
        currentPosition = currentPosition + currentVelocity;
        std::cout << currentPosition << std::endl;
    }
    return 0;
}