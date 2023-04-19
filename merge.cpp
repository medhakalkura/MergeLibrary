#include "merge.h"
#include<cmath>
#include <iostream>
#include <map>

using namespace std;

//template<typename Key>
PLRModel getModel(vector<int> arr, int n)
{
    uint64_t prev_key = 0;
    int index=0;
    PLRBuilder plrBuilder;
    for(int i=0;i<n;i++)
    {
        prev_key = plrBuilder.processKey(to_string(arr[i]), index, prev_key);
        index+=1;
    }
    PLRModel plrModel;
    plrModel = plrBuilder.finishTraining();
    return plrModel;
}

float GuessPositionFromPLR(int target_key, int index, PLRModel model){
    std::vector<Segment>& segments = model.plrModelSegments;
    size_t s = model.plrModelSegments.size();
    int keyCount = model.keyCount;
    //int target_int = LdbKeyToInteger(target_key);
  
  // binary search between segments
    uint32_t left = 0, right = (uint32_t)segments.size() - 1;
    while (left != right - 1) {
        uint32_t mid = (right + left) / 2;
        if (target_key < segments[mid].x)  
        right = mid;
        else
        left = mid;
    }
    cout<<"Target key : "<<target_key<<"\n";
    cout<<"k : "<<segments[left].k <<"\n";
    cout<<"b : "<<segments[left].b<<"\n";
    double result = target_key * segments[left].k + segments[left].b;
    cout<<"target_key * segments[left].k "<<target_key * segments[left].k + segments[left].b<<"\n";
    cout<<"result : "<<result<<"\n";
    if(result < 0){
        result = 0;
    }
    cout<<"RESULT : "<<result<<"\n";
    return result;
}

//template<typename Key>
vector<int> Merge(vector<int> arr1, vector<int> arr2, int a1, int a2) {
    // My implementation of the Merge function goes here
    PLRModel plr_model1 = getModel(arr1, a1);
    PLRModel plr_model2 = getModel(arr2, a2);
    for(int i=0;i<plr_model1.plrModelSegments.size();i++)
        cout<<"X K B :"<<plr_model1.plrModelSegments[i].x<<" "<<plr_model1.plrModelSegments[i].k<<" "<<plr_model1.plrModelSegments[i].b<<"\n";
    cout<<"\n";
    for(int i=0;i<plr_model2.plrModelSegments.size();i++)
        cout<<"X K B :"<<plr_model2.plrModelSegments[i].x<<" "<<plr_model2.plrModelSegments[i].k<<" "<<plr_model2.plrModelSegments[i].b<<"\n";
    //cout<<"Models created!\n";
    // cout<<"PLR MODELS 1 : Keycount : "<<plr_model1.keyCount<<"\n";
    // cout<<"PLR MODELS 1 : Segment size : "<<plr_model1.plrModelSegments.size()<<"\n";
    // cout<<"PLR MODELS 2 : Keycount : "<<plr_model2.keyCount<<"\n";
    // cout<<"PLR MODELS 2 : Segment size : "<<plr_model2.plrModelSegments.size()<<"\n";
    vector<int> merged_array;
    map<int, vector<int>> list;
    map<int, PLRModel> models;
    models[0]=plr_model1;
    models[1]=plr_model2;
    list[0]=arr1;
    list[1]=arr2;
    int cdf_error = 0;
    vector<int> pos;
    for(int i=0;i<2;i++)
        pos.push_back(0);
    while(true)
    {
        int smallest_iterator_index = 0;
        int second_smallest_iterator_index = 0;
        int smallest = -1;
        int second_smallest = -1;
        int cdf_error = 0;
        for (int i = 0; i < 2; i++) {
            if(pos[i] == list[i].size())
                continue;
            if (smallest == -1) {
                smallest = i;
                continue;
            }
            if(list[smallest][pos[smallest]] > list[i][pos[i]]){
                second_smallest = smallest;
                smallest = i;
            }
            else if(second_smallest == -1)
            {
                second_smallest = i;
            }
            else if(list[second_smallest][pos[second_smallest]] > list[i][pos[i]])
            {
                second_smallest = smallest;
            }
        }
        if(smallest == -1)
            break;
        if(second_smallest == -1)
        {
            for (int i=pos[smallest];i<list[smallest].size();i++) 
            {
                merged_array.push_back(list[smallest][pos[smallest]]);
                pos[smallest] += 1;
            }
        }
        else
        {   
            int target_key = list[second_smallest][pos[second_smallest]];
            int flag =0;
            float approx_pos = GuessPositionFromPLR(target_key, smallest, models[smallest]);
            approx_pos=floor(approx_pos);
            if(approx_pos < 0)
                approx_pos = 0;
            if(approx_pos >= list[smallest].size())
                approx_pos = list[smallest].size()-1;
            cout<<"approx_pos : "<<approx_pos<<"\n";

            while(approx_pos > 0 and list[smallest][approx_pos] > list[second_smallest][pos[second_smallest]]){
                cdf_error += 1;
                approx_pos -= 1;
            }
        while((approx_pos) < list[smallest].size() && (approx_pos <= 0 || list[smallest][approx_pos] <= list[second_smallest][pos[second_smallest]])){
            cdf_error += 1;
            approx_pos += 1;
        }
        cout<<"CDF ERROR : "<<cdf_error<<"\n";
        for(int i=pos[smallest];i<approx_pos;i++)
        {
            merged_array.push_back(list[smallest][pos[smallest]]);
            pos[smallest] += 1;
        }
        }
    }
    return merged_array;
}