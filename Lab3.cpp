#include <stdio.h>
#include <string.h> 
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>
#include <stack>
#include <fstream>
#include <cmath>
#include <random>
#include <chrono>


std::vector<std::vector<int>> matrix;
std::vector<std::vector<int>> data = { { 4, 1, 4 },{ 4, 3, 3 },{ 1, 2, 3 },{ 5, 1, 3 } };

bool sortcol(const std::vector<int>& v1,
	const std::vector<int>& v2) {
	return v1[1] > v2[1];
}

std::vector<int> combination_by_sum_of_time_in_machine(std::vector<std::vector<int>> table)
{
	int machines = table[0].size();
	int jobs = table.size();
	std::vector<std::vector<int>> index_and_count_time;
	std::vector<int> index_sorted;

	for (int j = 0; j<jobs; j++)
	{
		int sum = 0;
		index_and_count_time.push_back(std::vector<int>());
		index_and_count_time[j].push_back(j);
		for (int m = 0; m<machines; m++)
		{
			sum += table[j][m];
		}
		index_and_count_time[j].push_back(sum);
	}

	std::sort(index_and_count_time.begin(), index_and_count_time.end(), sortcol);
	for (int j = 0; j < index_and_count_time.size(); j++)
	{
		index_sorted.push_back(index_and_count_time[j][0]);
	}

	return index_sorted;
}

std::vector<std::vector<int>> combination_of_moveable_number(std::vector<int> static_numbers, int moveable_number)
{
	std::vector<std::vector<int>> vector_of_combinations;
	for (int i = 0; i<(static_numbers.size() + 1); i++)
	{
		std::vector<int> tmp = static_numbers;
		tmp.insert(tmp.begin() + i, moveable_number);
		vector_of_combinations.push_back(tmp);
	}
	return vector_of_combinations;
}



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
		ready_to_count.push_back(data[combination[i]]);
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


void countCmax(std::vector<std::vector<int>> data, int jobs, int machines) {

	std::vector<std::vector<int>> arr;
	int sum = 0;
	for (int i = 0; i < jobs; ++i) {
		for (int j = 0; j < machines; ++j) {
			sum = sum + data[i][j];
			//ready_to_count.push_back(tmp[combination[i]]);
		}
		std::cout << sum << std::endl;
		sum = 0;
	}

}

std::vector<int> neh_function(std::vector<std::vector<int>> table)
{
	std::vector<int> sequence_original = combination_by_sum_of_time_in_machine(table);
	std::vector<int> sequence;
	sequence.push_back(sequence_original[0]);

	for (int i = 0; i<sequence_original.size(); i++)
		std::cout << sequence_original[i] << "\t";
	std::cout << "\n\n\n";

	//std::vector<int> sequence;
	//sequence.insert(sequence.begin(), sequence_original.begin(), sequence_original.begin()+1);
	for (int i = 1; i<sequence_original.size(); i++)
	{
		std::vector<std::vector<int>> tmp_sequence =
			combination_of_moveable_number(sequence, sequence_original[i]);
		int tmp_time = 1000000;
		//int tmp_time = count_time(combination_to_jobs(tmp_sequence[i]));
		int tmp_time_idx = 0;
		int tmp = 1000000;
		for (int k = 0; k<(sequence.size() + 1); k++)
		{
			tmp = count_time(combination_to_jobs(tmp_sequence[k], table));
			if (tmp < tmp_time)
			{
				tmp_time = tmp;
				tmp_time_idx = k;
				//std::cout<<"\n||| k : "<<k<<" tmp "<<tmp<<" tmp_time "<< tmp_time<<"\n\n";
			}
			std::cout << "\n||| k : " << k << " tmp " << tmp << " tmp_time " << tmp_time << "\n\n";
		}
		sequence = tmp_sequence[tmp_time_idx];
		for (int i = 0; i<sequence.size(); i++)
			std::cout << sequence[i] << "\t";
		std::cout << "\n\t" << tmp_time << "\n\n";


	}
	return sequence;
}

bool simulated_annealing_stop_condition(int max_iteration, int current_iteration,
	int  critical_temperature, int current_temperature)
{
	if ((max_iteration == -1) && (critical_temperature == -1))
		return false;

	if (((current_iteration >= max_iteration) && (max_iteration > 0)) ||
		((current_temperature <= critical_temperature) && (critical_temperature > 0)))
		return false;


	return true;
}

std::vector<int> simulated_annealing(std::vector<std::vector<int>> table,
	std::vector<int> start_sequence, float cooling_parameter,
	int start_temperature, int max_iteration_number = -1, int critical_temperature = -1)
{
	int max_idx = start_sequence.size() - 1;
	int current_iteration = 0;
	int current_temperature = start_temperature;

	std::vector<int> current_sequence = start_sequence;
	std::vector<int> best_sequence = current_sequence;
	int best_sequence_time = count_time(combination_to_jobs(best_sequence, table));


	while (simulated_annealing_stop_condition(max_iteration_number, current_iteration,
		critical_temperature, current_temperature))
	{
		int count_time_old = count_time(combination_to_jobs(current_sequence, table));
		current_sequence = best_sequence;
		int rand_idx1 = std::rand() % max_idx;
		int rand_idx2 = rand_idx1;
		while (rand_idx2 == rand_idx1)
			rand_idx2 = std::rand() % max_idx;
		std::cout << "idx " << current_iteration << " rand_1 " << rand_idx1 << " rand_2 " << rand_idx2 << "\n";
		std::swap(current_sequence[rand_idx1], current_sequence[rand_idx2]);
		/*
		for(int i=0; i<current_sequence.size(); i++)
		std::cout<<current_sequence[i]<<"\t";
		std::cout<<"\n\n\n";
		*/

		int count_time_new = count_time(combination_to_jobs(current_sequence, table));
		float probability = 0.0;
		if (count_time_new >= count_time_old)
		{
			probability = std::exp((float)(count_time_old - count_time_new) /
				(float)current_temperature);
		}
		else
			probability = 1.0;


		std::cout << "probability " << probability << " old_time " << count_time_old << " new_time " << count_time_new << " tem " << current_temperature << "\n";

		if (probability >= (float)((std::rand() % 1000) / 1000))
		{
			current_sequence = current_sequence;
		}

		current_temperature = (int)((float)current_temperature*cooling_parameter);

		if (count_time_new < best_sequence_time)
		{
			best_sequence = current_sequence;
			best_sequence_time = count_time(combination_to_jobs(best_sequence, table));
		}
		current_iteration++;
		std::cout << "\n";
	}

	return best_sequence;
}

std::vector<std::vector<int>> load(std::string nazwa)
{
	int row = 0;
	int column = 0;
	std::fstream plik;
	plik.open(nazwa, std::ios::in | std::ios::out);
	plik >> row;
	plik >> column;
	std::vector<std::vector<int>> arr(row, std::vector<int>(column));
	if (plik.good())
	{
		while (!plik.eof())
		{
			for (int i = 0; i < row; ++i) {
				for (int j = 0; j < column; ++j) {
					plik >> arr[i][j];
				}
			}
		}
	}
	plik.close();
	/*
	for (int i = 0; i < row; i++)
	{
	for (int j = 0; j < column; j++)
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
	
	std::vector<std::vector<int>> table;
	table = load("Dane.txt");
	std::vector<int> cos = neh_function(table);
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	//auto rng = std::default_random_engine{};
	std::shuffle(std::begin(cos), std::end(cos), e);
	for (int i = 0; i<cos.size(); i++)
		std::cout << cos[i] << "\n";
	
	std::vector<int> tmp = simulated_annealing(table, cos, 0.95, 500, -1, 50);
	std::cout << "min time " << count_time(combination_to_jobs(tmp, table)) << "\n";
	
	return 0;
}
