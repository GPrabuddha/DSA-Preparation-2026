#include<bits/stdc++.h>
using namespace std;

int max_Element(vector<int> &a){
    int max = a[0];  // idea/pattern is that we are maintaining some information
    // about everything we have seen so far

    for(int i=1; i<a.size(); i++){
        if(max<a[i]){
            max = a[i];
        }
    }
    return max;
}

bool twoSum(vector<int> &a, int target){
    // given a sorted array we need to find if any two elements sum to target
    // *** key idea: Use some property of the array to eliminate many possibilities at once.
    int left = 0;
    int right = a.size() - 1;

    // problems with multiple if i calculate sum again with changed variable ex. even after right-- i calculate again 
    // fix: use if else to separate mutually exclusive conditions

    // while(left<right){

    //     if(a[left] + a[right] == target) return true;

    //     if(a[left] + a[right] > target){
    //         right--;
    //     }
    //     if(a[left] + a[right] < target){
    //         left++;
    //     }
    // }

        while(left<right){
        int sum = a[left] + a[right];
        
        if(sum == target) return true;

        else if(sum > target){
            right--;
        }
        else
            left++;
        
    }
    return false;

}

// *** The same problem can often have multiple patterns. 
// Your job is to recognize which one gives the best complexity given the constraints.


// If the problem asks:  "Return the indices of the two elements"
// then sorting creates a complication. We've lost the original positions unless we preserve them.
//  ** That's one reason the classic Two Sum problem is usually solved using a hash map rather than sorting + two pointers.

// for two sum with unsorted array ask below question
// ***** Instead of asking "where is the number that pairs with me?", ask "have I already seen the number that I need?"
// different perspectives can lead to thinking about different patterns


//  ## Prefix sum 

// bool hasZeroSumSubarray(vector<int> &a){
//     vector<int> prefix;
//     // prefix[0] = 0; vector is empty so doesn't work
//     prefix.push_back(0);
//     int index = 1;
//     for(int x:a){
//         prefix[index] = prefix[index-1] + x;
//         index++;
//     }

//     // array has zero sum subarray if two prefix have equal sum so we just need to find
//     // if we have seen a prefix with sum already
//     // Question: Have I seen this thing? -> ans: set

//     unordered_set<int> seen;
//     for(int x: prefix){
//         // current_prefix = x;
//         if(seen.count(x))
//             return true;

//         seen.insert(x);
//     }
//     return false;

// }

// efficient implementation
bool hasZeroSumSubarray(vector<int> &a){
    unordered_set<int> seen;
    int sum = 0;
    seen.insert(sum);

    for(int x: a){
        sum += x;

        if(seen.count(sum)) return true;

        seen.insert(sum);
    }
    return false;

}

bool hasSubarraySumK(vector<int> &a, int k) {
    // your code
    // unordered_map<int, int> freq;
    unordered_set<int> seen;
    int sum = 0; 
    // we are missing [3,4] k=7 here
    seen.insert(0);
    // int count = 0;
    // freq[0] = 1
    
    for(int x: a){
        sum += x;
        if(seen.count(sum-k)){
            // count += freq[sum-k];
            return true;
        }
        seen.insert(sum);
    }
    return false;

}


//  Sliding window
int longestSubArray(vector<int> &a, int k){
    // given: positive elements only and sum <k therefore use sliding window
    int left = 0;
    long long sum = 0;
    int ans = 0;

    for(int right = 0; right<a.size(); right++){
        sum += a[right];

        while(sum>k){
            // decrease window as all are positive no. removing should decrease sum
            sum -= a[left];
            left++;
        }
        ans = max(ans, right - left + 1);
    }

    return ans;
}




int main(){
    vector<int> b = {1, 2, 3, -4, -100};
    cout<< max_Element(b);

    return 0;
}