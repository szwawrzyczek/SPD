#pragma once
#include "Task.hpp"


using namespace std;


class Schrage
{
public:
	
	int Cmax; 
	int t; 	//time
	Task new_task;
	Task current_task;
	vector<Task> NOT_READY_tasks; 
	vector<Task> READY_tasks; 
	Task sequence[2000]; // if you load big data instance change 2000 
						// to greater value
	
	friend bool operator<(const Task& o1, const Task& o2);
	Schrage();
	~Schrage();
	void schrage_S();
	void schrage_ptmn();
	bool load_file(string);
	void sort();


};
