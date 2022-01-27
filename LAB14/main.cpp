#include "iostream"
#include "vector"
#include "string"

using namespace std;

pair<string, bool> decide(vector<string> decisionToMake){
    pair<string, bool> decision;
    string day = decisionToMake.at(0);
    string outlook = decisionToMake.at(1);
    string temperature = decisionToMake.at(2);
    string humidity = decisionToMake.at(3);
    string wind = decisionToMake.at(4);

    decision.first = day; // punkt wejscia

    if (outlook == "Overcast"){
        decision.second = true;
        return decision;
    } else if (outlook == "Sunny"){
        if (humidity == "High"){
            decision.second = false;
            return decision;
        } else {
           decision.second = true;
            return decision;
        }
    } else {
        if (wind == "Strong"){
            decision.second = false;
            return decision;
        } else {
            decision.second = true;
            return decision;
        }
    }
}

int main(int argc, char* argv[]){
    vector<vector<string>> decisionsToMake = {
            {"D1", "Sunny", "Hot", "High", "Weak"},
            {"D2", "Sunny", "Hot", "High", "Strong"},
            {"D3", "Overcast", "Hot", "High", "Weak"},
            {"D4", "Rain", "Mild", "High", "Weak"},
            {"D5", "Rain", "Cool", "Normal", "Weak"},
            {"D6", "Rain", "Cool", "Normal", "Strong"},
            {"D7", "Overcast", "Cool", "Normal", "Strong"},
            {"D8", "Sunny", "Mild","High", "Weak"},
            {"D9", "Sunny", "Cool", "Normal", "Weak"},
            {"D10", "Rain", "Mild", "Normal", "Weak"},
            {"D11", "Sunny", "Mild", "Normal", "Strong"},
            {"D12", "Overcast", "Mild", "High", "Strong"},
            {"D13", "Overcast", "Hot","Normal", "Weak"},
            {"D14", "Rain", "Mild", "High", "Strong"}
    };

    pair<string, bool> decision;
    for (auto &item : decisionsToMake){
        decision = decide(item);
        cout << decision.first << " : ";
        decision.second ? cout << "yes" : cout << "no";
        cout << "\n";
    }

    return 0;
}