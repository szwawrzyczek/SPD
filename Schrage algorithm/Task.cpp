#pragma once
#include "Task.hpp"

using namespace std;

Task::Task() {} 
Task::~Task() {} 

ostream& operator<<(ostream& stream, const Task& o) {
	stream<<"Task : "<<o.nr<<"\t"<<"R: "<< o.r<<"\t\t"<<"P: ";
	stream<< o.p<<"\t"<<"Q: "<< o.q<<"\t"<<endl;
	return stream;
}