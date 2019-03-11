//#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include "stdafx.h"


std::vector<std::vector<int>> matrix;
std::vector<std::vector<int>> data2 = { { 4, 5 },{ 4, 1 },{ 10, 4 },{ 6, 10 },{ 2, 3 } };
//std::vector<std::vector<int>> data4 = { { 4, 5 },{ 4, 1 },{ 10, 4 },{ 6, 10 },{ 2, 3 } };
std::vector<std::vector<int>> data3 = { { 5, 5, 3 },{ 4, 5, 2 },{ 4, 4, 5 },{ 3, 5, 7 } };

void printArr(int a[], int n)
{
	for (int i = 0; i<n; i++)
		std::cout << a[i] << " ";
	std::cout << std::endl;
}


std::vector<int> add_array_to_list(int arr[], int n)
{
	std::vector<int> row;
	row.push_back(0);
	for (int i = 0; i<n; i++)
		row.push_back(arr[i]);
	return row;
}


void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


void permutation(int *arr, int start, int end)
{
	if (start == end)
	{
		matrix.push_back(add_array_to_list(arr, end + 1));
		return;
	}
	int i;
	for (i = start; i <= end; i++)
	{
		swap((arr + i), (arr + start));
		permutation(arr, start + 1, end);
		swap((arr + i), (arr + start));

	}
}

int count_time(std::vector<std::vector<int>> table)
{
	int machines = table[0].size();
	int jobs = table.size();

	std::vector<std::vector<int>> c_time(jobs, std::vector<int>(machines, 0));

	for (int j = 0; j<jobs; j++)
	{
		for (int m = 0; m<machines; m++)
		{
			if (j == 0)
			{
				for (int i = 0; i <= m; i++)
				{
					c_time[j][m] += table[j][i];
				}
				//std::cout<<"1\t";
				//std::cout<<c_time[j][m]<<"| J:"<<j<<"| M:"<<m<<"\n";
			}
			else if (m == 0)
			{
				for (int i = 0; i <= j; i++)
				{
					c_time[j][m] += table[i][m];
				}
				//std::cout<<"2\t";
				//std::cout<<c_time[j][m]<<"| J:"<<j<<"| M:"<<m<<"\n";
			}
			else
			{
				c_time[j][m] = std::max(c_time[j][m - 1], c_time[j - 1][m]) + table[j][m];
				//std::cout<<"3\t";
				//std::cout<<c_time[j][m]<<"| J:"<<j<<"| M:"<<m<<"\n";
			}

		}
	}
	return(c_time[jobs - 1][machines - 1]);
}


void print_matrix()
{
	for (int i = 0; i < matrix.size(); i++)
	{
		std::cout << i << ")\t";
		for (int j = 0; j < matrix[i].size(); j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void print_matrix_universal(std::vector<std::vector<int>> tmp_matrix)
{
	for (int i = 0; i < tmp_matrix.size(); i++)
	{
		std::cout << i << ")\t";
		for (int j = 0; j < tmp_matrix[i].size(); j++)
		{
			std::cout << tmp_matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

std::vector<std::vector<int>> combination_to_jobs(std::vector<int> combination)
{
	std::vector<std::vector<int>> ready_to_count;
	for (int i = 0; i<combination.size(); i++)
	{
		ready_to_count.push_back(data2[combination[i]]);
	}
	return ready_to_count;

}

std::vector<std::vector<int>> combination_to_jobs(std::vector<int> combination, std::vector<std::vector<int>> tmp)
{
	std::vector<std::vector<int>> ready_to_count;
	for (int i = 0; i<combination.size(); i++)
	{
		ready_to_count.push_back(tmp[combination[i]]);
	}
	return ready_to_count;

}

void all_combination_c_time()
{
	for (int i = 0; i<matrix.size(); i++)
	{
		std::vector<int> tmp_vec = std::vector<int>(matrix[i].begin() + 1, matrix[i].end());
		matrix[i][0] = count_time(combination_to_jobs(tmp_vec));
	}

}

void find_min_cmax() 
{
	int smallest = matrix[0][0];
	for (int i = 1; i < matrix.size(); ++i)
		if (matrix[i][0] < smallest)
			smallest = matrix[i][0];

	std::cout << "Min Cmax value: " << smallest << '\n';

}

int** convert_data(std::vector<std::vector<int>> arr)
{
	int machines = arr[0].size();
	int jobs = arr.size();
	//std::cout << machines << '/t' << jobs << std::endl;
	int** tmp;
	tmp = new int*[jobs];
	for (int i = 0; i < jobs; i++) {
		tmp[i] = new int[machines];
	}
	for (int i = 0; i < jobs; i++)
	{
		for (int j = 0; j < machines; j++)
		{
			tmp[i][j] = arr[i][j];
			//std::cout << tmp[i][j] << " ";
		}
		//std::cout << "\n";

	}
	return tmp;
}

int** reduce_col(std::vector<std::vector<int>> arr)
{
	int machines = arr[0].size();
	int jobs = arr.size();
	int** tmp;
	tmp = new int*[jobs];
	for (int i = 0; i < jobs; i++) {
		tmp[i] = new int[machines];
	}
	for (int i = 0; i < jobs; i++)
	{
		tmp[i][0] = arr[i][0] + arr[i][1];
		tmp[i][1] = arr[i][1] + arr[i][2];
		/*
		for (int j = 0; j < machines - 1; j++)
		{
			std::cout << tmp[i][j] << " ";
		}
		std::cout << "\n";
		*/
	}
	return tmp;
}

/*
@johnson_algorithm function
need parameters: int Table[n][2]			  - Table n task for 2 machins which represent time
vector<int>& task_sequence  - References to result sequences of tasks
int n						  - Amount of tasks
*/
void johnson_algorithm(int **Tablica,std:: vector<int>& task_sequence, int n) {
	std::queue <int> first_tasks;		//tasks on 1 machine
	std::stack <int> second_tasks;		//task on second machine
									//	vector <int> task_sequence;		//first+second tasks 
	bool tasks_list[24];				// tasks to do
	int prev_min = 0;					//prev task min
	int which_task, which_machine = 0;
	std::fill_n(tasks_list, n, 1);	        //fill table with n elem. Set on 1		
	for (int iter = 0; iter<n; iter++)
	{
		int min = 450000;		//1000 some great value;
		for (int i = 0; i<n; i++)
		{
			if (tasks_list[i] == false)	//if done serach in next one
				continue;
			for (int j = 0; j<2; j++)
			{
				if ((Tablica[i][j]) <= min)
				{
					min = Tablica[i][j];  //new min
					which_task = i + 1; which_machine = j;
					/*	 		unnecessary code?!
					if(prev_min==min)
					{
					tasks_list[i]=false;
					if(j==0)
					{
					first_tasks.push(i+1);

					}
					else
					{
					second_tasks.push(i+1);
					}
					}*/
				}
			}
		}
		tasks_list[which_task - 1] = false;		//task done
		if (which_machine == 0)
			first_tasks.push(which_task);
		else
			second_tasks.push(which_task);
	}
	for (int i = 0; !first_tasks.empty(); i++)
	{
		task_sequence.push_back(first_tasks.front());
		first_tasks.pop();
	}
	for (int i = 0; !second_tasks.empty(); i++)
	{
		task_sequence.push_back(second_tasks.top());
		second_tasks.pop();
	}
	std::cout << "Optymalna Sekwencja wykonania zadan(Algorytm Johnsona) to" << std::endl;
	for (int i = 0; i<task_sequence.size(); i++)
	{
		task_sequence[i] = task_sequence[i] - 1;
		std::cout << task_sequence[i] << " ";
	}
	std::cout << std::endl;
}

std::vector<std::vector<int>> load(std::string nazwa)
{	
	int rozmiar=0;
	std::vector<std::vector<int>> arr;
	std::fstream plik;
	plik.open(nazwa, std::ios::in | std::ios::out);
	if (plik.good())
	{
		plik >> rozmiar;
		int i = 0;
		while (!plik.eof())
		{
			arr.push_back(std::vector<int>());
			int d;
			plik >> d;
			arr[i].push_back(d);
			plik >> d;
			arr[i].push_back(d);
			plik >> d;
			arr[i].push_back(d);
			i++;
		}	
	}
	plik.close();
	/*
	for (int i = 0; i < rozmiar; i++) 
	{
		for (int j = 0; j < 3; j++) 
		{
			std::cout << arr[i][j] << '\t';
		}
		std::cout << '\n';
	}
	*/
	return arr;
}


int main()
{
	int arr[5] = { 0,1,2,3,4 };
	int data[5][2] = { { 4, 5 },{ 4, 1 },{ 10, 4 },{ 6, 10 },{ 2, 3 } };
	int n = sizeof arr / sizeof arr[0];
	int johnson_time = 0;
	std::vector<int> combination = { 4,3,2,1,0 };
	std::vector <int> task_sequence;
	std::vector <int> task_sequence2;
	std::vector <int> task_sequence3;
	std::vector<std::vector<int>> table;
	int **a, **b, **c;
	//print_matrix();
	//print_matrix_universal(combination_to_jobs(combination));
	//int jobs = 5;
	//int machines = 2;
	//std::vector<std::vector<int>> table = { { 4, 5 },{ 4, 1 },{ 10, 4 },{ 6, 10 },{ 2, 3 } };
	permutation(arr, 0, n - 1);
	all_combination_c_time();
	print_matrix();
	find_min_cmax();
	b = convert_data(data2);
	johnson_algorithm(b, task_sequence, 5);
	johnson_time = count_time(combination_to_jobs(task_sequence, data2));
	std::cout << "C_time dla kombinacji z algorytmu Johnsona dla wariantu 2 maszynowego " << johnson_time << std::endl;
	std::cout << std::endl;
	a=reduce_col(data3);
	johnson_algorithm(a, task_sequence2, 4);
	johnson_time = count_time(combination_to_jobs(task_sequence2, data3));
	std::cout << "C_time dla kombinacji z algorytmu Johnsona dla wariantu 3 maszynowego " << johnson_time << std::endl;
	std::cout << std::endl;
	table = load("Dane.txt");
	c = reduce_col(table);
	johnson_algorithm(c, task_sequence3, 24);
	johnson_time = count_time(combination_to_jobs(task_sequence3, table));
	std::cout << "C_time dla kombinacji z algorytmu Johnsona dla wczytanych danych z pliku" << johnson_time << std::endl; 
	system("pause");
	return 0;
}

