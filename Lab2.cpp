#include <stdio.h>
#include <tchar.h>
#include <stdio.h> 
#include <string.h> 
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>
#include <stack>
#include <fstream>

std::vector<std::vector<int>> matrix;
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

	/*
	for (int j = 0; j < index_and_count_time.size(); j++)
	{
	for (int m = 0; m <index_and_count_time[0].size(); m++)
	{
	std::cout<<index_and_count_time[j][m]<<" ";
	}
	std::cout<<"\n";
	}
	*/
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

	/*
	for (int j = 0; j < vector_of_combinations.size(); j++)
	{
	for (int m = 0; m <vector_of_combinations[0].size(); m++)
	{
	std::cout<<vector_of_combinations[j][m]<<" ";
	}
	std::cout<<"\n";
	}
	*/
	return vector_of_combinations;
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


std::vector<std::vector<int>> combination_to_jobs(std::vector<int> combination, std::vector<std::vector<int>> data)
{
	std::vector<std::vector<int>> ready_to_count;
	for (int i = 0; i<combination.size(); i++)
	{
		ready_to_count.push_back(data[combination[i]]);
	}
	return ready_to_count;

}



/*
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
*/
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

//1, 0, 3, 2
//18


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
	/*
	for (int i = 0; i<cos.size(); i++)
		std::cout << cos[i] << "\n";
		*/
	std::cout << "\n" << count_time(combination_to_jobs(cos, table)) << "\n";
	//combination_of_moveable_number(std::vector<int>{3, 5, 7}, 2);
	system("pause");
}

