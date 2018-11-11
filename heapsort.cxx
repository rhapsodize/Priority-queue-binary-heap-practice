#include <cstdio>
#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <map>
#include "json.hpp"
#include "priorityqueue.h"

using namespace std;

int main(int argc, char** argv) {

	ifstream file1; 

	string fileName = argv[1];

	file1.open(fileName); //access the file at the second input

	nlohmann::json jsonObject1; 

	if (file1.is_open()) 
	{ 
		file1 >> jsonObject1; 
	}

	int arraySizeF1 = jsonObject1["metadata"]["arraySize"];
	int sampleSizeF1 = jsonObject1["metadata"]["numSamples"];
	vector <string> storeKeyFile1;
	vector <int> storeUnsorted;
	vector <int> storeFinal;

	nlohmann::json printJson; 


	for (auto itr1 = jsonObject1.begin(); itr1 != jsonObject1.end(); ++itr1) 
	{
		if (itr1.key() != "metadata")
		{
			auto key1 = itr1.key();
			storeKeyFile1.push_back(key1);

			for (auto itr2 = jsonObject1[key1].begin(); itr2 != jsonObject1[key1].end(); ++itr2) 
			{
				storeUnsorted.push_back(*itr2);
				//cout << *itr2 << endl;
			}
		}
	}
//cout << arraySizeF1;
	for (int i = 0; i < sampleSizeF1; ++i)
	{
		priorityqueue *getQueue = new priorityqueue(arraySizeF1);
		//priorityqueue getQueue(arraySizeF1);
		//all values in the current sample should be sorted by the end of the first loop
		for (int j = 0; j < arraySizeF1; ++j) //arraySizeF1 is 4 for SampleExample.json
		{
			//cout << storeUnsorted.at(i*arraySizeF1+j) << " ";

			getQueue->insert(storeUnsorted.at(i*arraySizeF1+j));
		}
	
		for (int j2 = 0; j2 < arraySizeF1; ++j2)
		{
			//storeFinal.at(i) = getQueue->getMax();
			storeFinal.push_back(getQueue->getMax());
			getQueue->removeMax(); 	
			printJson[storeKeyFile1.at(i)].push_back(storeFinal.at(i*arraySizeF1+j2));
		}
	}

	printJson["metadata"]["arraySize"] = arraySizeF1;
	printJson["metadata"]["numSamples"] = sampleSizeF1;

	cout << printJson.dump(2);

}