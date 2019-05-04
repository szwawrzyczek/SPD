#pragma once
#include "Schrage_algorithm.hpp"


using namespace std;
int n;


Schrage::Schrage() : Cmax(0), t(0){}
Schrage::~Schrage() {}

void Schrage::schrage_S() {
	
	Task tmp; 
	int i = 1; 
	this->sort();	//sort sequence by R (for second while loop warning)
	t = sequence[0].r; 
	Cmax = 0; 
	this->sort();
	for (i = 0; i < n; i++) {
		NOT_READY_tasks.push_back(sequence[i]);
	}

	while (!(READY_tasks.empty()) || !(NOT_READY_tasks.empty()))
	{

		while (!(NOT_READY_tasks.empty()) && (NOT_READY_tasks.front().r <= t))
		{
			tmp = NOT_READY_tasks.front(); // smallest R task
			READY_tasks.push_back(tmp); // avalible
			NOT_READY_tasks.erase(NOT_READY_tasks.begin()); 
		}
		if ((READY_tasks.empty())) 
		{
			t = NOT_READY_tasks.front().r; // jump to next task
		}
		else {
				// searching max q from ready tasks
			int tmp_max_q=0;
			int iter=0;
			for( unsigned int k=0; k<READY_tasks.size(); k++)
			{	
				if(READY_tasks[k].q > tmp_max_q){
					tmp_max_q=READY_tasks[k].q;
					iter=k;
				}
			}

			tmp = READY_tasks[iter]; // current task

			sequence[i] = tmp; // add to sequence
			READY_tasks.erase(READY_tasks.begin()+iter); // delete from ready tasks
			t += sequence[i].p; // jump to end of process time
			
			Cmax = max(Cmax, t + sequence[i].q);  

			
			i++; 
		}

	} // while empty(dost) || empty(niedost)
	
	cout << "Kolejnosc zadan algorytmu schrage'a (S) : \n" << endl;
	for (i = 0; i < n; i++)
	{
		cout << sequence[i];
	}
	cout <<endl<< "Cmax algorytmu schrege'a (S) : " << Cmax<< endl;
} 


 void Schrage::schrage_ptmn() {
	
	current_task.p = 0; current_task.q = 0;
	int i = 0; 
	this->sort();	
	t = sequence[0].r; 
	Cmax = 0; 
	
	for (i = 0; i < n; i++) {
		NOT_READY_tasks.push_back(sequence[i]);
	}
	while (!(empty(READY_tasks)) || !(empty(NOT_READY_tasks)))
	{

		while (!(NOT_READY_tasks.empty()) && (NOT_READY_tasks.front().r <= t))
		{
			new_task = NOT_READY_tasks.front(); // task with smallest R
			READY_tasks.push_back(new_task); // now avalible
			NOT_READY_tasks.erase(NOT_READY_tasks.begin()); // erese frome not ready tasks

			if (new_task.q > current_task.q)  
			{
				current_task.p = t - new_task.r; // substruct done time amount
				t = new_task.r; // new task R to do
				if (current_task.p > 0) // if still doing
				{
					READY_tasks.push_back(current_task); 
				}
			}
		}
		if (READY_tasks.empty()) 
		{
			t = NOT_READY_tasks.front().r; // go to next task
		}
		else // if sth is doing
		{
			int tmp_max_q=0;
			int iter=0;
			for( unsigned int k=0; k<READY_tasks.size(); k++)
			{			// searching max q from ready tasks
				if(READY_tasks[k].q > tmp_max_q){
					tmp_max_q=READY_tasks[k].q;
					iter=k;
				}
			}

			new_task = READY_tasks[iter]; 
			READY_tasks.erase(READY_tasks.begin()+iter); // erese if done
			current_task = new_task;
			t = t + new_task.p; // go to end moment 
			Cmax = max(Cmax, t + new_task.q); // check which greater
		}
		
	} // while empty(dost) || empty(niedost)
	cout <<endl<< "Cmax algorytmu schrege'a (ptmn) : " << Cmax<<endl<<endl;
}

bool Schrage::load_file(std::string nazwaPliku) 
{
	int i = 0; 

	ifstream plik; 
	plik.open(nazwaPliku.c_str());
	if (!plik.good()) 
		return false;
	plik >> n;
	cout << "Liczba zadan: " << n << endl;

	for (i = 0; i < n; i++)
	{
		plik >> sequence[i].r >> sequence[i].p >> sequence[i].q; // row load
		sequence[i].nr = i + 1;
	}

	return true;
}

void Schrage::sort() { 
	
	int i = 0;
	Task tmp;
	int temp = n;
	while (n--) {
		for (i = 0; i < n; i++)
		{
			if (sequence[i].r > sequence[i + 1].r)
			{
				tmp = sequence[i];
				sequence[i] = sequence[i + 1];
				sequence[i + 1] = tmp;
			}
		}
	}
	n = temp;	
}
