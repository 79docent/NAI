#include <iostream>
#include <stdlib.h>
#include <utility>      
#include <tuple>
 
int funct1 (int x){
x = 20 - abs(x);
 return x;
} 
auto funct2 = [](int i){
    int result = (2 * (i%2) - 1)*i/2;
    return result;
};
 
auto obliczenia = [](auto f1, auto f2, int n) {
    using namespace std;
    int max_x = f2(0);
    int max_y = f1(max_x);
    for (int i = 1; i < n; i++) {
        int x = f2(i);
        int y = f1(x);
        if (y > max_y) {
            max_x = x;
            max_y = y;
        }
    }
    pair <int,int> para;
   para = make_pair(max_x,max_y);

    return para;
};
 
 
int main() {
    using namespace std;
    pair <int,int> final;
    final = obliczenia(funct1,funct2,5);
    cout<<final.first<<" & "<<final.second;
}