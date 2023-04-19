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
    for (int x=0;x<10000;x++)
    {
    arr1.push_back(rand()%1000000);
    }
    for (int x=0;x<10000;x++)
    {
    arr2.push_back(rand()%1000000);
    }
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
    //vector<int> arr1 = {0,9,12,13,15};
    //vector<int> arr2 = {2,3,5,6,19};
    vector<int> result;
    result = Merge(arr1,arr2,arr1.size(),arr2.size());
    cout<<"The result is : \n";
    for(int i=0;i<1000;i++)
        cout<<result[i]<<" ";
    for(int i=0;i<999;i++)
        assert(result[i]<=result[i+1]);
    return 0;
}