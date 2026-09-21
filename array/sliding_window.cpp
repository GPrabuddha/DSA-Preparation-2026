#include<bits/stdc++.h>
using namespace std;
//  SLIDING WINDOWS PROBLEMS
// sliding window can be fixed size or variable size

// solution to problem 1
int maxSumSubarray(vector<int> &nums, int k){
    // target O(n) and space O(1)
    // int l=0; // $ don't need this as window is fixed size so we can initialize
    int l= k-1; // $

    // int r=0; // we have left and right in sliding window, where right expands and left shrink (both under some condition)
    // int i in for loop can work as right pointer

    // we want max sum with size k subarraay 
    int windowSum = 0; // as array elements can be negative
    for(int i=0; i<= l; i++){
        windowSum += nums[i];
    }
    int ans = windowSum;
    // cout<< ans<<endl;
    for(int i=l+1; i<nums.size(); i++){
        // new_subarray_sum = ans - nums[i-l-1] + nums[i]; // here it should have been new_subarray_sum -nums[i-l-1] + nums[i]
        windowSum = windowSum - nums[i-l-1] + nums[i];
        ans = max(ans, windowSum);
        // cout<<nums[i]<< ": "<<ans<< ": "<<new_subarray_sum<<endl;
    }
    return ans;

}

// Solution problem 2:
int longestSubarray(vector<int> &nums, int k){
    // important point to notice: the array is of positive integers i.e when we remove sum decrease and when we add sum increases
    int l = 0; // $ take it window size
    int ans=0;
    int window_sum = 0;

    // $ **** here i was using l as expanding but i was wrong
    // for(int r=0; r<nums.size(); r++){
    //     if(window_sum<=k){
    //         l++;
    //         window_sum = window_sum + nums[l];
    //         ans = max(ans, r-l+1);
    //     } else 
    // }

    // **** use for loop pointer for expanding and if condition is not satisfied use left for shrinking
    for(int r=0; r<nums.size(); r++){
        // *** 1. expand
        window_sum += nums[r];


        // *** 2. Shrink if condition is violated
        // if(window_sum > k) // we need to keep shrinking till condition is violated
        while(window_sum>k){
            window_sum -= nums[l];
            l++;
        }

        // *** 3. Record the valid window
        ans = max(ans, r-l+1);
    }
    return ans;

}

// Solution problem 3:
int longestSubstring(string s, int k){
    // as string is like an array, substring is like a subarray (contiguous)
    // adding or removing characters changes some property therefore sliding window also as it is asking for contiguous substring
    int l=0;
    int ans=0;
    // int window_size=0;
    // string subs;  // don't create another string use l, and r to manage it using s.substr(index, length)

    unordered_map<char, int> freq;
    // string a =
    // for(char c:) // no need to build it, add as we go

    for(int r=0; r<s.size(); r++){
        // 1. expand substring
            // string a = s.substr(l, r-l+1);

            freq[s[r]]++;


        // 2. check condition to remove it * here condition is No. of distinct char <=k
        // 2.1 find distinct char in substring -> whenever freq. comes think hashmap
        // unordered_map<char, int> freq;
        // for(char c: a){
        //     freq[c]++;
        // }

        // **** this creates freq map for every window, taking extra times

        while(size(freq) > k){
            freq[s[l]]--;     

            if(freq[s[l]] == 0){
                freq.erase(s[l]);
            }

            l++;
        }
        ans = max(ans, r-l+1);
    }
    return ans;
}


// solution to problem 4
bool checkInclusion(string s1, string s2){
    int length_of_window = s1.size();
    int l = 0;
    unordered_map<char,int> freq_s2;
    unordered_map<char,int> freq_s1;
    for(char c:s1){
        freq_s1[c]++;
    }

    for(int r = 0; r<s2.size(); r++){
        // 1. Expand
        freq_s2[s2[r]]++;

        if((r-l+1) < length_of_window){ // this takes care of length
            continue; // expanding 
        }

        // need to check now if char freq are same or not
        // while(freq_s1.size() != freq_s2.size()){  // ***** while is not needed because fixed window size
        //     freq_s2.erase(s2[l]);
        //     l++;
        // }

        // *** above while is not needed as it is fixed size window and I get fixed size windows using above if condition
        // now i just need to remove left and add right if condition fail as it is fixed size

        // runs if freq_s1==freq_s2 i.e. no. of distinct char are same
        // now we need to check if those char frequencies/count match or char match if not move window
        // for(auto c: freq_s1){
        //     if(c.second != freq_s2[c.first]){ // ** no need for this (if(freq_s1==freq_s2)) works

        if(freq_s1 == freq_s2){
            return true;
        }

        freq_s2[s2[l]]--;
        if(freq_s2[s2[l]] == 0){
            freq_s2.erase(s2[l]);
        }
        l++;

        //         freq_s2[s2[l]]--;
        //         if(freq_s2[s2[l]] == 0){
        //             freq_s2.erase(s2[l]);
        //         }
        //         l++;
        //         continue;
        //     }
        // }
        // return true; // ** was returning unconditional true value, wrong as first invalid window can trigger this
    }
    return false;
}
// *** I used same structure in problem 4 

// Fixed Sliding Window
//         ↓
// Add right element
//         ↓
// Window full?
//         ↓
// Check condition
//         ↓
// Valid → answer
// Invalid → remove left + move left
//         ↓
// Repeat


// solution problem 5
int lengthOfLongestSubstring(string s) {
    // this is variable window problem, where based on invalidity we keep removing objects
    int l=0;
    int ans=0;
    unordered_map<char,int> freq;

    for(int r=0; r<s.size(); r++){
        // 1. expand window
        freq[s[r]]++;

        // 2. check if expanding caused our condition to violate
        // condition we have here is no repeated characters i.e. freq[char] ==1
        while(freq[s[r]]>1){
            freq[s[l]]--; // ** remove from left side
            l++;
        }
        ans = max(ans, r-l+1);
    }
    return ans;
}

int main(){
    // problem 1: Maximum Sum Subarray of Size K
    // Find the maximum sum of any contiguous subarray containing exactly k elements.

    vector<int> nums = {2, 1, 5, 1, 3, 2};
    // cout << maxSumSubarray(nums, 2);

    // problem 2: Longest Subarray With Sum ≤ K
    // Given an array of positive integers and an integer k, find the length of the longest contiguous subarray whose sum is at most k.

    // problem 3: Longest Substring With At Most K Distinct Characters
    // Given a string s and an integer k, find the length of the longest substring containing at most k distinct characters.

    // Problem 4: permutation in a string
    // Given two strings s1 and s2, determine whether any permutation of s1 appears as a substring of s2.
    // Example-> s1 = "ab",     s2 = "eidbaooo"
    // $$ How to think-> 1. as it is substring, it's lengh should be equal to length of s1
    // 2. we need to check freq, order doesn't matter here
    // Therefore it is a FIXED SIZE SLIDING WINDOW + HASHMAP PROBLEM

    // problem 5: Longest Substring Without Repeating Characters
    // Find the length of the longest substring with no repeated characters.





    return 0;
}