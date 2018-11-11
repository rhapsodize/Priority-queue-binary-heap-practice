//#ifndef PRIORITYQUEUE_H
//#define PRIORITYQUEUE_H

#include <vector>
using namespace std;

class priorityqueue
{

public:
	int max_size;
	priorityqueue(int k);
	vector <int> vecReturn();
	void insert(int k);
	void removeMax();
	void removeKey(int k);
	void change(int k, int newK);
	int getMax();

};


