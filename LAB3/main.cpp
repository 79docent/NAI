#include <iostream>
#include <math.h>
#include <vector>
#include <cstdio>
#include <random>
#include <functional>
#include <fstream>
using namespace std;

random_device rd;
mt19937 gen(rd());

ostream& operator << (ostream& o, vector<double>v) {
    for (auto e : v) {
        o << e << ",";
    }
    return o;
}

auto booth_function = [](vector <double> v) {
    double x = v.at(0);
    double y = v.at(1);

  return pow((x + 2 * y - 7), 2) + pow((2 * x + y - 5), 2);
};

auto himmelblau_function = [](vector <double> v) {
    double x = v.at(0);
    double y = v.at(1);

    return  pow((pow(x, 2) + y - 11), 2) + pow((x + pow(y, 2) - 7), 2);
};

auto booth_domain = [](vector<double> v) {
    return (abs(v[0]) <= 10) && (abs(v[1]) <= 10);
};

auto himmelblau_domain = [](vector<double> v) {
    return (abs(v[0]) <= 5) && (abs(v[1]) <= 5);
};


vector<double> simulated_annealing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain, vector<double> p0, int iterations, ofstream &out,function<vector<double>(vector<double>)> N, function<double(int)> T)
{
    auto currentPoint = p0;
    auto best = p0;


    uniform_real_distribution<> u_k(0.0, 1.0);

    if (!f_domain(currentPoint)) throw std::invalid_argument("The p0 musi byc w dziedzinie");
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
        out<<k<<" "<<f(currentPoint)<<endl;
    }
    return best;
}

vector<double> hill_climbing(function<double(vector<double>)> f, function<bool(vector<double>)> f_domain,ofstream &out, vector<double> p0, vector <double> distanceBetweenPoints, int iterations)
{
    auto p = p0;
    double a = distanceBetweenPoints.at(0);
    double b = distanceBetweenPoints.at(1);
    uniform_int_distribution<> distrib(0, p.size() - 1);
    uniform_real_distribution<> distrib_r(a, b);
    if (!f_domain(p)) throw std::invalid_argument("The p0 musi byc w dziedzinie");
    for (int i = 0; i < iterations; i++) {
        auto p2 = p;
        p2[distrib(gen)] += distrib_r(gen);
        if (f_domain(p2)) {
            double y2 = f(p2);
            if (y2 < f(p)) {
                p = p2;
            }
        }
                out<<i<<" "<<f(p)<<endl;

    }
    return p;
}

int main() {
    
    ofstream outfile("file.txt");
    ofstream outfile2("file2.txt");
    ofstream outfile3("file3.txt");
    ofstream outfile4("file4.txt");


    int iterations;
    vector <double> distanceBetweenPoints{ -0.1,0.1 };
        cout << "Podaj ilosc iteracji: " << endl;
        cin >> iterations;
        uniform_real_distribution<> distrib_r(-10, 10);
        vector<double> boothP0 = { distrib_r(gen),distrib_r(gen) };
        
            auto result1 = hill_climbing(booth_function, booth_domain,outfile, boothP0, distanceBetweenPoints, iterations);
            cout << "Hillclimb dla funkcji Bootha: " <<result1 << "->" << booth_function(result1) << endl;
        
                auto result2 = simulated_annealing(booth_function, booth_domain, boothP0, iterations, outfile2,[](auto p) {
                    normal_distribution<double> n(0.0, 0.3);
                    for (auto& e : p) {
                        e = e + n(gen);
                    }
                    return p;
                    },
                    [](int k) { return 1000.0 / k; });
                cout << "Wyzarzanie dla funkcji Bootha: " << result2 << " -> " << booth_function(result2) << endl;
            
        uniform_real_distribution<> distrib_r2(-5, 5);
        vector<double> ackleyP0 = { distrib_r2(gen),distrib_r2(gen) };
        
            auto result3 = hill_climbing(himmelblau_function, himmelblau_domain,outfile3,ackleyP0, distanceBetweenPoints, iterations);
            cout << "Hillclimb dla funkcji Himmelblau: " << result3 << " -> " << himmelblau_function(result3) << endl;
       
            auto result4 = simulated_annealing(himmelblau_function, himmelblau_domain, ackleyP0, iterations, outfile4,[](auto p) {
                normal_distribution<double> n(0.0, 0.3);
                for (auto& e : p) {
                    e = e + n(gen);
                }
                return p;
                },
                [](int k) { return 1000.0 / k; });
            cout << "Wyzarzanie dla funkcji Himmelblau: " << result4 << " -> " << himmelblau_function(result4) << endl;
       
    return 0;
}