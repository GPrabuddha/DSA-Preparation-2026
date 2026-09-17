#include<bits/stdc++.h>
using namespace std;
//  IDEA: searching faster
// Use extra memory to make searching/counting much faster.

bool containsDuplicate(vector<int> &nums){
    // What info do we need: Have I already seen this number?
    // that's what hashset is for therefore use unordered_set
    unordered_set<int> seen;
    seen.insert(nums[0]);
    for(int i=1; i<nums.size(); i++){
        if(seen.count(nums[i])) return true;
    }
    return false;
}

bool twoSum(vector<int> &nums, int target){
    // for each x:

    // 1. What do I need?
    //    target - x

    // 2. Have I seen it?
    //    yes → answer

    // 3. Otherwise remember x
    unordered_set<int> seen;
    seen.insert(nums[0]); // if nums is empty can cause problems therefore start from 0th index

    // for(int i=1; i<nums.size(); i++){
    for(int x: nums){
        if(seen.count(target - x)){
            return true;
        }
        seen.insert(x);
    }
    return false;
}

int firstUniqueElement(vector<int> &nums){
    // count freq first
    unordered_map<int, int> freq;
    for(int x: nums){
        freq[x]++;
    }
    // for(auto p: freq){ 
    //     if(p.second == 1){
    //         return p.first;
    //     }
    //     // nums = [10, 20, 30, 20, 30, 40, 50] above auto p doesn't work for this as auto p doesn't keep ordering same as original
    // }

    for(int x: nums){
        if(freq[x] ==1){
            return x;
        }
    }
    return -1;

}

int majorityElement(vector<int> &nums){
    // count the freq of each element first, how? unordered_map
    unordered_map<int, int> freq;

    for(int x:nums){
        freq[x]++;
    }
    for(auto p:freq){
        if(p.second > (nums.size()/2)){  // *** nums.size()/2 is an integer division
            return p.first;
        }
    }
    return -1;
}

int longestConsecutive(vector<int> &nums){
    // unordered_set<int> seen;
    // int ans = 1; // by default a single element is the longest sequence at start
    // for(int x: nums){
    //     if(!seen.count(x-1)){
    //         // x is the beggining of sequence
    //         seen.insert(x);
    //         while(seen.count(x+1)){
    //             ans += 1;
    //             x += 1;
    //         }
    //     }
    // }

    //  problem with my approach was i was trying to build seen but ordering info was not added
    // but we can use array for ordering info
    unordered_set<int> seen;
    // int ans = 1; // for empty nums it return 1 which is false
    int ans = 0;

    for(int x: nums){
        seen.insert(x);
    }

    for(int x: nums){
        if(!seen.count(x-1)){
            int length = 1;
            while(seen.count(x+1)){
                length++;
                x++;
            }
            ans = max(ans, length);

        }
    }
    return ans;

}

vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
    unordered_set<int> n1;
    vector<int> res;
    for(int x: nums1){
        n1.insert(x);
    }
    // for(int x: nums2){
    //     if(n1.count(x)){
    //         res.push_back(x); // this can add duplicate elements but we want unique elements
    //     }
    // }
    unordered_set<int> added;
    for(int x: nums2){
        if(n1.count(x) && (!added.count(x))){
            res.push_back(x);
            added.insert(x);
        }
    }
    return res;
}

int main(){
    // HashSet
    unordered_set<int> s;
    s.insert(10);
    s.insert(20);
    s.insert(30);

    // Have i seen this element/check existence?
    // if(s.count(20)){
    //     cout<< "found"<<endl;
    // }

    // Hashmap
    // instead of storing just value, we store key->value relationship
    unordered_map<int, int> freq;

    // application freq. counting
    // int a[] = [1, 2, 2, 3, 4, 3]; not valid in cpp
    // int a[] = {1, 2, 2,2, 3, 4, 3};
    // for(int x: a){
    //     freq[x]++;

    // }
    // cout<<freq[2]<<endl;

    //     for (auto p : freq) {
    //     cout << p.first << " -> " << p.second << endl;
    // }


    // ### Problem 1 contains duplicate
    // vector<int> a = {1, 2, 3, 1};
    // cout<<boolalpha<< containsDuplicate(a);

    // ### Problem 2 Two sum (unsorted array)
    // array is not sorted
    // what info do we need? needed = target - current already exists?
    // have i seen needed? i.e. does any prior number add to current

    // vector<int> nums = {2, 11, 7, 15};
    // cout<< boolalpha << twoSum(nums, 10);


    // ### Problem 3 first unique element
    // vector<int> nums ={4, 1, 2, 1, 2, 4, 7};
    // vector<int> nums = {10, 20, 30, 20, 30, 40, 50};

    // Hashmap -> "How many times does this value occur?"
    // Array -> "What was the original order?"
    // cout<< firstUniqueElement(nums);

    // ### Problem 4 Majority element
    // Given [2,2,1,1,1,2,2], find the element that appears more than n/2 times.
    // vector<int> nums = {2,2,1,1,1,2,2};
    // cout<< majorityElement(nums);

    // ### Problem 5 Longest consecutive subsequence
    // Given an unsorted array of integers nums, find the length of the longest sequence of consecutive integers.

    // A consecutive sequence consists of integers where each number is exactly 1 greater than the previous number.

    // You must design an algorithm with O(n) average time complexity.

//     Array
//  ↓
// preserves order / can have duplicates

// HashSet
//  ↓
// fast existence lookup
//  ↓
// removes duplicates


// Problem 6: Intersection of Two Arrays
// Given two integer arrays nums1 and nums2, return an array containing the unique elements that appear in both arrays.


    return 0;
}