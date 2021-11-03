#include <iostream>
#include <math.h>
#define M_PI 3.1415926535
#define M_E 2.7182818284590452
#include <vector>
#include <cstdio>
#include <random>
#include <functional>
using namespace std;

random_device rd;
mt19937 gen(rd());

ostream& operator << (ostream& o, vector<double>v) {
    for (auto e : v) {
        o << e << ",";

    }
    return o;
}


vector<double> simulated_annealing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain, vector<double> p0, int iterations, function<vector<double>(vector<double>)> N, function<double(int)> T)
{
    auto currentPoint = p0;
    auto best = p0;


    uniform_real_distribution<> u_k(0.0, 1.0);

    if (!f_domain(currentPoint)) throw std::invalid_argument("The p0 point must be in domain");
    for (int k = 0; k < iterations; k++) {
        auto nextPoint = N(currentPoint);
        if (!f_domain(nextPoint)) continue;
        if (f(nextPoint) < f(currentPoint)) {
            currentPoint = nextPoint;
        }
        else {
            double u = u_k(gen);
            if (u < exp(-abs(f(nextPoint) - f(currentPoint)) / T(k))) {
                currentPoint = nextPoint;
            }
            else {

            }
        }
        if (f(currentPoint) < f(best)) {
            best = currentPoint;
        }
    }
    return best;
}

vector<double> hillClimbing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain, vector<double> p0, vector <double> distanceBetweenPoints, int iterations)
{
    auto p = p0;
    double a = distanceBetweenPoints.at(0);
    double b = distanceBetweenPoints.at(1);
    uniform_int_distribution<> distrib(0, p.size() - 1);
    uniform_real_distribution<> distrib_r(a, b);
    if (!f_domain(p)) throw std::invalid_argument("The p0 point must be in domain");
    for (int i = 0; i < iterations; i++) {
        auto p2 = p;
        p2[distrib(gen)] += distrib_r(gen);
        if (f_domain(p2)) {
            double y2 = f(p2);
            if (y2 < f(p)) {
                p = p2;
            }
        }
    }
    return p;
}

auto boothFunction = [](vector <double> v) {
    double x = v.at(0);
    double y = v.at(1);
    double results;
    results = pow((x + (2 * y) - 7), 2) + pow(((2 * x) + y - 5), 2);
    return results;
};

auto ackley = [](vector<double> v) {
    double x = v.at(0);
    double y = v.at(1);
    double results;
    results = -20 * exp(-0.2 * sqrt(0.5 * (x * x + y * y))) - exp(0.5 * (cos(2 * M_PI * x) + cos(2 * M_PI * y))) + M_E + 20.0;
    return results;
};

auto ackleyDomain = [](vector<double> v) {
    return (abs(v[0]) <= 5) && (abs(v[1]) <= 5);
};
auto boothDomain = [](vector<double> v) {
    return (abs(v[0]) <= 10) && (abs(v[1]) <= 10);
};



int main() {
    using namespace std;
    vector <double> numbers;
    int wybor;
    cout << "Wybierz funkcje optymalizacyjna: 1 = Booth 2 = Ackley ";
    cin >> wybor;
    int iteracje;
    int wybor2;
    vector <double> distanceBetweenPoints{ -0.1,0.1 };
    if (wybor == 1) {
        cout << "Podaj ilosc iteracji" << endl;
        cin >> iteracje;
        uniform_real_distribution<> distrib_r(-10, 10);
        vector<double> boothP0 = { distrib_r(gen),distrib_r(gen) };
        cout << "Wybierz algorytm : 1 = HillClimbing 2 = SimulatedAnnealing ";
        cin >> wybor2;
        if (wybor2 == 1) {
            auto result = hillClimbing(boothFunction, boothDomain, boothP0, distanceBetweenPoints, iteracje);
            cout << result << "->" << boothFunction(result) << endl;
        }
        else if (wybor2 == 2) {
                auto result = simulated_annealing(boothFunction, boothDomain, boothP0, iteracje, [](auto p) {
                    normal_distribution<double> n(0.0, 0.3);
                    for (auto& e : p) {
                        e = e + n(gen);
                    }
                    return p;
                    },
                    [](int k) { return 1000.0 / k; });
                cout << result << " -> " << boothFunction(result) << endl;
            }
 
    }
    else if (wybor == 2) {
        cout << "Podaj ilosc iteracji" << endl;
        cin >> iteracje;
        uniform_real_distribution<> distrib_r(-5, 5);
        vector<double> ackleyP0 = { distrib_r(gen),distrib_r(gen) };
        cout << "Wybierz algorytm : 1 = HillClimbing 2 = SimulatedAnnealing ";
        cin >> wybor2;
        if (wybor2 == 1) {
            auto result = hillClimbing(ackley, ackleyDomain, ackleyP0, distanceBetweenPoints, iteracje);
            cout << result << " -> " << ackley(result) << endl;
        }
        else if (wybor2 == 2) {
            auto result = simulated_annealing(ackley, ackleyDomain, ackleyP0, iteracje, [](auto p) {
                normal_distribution<double> n(0.0, 0.3);
                for (auto& e : p) {
                    e = e + n(gen);
                }
                return p;
                },
                [](int k) { return 1000.0 / k; });
            cout << result << " -> " << ackley(result) << endl;
        }
    }
    return 0;
}
