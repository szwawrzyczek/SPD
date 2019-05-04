#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <math.h>
#include <queue>

using namespace std;

class Task {
public:
	int nr;
	int r;  
	int p;
	int q;

	Task();
	~Task();
	friend ostream& operator<<(ostream& stream, const Task& o);
};

