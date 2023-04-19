#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

#include "merge.h"

using namespace std;

int main()
{
    cout<<"Start Test\n";
    vector<int> arr1;
    vector<int> arr2;
    vector<int> arr3;
    vector<int> arr4;
    for (int x=0;x<10000;x++)
    {
    arr1.push_back(rand()%1000000);
    }
    for (int x=0;x<10000;x++)
    {
    arr2.push_back(rand()%1000000);
    }
    for (int x=0;x<10000;x++)
    {
    arr3.push_back(rand()%1000000);
    }
    for (int x=0;x<10000;x++)
    {
    arr2.push_back(rand()%1000000);
    }
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
    sort(arr3.begin(), arr3.end());
    sort(arr4.begin(), arr4.end());
    vector<vector<int>> matrix;
    matrix.push_back(arr1);
    matrix.push_back(arr2);
    matrix.push_back(arr3);
    matrix.push_back(arr4);
    vector<int> result;
    result = Merge(matrix);
    cout<<"Size of the result is : "<<result.size()<<"\n";
    for(int i=0;i<matrix.size()*10000-1;i++)
    {
        assert(result[i]<=result[i+1]);
    }
    cout<<"Sorted!\n";
    return 0;
}