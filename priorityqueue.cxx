#include "priorityqueue.h"
#include <vector>
#include <iostream>
#include <algorithm>  

using namespace std;
vector<int> storeVal;
int countInsert = 0;

priorityqueue::priorityqueue(int max)
{
    max_size = max;
    storeVal.resize(1);
    storeVal.reserve(max_size+1);
    //cout << max_size;
    
    //cout << storeVal.size();
    /*
    for (int i = 0; i < storeVal.size(); ++i)
    {
        cout << storeVal.at(i);
    }
    */
}

vector <int> priorityqueue::vecReturn()
{
    return storeVal;
}

void priorityqueue::insert(int k)
{
    //insert into binary heap
    //perform hepify up
    
    if (storeVal.size()-1 > max_size)
    {
        cout << "PriorityQueue::insert called on full priority queue";
        return;
    }

    storeVal.push_back(k); 
    //storeVal.at(max_size) = k;//insert k at the last location. Not using max_size - 1 because starting at index 1
    //cout << k;
    int parentIndex = 0;

    int childIndex = storeVal.size()-1; 
    if(childIndex % 2 == 0)
    {
        parentIndex = (childIndex)/2;
    }

    else if(childIndex % 2 == 1)
    {
        parentIndex = (childIndex - 1)/2;
    }

    while (childIndex > 1 && (storeVal.at(childIndex) > storeVal.at(parentIndex)))
    {
        int temp = storeVal.at(parentIndex);
        storeVal.at(parentIndex) = storeVal.at(childIndex);
        storeVal.at(childIndex) = temp;

        childIndex = parentIndex;
        if(childIndex % 2 == 0)
        {
            parentIndex = (childIndex)/2;
        }
        else if(childIndex % 2 == 1)
        {
            parentIndex = (childIndex - 1)/2;
        }
    }
}

int priorityqueue::getMax()
{
    return storeVal.at(1);
}
void priorityqueue::removeMax()
{

    if (storeVal.size() == 1)
    {
        cout << "PriorityQueue::removeMax called on an empty priority queue";
        return;
    }

    int parentIndex = 1;
    int child1Index = 2*parentIndex;
    int child2Index = 2*parentIndex + 1;
    int maxChildIndex;
    //cout << storeVal.back() << endl;
    storeVal.at(parentIndex) = storeVal.back();
    storeVal.pop_back(); //assuming vector pops the back, getting rid of the last value

    //heapify down
    if (child1Index > (storeVal.size() - 1) || child2Index >(storeVal.size() - 1) )
    {
        return;
    }
        while((storeVal.at(parentIndex) < storeVal.at(child1Index)) || (storeVal.at(parentIndex) < storeVal.at(child2Index)))
        {
            if (storeVal.at(child1Index) < storeVal.at(child2Index))
            {
                maxChildIndex = child2Index;
            }
            else
            {
                maxChildIndex = child1Index;
            }
            int temp = storeVal.at(parentIndex);
            storeVal.at(parentIndex) = storeVal.at(maxChildIndex);
            storeVal.at(maxChildIndex) = temp;

            parentIndex = maxChildIndex;
            child1Index = 2*parentIndex;
            child2Index = 2*parentIndex + 1;    
            if (child1Index > (storeVal.size() - 1) || child2Index >(storeVal.size() - 1) )
            {
                break;
            }
        }
    
}

int searchK(int k)//binary tree returns boolean, find returns last value, lowerbound may return false value, so my own
{
    for (int i = 1; i < storeVal.size(); ++i)
    {
        if (k == storeVal.at(i))
        {
            return i;
        }
    }
    return -1;
}

void priorityqueue::removeKey(int k)
{
    int getIndex = searchK(k);
    //cout << "remove at index " << getIndex;

        if (getIndex == -1)
        {
            cout << "PriorityQueue::removeKey key " << k << " not found";
        }
        int parentIndex = getIndex;
        int child1Index = 2*parentIndex;
        int child2Index = 2*parentIndex + 1;
        int maxChildIndex;
        int grandparent = 0;

        if (k < storeVal.at(storeVal.size()-1))
        {
            storeVal.at(parentIndex) = storeVal.at(storeVal.size() - 1);
            storeVal.pop_back(); //assuming vector pops the back, getting rid of the last value
            //heapify up
            if(parentIndex % 2 == 0)
            {
                grandparent = (parentIndex)/2;
            }

            else if(parentIndex % 2 == 1)
            {
                grandparent = (parentIndex - 1)/2;
            }

            while (parentIndex > 1 && (storeVal.at(parentIndex) > storeVal.at(grandparent)))
            {
                int temp = storeVal.at(grandparent);
                storeVal.at(grandparent) = storeVal.at(parentIndex);
                storeVal.at(parentIndex) = temp;

                parentIndex = grandparent;
                if(parentIndex % 2 == 0)
                {
                    grandparent = (parentIndex)/2;
                }
                else if(parentIndex % 2 == 1)
                {
                    grandparent = (parentIndex - 1)/2;
                }
            }
        }
        else //k >  storeVal.at(storeVal.size()-1
        {
            //heapify down
            storeVal.at(parentIndex) = storeVal.at(storeVal.size() - 1);
            storeVal.pop_back(); //assuming vector pops the back, getting rid of the last value
            
            //heapify down
            if (child1Index > (storeVal.size() - 1) )
            {
                return;
            }

            while((storeVal.at(parentIndex) < storeVal.at(child1Index)))
            {

                if((storeVal.at(parentIndex) < storeVal.at(child1Index)))
                {
                    maxChildIndex = child1Index;
                }

                if (child2Index < storeVal.size()-1 && storeVal.at(maxChildIndex) < storeVal.at(child2Index))
                {
                    maxChildIndex = child2Index;
                }
                if (maxChildIndex == 0)
                {
                    return;
                }
                int temp = storeVal.at(parentIndex);
                storeVal.at(parentIndex) = storeVal.at(maxChildIndex);
                storeVal.at(maxChildIndex) = temp;

                parentIndex = maxChildIndex;
                child1Index = 2*parentIndex;
                child2Index = 2*parentIndex + 1;
                if (child1Index > (storeVal.size() - 1) || child2Index >(storeVal.size() - 1) )
                {
                    return;
                }
            }
        }
       

}


void priorityqueue::change(int k, int newK)
{
    int searchIndex = searchK(k);

    if (searchIndex == -1)
    {
        cout << "PriorityQueue::change key " << k <<  " not found";
    }
    else
    {
        int parentIndex;
        int currentIndex = searchIndex;

        if (k < newK) //then heapify up
        {
            storeVal.at(currentIndex) = newK;

            int childIndex = currentIndex; 
            if(childIndex % 2 == 0)
            {
                parentIndex = (childIndex)/2;
            }

            else if(childIndex % 2 == 1)
            {
                parentIndex = (childIndex - 1)/2;
            }

           if (currentIndex > 1 && (storeVal.at(currentIndex) > storeVal.at(parentIndex))) //checking parents to see if I'm bigger
            {
                while (currentIndex > 1 && (storeVal.at(currentIndex) > storeVal.at(parentIndex)))
                {
                    int temp = storeVal.at(parentIndex);
                    storeVal.at(parentIndex) = storeVal.at(currentIndex);
                    storeVal.at(currentIndex) = temp;

                    currentIndex = parentIndex;
                    if(currentIndex % 2 == 0)
                    {
                        parentIndex = (currentIndex)/2;
                    }
                    else if(currentIndex % 2 == 1)
                    {
                        parentIndex = (currentIndex - 1)/2;
                    }
                }
            }
        }
        //heapify down
        else
        {
            storeVal.at(currentIndex) = newK;

            while(2*currentIndex < storeVal.size()) //checking children to see if I'm smaller
            {
                int j = 2*currentIndex;
                if (storeVal.size() < (j + 1) && storeVal.at(j) < storeVal.at(j+1))
                {
                    j++;
                }
                if(storeVal.at(currentIndex) < storeVal.at(j))
                {
                    int temp = storeVal.at(currentIndex);
                    storeVal.at(currentIndex) = storeVal.at(j);
                    storeVal.at(j) = temp;
                }
                currentIndex *= 2;
            }
        }
    }
}

  /*
int main()
{ 
     
    q.insert(1);
    q.insert(2);
    q.insert(3);
    q.insert(6);
    q.insert(7);
    q.insert(8);
    q.insert(9);
    q.insert(4);
    q.insert(5);
    
    q.removeMax();
    q.removeMax();
    q.removeMax();
    q.removeMax();
    q.removeMax();
    
    get = q.vecReturn();


    //few2
    
    priorityqueue q(4);
    vector <int> get;
    q.insert(2521);
    q.insert(4228);
    q.insert(4516);
    q.change(4228, 4488);
    q.removeKey(4488);
    

    get = q.vecReturn();

    for (int i = 0; i < get.size(); ++i)
    {
        cout << get.at(i) << " ";
    }
    cout << endl;

    few3
    priorityqueue q(4);
    vector <int> get;
    q.insert(2850);
    q.insert(3313);
    q.change(3313, 637);
    q.insert(1071);
    q.change(1071, 4842);
    q.insert(3805);
    q.removeMax();
    q.insert(4651);
    q.removeMax();
    q.change(2850, 3853);
    q.removeMax();
    q.insert(2174);
    q.removeMax();
    q.change(2174, 2832);
    q.change(2832, 4297);
    q.insert(3747);
    q.removeMax();
    q.change(3747, 4053);
    q.change(4053, 689);
    q.change(689, 1708);
    

  

   
}

    */