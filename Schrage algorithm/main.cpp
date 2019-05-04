#include "Schrage_algorithm.hpp"
#include "Task.hpp"
#include <iostream>

using namespace std;

//if notdef;

int main()
{
    system("cls");
    cout<<endl;
    cout<<"Program rozwiazujacy problem RPQ w operciu o algorytm Schrage'a - S oraz pmtn";
    cout<<endl<<endl;

    Schrage schrage;
    schrage.load_file("in200.txt");
    schrage.schrage_S();
    schrage.schrage_ptmn();

    return 0;
}
