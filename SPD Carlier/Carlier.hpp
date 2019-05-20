#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <string>


extern int n;
#define INFINITY 100000000
using namespace std;

class Task {
public:
	int n;		//numer Task_vec
	int r;      //termin dostepnosci
	int p;		//czas trwania Task_vec
	int q;		//czas dostarczenia
};


class Carlier {
	int a = -1, b = -1, c = -1;
	vector<Task> Task_vec;
	vector<int> TimeTask_vec;
	vector<int> Sequence_vec;

	struct Sort_Q {
		bool operator()(const Task& a, const Task& b) {
			if (a.q<b.q)
				return true;
			else
				return false;
		}
	};

	struct Sort_R {
		bool operator()(const Task& a, const Task& b) {
			if (a.r>b.r)
				return true;
			else
				return false;
		}
	};

public:
	int getTimeTask_vec(int n)
    {
		return TimeTask_vec[n];
	}
    Task getTask_vec(int n)
    {
		return Task_vec[n];
	}
    int getSequence_vec(int n)
    {
		return Sequence_vec[n];
	}
	void loadData(vector<Task> kopiowaneTask) 
    {
		Task_vec = kopiowaneTask;
	}
	void loadData(string filename);
	int Schrage_S() ;
	int Schrage_PTMN();
    void get_b(int C_max);
    void get_a(int C_max);
    void get_c();
	int find_Rprim() ;
	int find_Qprim();
	int find_Pprim() ;
	int Carlier_Algorithm(int UB) ;

};