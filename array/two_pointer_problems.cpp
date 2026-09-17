#include<bits/stdc++.h>
using namespace std;

// Before writing code, always answer these 3 questions:

// 1. What does each pointer represent?
// 2. When do I move left?
// 3. When do I move right?


void reverseArray(vector<int> &nums){
    // pattern left + right, swap, move both inward
    int left = 0;
    int right = nums.size() - 1;
    while(left < right){
        swap(nums[left], nums[right]);
        left++;
        right--;
    }
}

bool palindromeArray(vector<int> &nums){
    // compare a[left] and a[right]
    int left = 0;
    int right = nums.size() - 1;
    while(left < right){
        if(nums[left] == nums[right]){
            left++;
            right--;
        } else return false;
    }
    return true;
}

void moveZeroes(vector<int> &nums){
      // slow = position for next non-zero, fast = scanner.

      // i want to track the position where my next non-zero element goes
      int non_zero = 0;
    //   i is for scanning the array
    //   for(int i=0; i<nums.size() - 1; i++){  silly mistake ****** wasn't iterating full array
    for(int i=0; i<nums.size(); i++){
        // cout<< "iteration: " << i << endl;
        // whenever we get non-zero element we want to swap as the non_zero position
        if(nums[i] != 0){
            // nums[non_zero] = nums[i];  // ***** with this it was getting difficul to keep track of zeros, and array was full of non-zero elements only
            swap(nums[non_zero], nums[i]);
            non_zero++;
        }
        // cout<<nums[i]<<endl;
        // cout << "non_zero: " << non_zero << endl;
      }
}

vector<int> squareSorted(vector<int> &nums){
    // constraint: solve in O(n) time
    // key idea is that largest value can come from either end
    // int negative_side = 0;
    // int positive_side = nums.size() -1;
    

    // ***** or rather keep the same left and right, and as array can contain negative numbers
    // max element can come from either side so we need 2 pointers, left to track negative numbers and right to track positive numbers
    // but they have additional purpose as array can be full negative and that is to decrease right as we get max element which can come from either rightmost or leftmost element
    
    // int left = 0;
    // int right = nums.size()-1;
    // while(left<right){
    //     int left_square = nums[left] * nums[left];
    //     int right_square = nums[right] * nums[right];
    //     if(left_square < right_square){
    //         right --;
    //     } 
    //     // else {
    //     //     swap(nums[left], nums[right]); // ***** can cause problems if both left and right have same square then left never moves
    //     // }
    //     else if(left_square > right_square){
    //         swap(nums[left], nums[right]);
    //     }
    //     else right--;
    // }
    // for(int i=0; i<nums.size(); i++){
    //     nums[i] = nums[i] * nums[i];
    // }
//  ******** this solution destroys ordering as we are chaning nums with swap, remember two pointer is for sorted array so ordering is important
// as our operations depend on it [-5,-3,-2,-1] fail case

    int left = 0;
    int right = nums.size() - 1;

    vector<int> result(nums.size());
    int pos = nums.size() - 1;

    while (left <= right) {
        int left_square = nums[left] * nums[left];
        int right_square = nums[right] * nums[right];

        if (left_square > right_square) {
            result[pos] = left_square;
            left++;
        }
        else {
            result[pos] = right_square;
            right--;
        }

        pos--;
    }

    return result;

}

int main(){
    // ### Problem 1 reverse an array in place
    // vector<int> nums = {1, 2, 3, 4, 5};
    // reverseArray(nums);
    // for(int x:nums){
    //     cout<< x;
    // }

    // ### Problem 2 check if an array is a palindrom
    // vector<int> nums = {1, 2, 3, 4, 5};
    // vector<int> nums2 = {1, 2, 2, 1};
    // cout << boolalpha << palindromeArray(nums);
    // cout<<endl;
    // cout << boolalpha << palindromeArray(nums2);

    // ### Problem 3 Move zeroes
    //  Move all zeroes to the end while maintaining the relative order of non-zero elements.
    // vector<int> nums = {0, 1, 0 , 3, 12};
    // moveZeroes(nums);
    // for(int x: nums){
    //     cout<< x << ",";
    // }
  

    // ### Problem 4 Squares of sorted array
    // Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number, also sorted in non-decreasing order.

    // You must solve it in O(n) time.
    // vector<int> nums = {-4, -1, 0, 3, 10};
    vector<int> nums = {-5, -2, 1, 2, 3};
    vector<int> result = squareSorted(nums);
    for(int x: result){
        cout << x << ",";
    }

    return 0;
}