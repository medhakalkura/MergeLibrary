#ifndef MERGE_H_
#define MERGE_H_

#include "plr.h"
#include <map>
#include <iostream>
using namespace std;

//template<typename Key>
vector<int> Merge(vector<int> arr1, vector<int> arr2, int a1, int a2);

float GuessPositionFromPLR(int target_key, int index, map<int, PLRModel> models);

//template<typename Key>
PLRModel getModel(vector<int> arr, int n);

#endif