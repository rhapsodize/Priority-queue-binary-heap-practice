#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"
#include "priorityqueue.h"
#include <sstream>

#include <vector>

using namespace std;

int main(int argc, char** argv) {

  ifstream file1; 
  file1.open(argv[1]); //access the file at the second input
  nlohmann::json jsonObject1; 

  nlohmann::json jsonAll; 



  if (file1.is_open()) 
  { 
    file1 >> jsonObject1; 
  }

  int maxHeapSize = jsonObject1["metadata"]["maxHeapSize"];
  int numOperations = jsonObject1["metadata"]["numOperations"];

  //cout << maxHeapSize << endl;

  //priorityqueue *getQueue = new priorityqueue(maxHeapSize);
  priorityqueue getQueue(maxHeapSize);
  
  vector <int> get;
  vector <string> storeKeyFile1;

  int increase = 0;
  int insertNum = 0;
  for (auto itr1 = jsonObject1.begin(); itr1 != jsonObject1.end(); ++itr1) 
  {
    if (itr1.key() != "metadata")
    {
      auto key1 = itr1.key();

      vector <int> storeVal;
      storeVal.resize(2);
      //storeKeyFile1.push_back(itr1.key());

      for (auto itr2 = jsonObject1[key1].begin(); itr2 != jsonObject1[key1].end(); ++itr2) 
      {
      //cout << itr2.key() << " ";
       //cout << itr2.value() << " ";
              //cout << *itr2<< " ";

        
        if (itr2.key() == "key")
        {
          //storeVal.push_back(itr2.value());
          storeVal.at(0) = itr2.value();
         //cout << itr2.value() << " ";
        }

        else if (itr2.key() == "newKey")
        {
          //storeVal.push_back(itr2.value());
          storeVal.at(1) = itr2.value();
          //cout << storeVal.at(1) << " ";
        }

        else if (itr2.key() == "operation")
        {
              //when inserting, the vector has 1 value, at index 0.
              if (itr2.value() == "insert")
              {

                //cout << insertNum << "!!!!!!!!!!!!!!!!!!!";
                getQueue.insert(storeVal.at(0));
             // cout << storeVal.at(0) << " ";
                storeVal.pop_back();
              }
              //when changing, the vector has 2 values, key at index 0, newKey at index 1
              else if (itr2.value() == "change")
              {
                //cout << storeVal.at(0) << " ";
                getQueue.change(storeVal.at(0), storeVal.at(1));
                storeVal.pop_back(); //popping twice because when encountering "change", 2 values exits
                storeVal.pop_back();
              }

              else if (itr2.value() == "removeMax")
              {
                //cout << insertNum << "??????????????";

                getQueue.removeMax();
              }

              else if (itr2.value() == "removeKey")
              {
                //cout << insertNum << "??????????????" << endl;
                //cout << storeVal.at(0) << "is val for removeKey";
                getQueue.removeKey(storeVal.at(0)); //segfa
                storeVal.pop_back();
              }
        }
      }
     // cout << endl;
     /* get = getQueue.vecReturn();
      for (int i = 1; i < get.size(); ++i)
      {
        cout << get.at(i) << "(" << i << ") ";
      }
      cout << endl;
      */
    }
  }
/*
  vector <int> get;
  get = getQueue.vecReturn();
  for (int i = 1; i < get.size(); ++i)
  {
    cout << get.at(i) << " ";
  }
  */


  vector <int> storeVal;
  storeVal = getQueue.vecReturn();

  int geti = 0;
  for (auto itr1 = jsonObject1.begin(); itr1 != jsonObject1.end(); ++itr1) 
  {
    if (itr1.key() != "metadata")
    {
      itr1.key() = to_string(geti);
      storeKeyFile1.push_back(itr1.key());
      geti++;
    }
   
  }
  int count = 0;
  for (int i = 1; i < storeVal.size(); ++i)
  {
    nlohmann::json temp;
    temp["key"] = storeVal.at(i);
    if (i != 1)
    {
          if(i % 2 == 0)
          {
            temp["parent"] = i/2;
          }
          else if(i % 2 == 1)
          {
            temp["parent"] = (i-1)/2;
          }
    }
    
    if ((2*i + 1) < storeVal.size())
    {
      temp["rightChild"] = 2*i+1;
    }
    if ((2*i) < storeVal.size())
    {
      temp["leftChild"] = 2*i;
    }

    jsonAll[to_string(i)] = temp;
    count ++;
  }

  
  jsonAll["metadata"]["maxHeapSize"] = maxHeapSize;
  jsonAll["metadata"]["max_size"] = maxHeapSize;
  jsonAll["metadata"]["numOperations"] = numOperations;
  jsonAll["metadata"]["size"] = storeVal.size(); //because hi contains 0 at front, but thing starts at 1, so 1 less

cout << jsonAll.dump(1);

}