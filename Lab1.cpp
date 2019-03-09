#include "stdafx.h"

//using namespace std;

std::vector<std::vector<int>> matrix;
std::vector<std::vector<int>> data2 = { { 4, 5 },{ 4, 1 },{ 10, 4 },{ 6, 10 },{ 2, 3 } };
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

void reduce_col(std::vector<std::vector<int>> arr)
{
	int machines = arr[0].size();
	int jobs = arr.size();
	//std::cout << machines << " ";
	//std::cout << jobs << " ";
	//std::vector<std::vector<int>> tmp;
	int tmp[4][2] = {};
	
	for (int i = 0; i < jobs; i++)
	{
		tmp[i][0] = arr[i][0] + arr[i][1];
		tmp[i][1] = arr[i][1] + arr[i][2];
		
		for (int j = 0; j < machines-1; j++)
		{
			std::cout << tmp[i][j] << " ";
		}
		std::cout << "\n";
		
	}
}

void johnson_algorithm()
{

}

int main()
{
	int arr[5] = { 0,1,2,3,4 };
	//int data[5][2] = { { 4, 5 },{ 4, 1 },{ 10, 4 },{ 6, 10 },{ 2, 3 } };
	int n = sizeof arr / sizeof arr[0];
	std::vector<int> combination = { 4,3,2,1,0 };
	//print_matrix();
	//print_matrix_universal(combination_to_jobs(combination));
	//int jobs = 5;
	//int machines = 2;
	//std::vector<std::vector<int>> table = { { 4, 5 },{ 4, 1 },{ 10, 4 },{ 6, 10 },{ 2, 3 } };
	permutation(arr, 0, n - 1);
	all_combination_c_time();
	print_matrix();
	find_min_cmax();
	//reduce_col(data3);
	//std::cout << count_time(table) << '\n';
	//system("pause");
	//return 0;
}
