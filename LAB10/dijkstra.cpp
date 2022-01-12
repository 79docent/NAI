#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


 vector <vector<int>>  getFile(string file) {

    int connected_points[2];

    ifstream txtFileGraph(file);
    vector <vector<int>> listOfPairs; 

    while (txtFileGraph.eof() == false) { 

       for (int i = 0; i < 2 ; i++ ) { 
       txtFileGraph >> connected_points[i];
       }
       vector <int> connections; 

    for (int i = 0; i < 2 ; i++ ) {  
       connections.push_back(connected_points[i]); 
    }
       listOfPairs.push_back(connections); 
    }
       listOfPairs.pop_back(); 

       return listOfPairs; 
}

int main () {

    vector <vector<int>> pairsFromTxtFile = getFile("graph.txt"); 
    ofstream dotFileGraph ("graph.dot"); 

    dotFileGraph << "digraph finite_state_machine {" << endl; 

    for (int i = 0; i <= pairsFromTxtFile.size(); i++) { 
        dotFileGraph << pairsFromTxtFile[i][0] << " -> " << pairsFromTxtFile[i][1]<< "[ label = \"infinity\" ] [color=\"green\"];" << endl; 
    }
    dotFileGraph << "}"; 

    return 0;
}