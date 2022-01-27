#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <tuple>
#include <vector>
using namespace std;
#include <stdlib.h>
#include <time.h>

pair<unsigned long long int, unsigned long long int> convertToPair(vector<int> wektor)
{
  unsigned long long int x = 0;
  unsigned long long int y = 0;
  for (int i = 0; i < 64; i++)
  {
    if (wektor[i] == 1)
      x += pow(2.0, i);
  }
  for (int i = 64; i < wektor.size(); i++)
  {
    if (wektor[i] == 1)
      y += pow(2.0, i - 64);
  }
  return {x, y};
}


auto ackley = [](pair<double,double> p) {
    double x = p.first;
    double y = p.second;
    double results;
    results = -20 * exp(-0.2 * sqrt(0.5 * (x * x + y * y))) - exp(0.5 * (cos(2 * M_PI * x) + cos(2 * M_PI * y))) + M_E + 20.0;
    return results;
};

vector<int> generateRandomVector(int n)
{
  vector<int> vec = {};
  srand(time(NULL));
  for (int i = 0; i < n; i++)
  {
    int randomNumber = rand() % 2;
    vec.push_back(randomNumber);
  }
  return vec;
}

int main()
{
  vector<int> numbers = generateRandomVector(128);
  pair<unsigned long long int, unsigned long long int> para = convertToPair(numbers);
  cout << "Pary: " << endl;
  cout << para.first << endl;
  cout << para.second << endl;
  pair<double, double> para2 = {
  ((double(para.first) / INT64_MAX) - 1) * 5, ((double(para.second) / INT64_MAX) - 1) * 5
  };
  cout<<para2.first<<endl;
  cout<<para2.second<<endl;
  cout<<ackley(para2);
  cout << endl;
}