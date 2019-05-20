#include <iostream>
#include "Carlier.hpp"
 
int n=0;
int main() {
    int C = INFINITY;
	Carlier carlier_object;
    int CMAX_result=0;
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"Program realizujacy rozwiazanie problemu RPQ wg algorytmu Carliera"<<endl;
    cout<<"------------------------------------------------------------------\n\n"<<endl;
	carlier_object.loadData("in100.txt");
    CMAX_result=carlier_object.Carlier_Algorithm(C);

	//system("PAUSE");
}