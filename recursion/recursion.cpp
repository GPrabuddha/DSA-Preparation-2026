#include<bits/stdc++.h>
using namespace std;

// Recursion means a function solves a problem by calling itself on a smaller version of the same problem.

// the important structure is

/*
void solve(problem){

    // 1. Base case
    if(smallest_case){
        return;
    }

    // 2. Do something

    // 3. Solve smaller problem
        solve(smaller_problem)
}
*/

void print(int n){
    if(n==0) return;

    cout << n << " ";

    print(n-1);
}


// RECURSION has 2 phases, before vs after
void f(int n){
    if(n==0) {
        return;
    }

    cout << "Before: " << n << endl;

    f(n-1);

    cout << "After: " << n << endl;
}

// PROBLEM 1: Print 1 to N
void print1n(int n){
    if(n==0){
        return;
    }

    print1n(n-1);
    cout << n << " ";
}

// *****
// Code before the recursive call executes while going down. 
// Code after the recursive call executes while coming back up.

int factorial(int n){
    if(n==0){
        return 1;
    }

    // factorial(n-1);
    return (n * factorial(n-1));

    // as n! = n × (n-1)!
}

/* Whenever you see a recursion problem ask
1. What is the smallest problem?
    That's your base case.

2. How can I express the current problem using a smaller problem?
    That's your recursive case.

Ex. Factorial
    Current problem:
    factorial(n)

    Smaller problem:
    factorial(n-1)

    Relationship:
    factorial(n) = n * factorial(n-1)

*/

// Recursion on arrays
// print array elements
void printArr(vector<int>& arr, int index){
    if(index == arr.size()){
        return;
    }

    cout<< arr[index] << " ";

    printArr(arr, index+1);
}

// RECURSION + TWO POINTERS -> Check whether an array/string is a palindrome
bool palindrome(string &s, int l, int r){
    // 1. base case
    if(l >= r){
        return true;
    }
    // 2. do something here check if they don't match
    if(s[l] != s[r]){
        return false;
    }

    // 3. recursive call, represent current problem as smaller problem
    // here palindrome(s, l, r) = check s[l] & s[r] + palindrome(s, l+1, r-1)
    return palindrome(s, l+1, r-1); 

}

/* For every recursion problem, write this on paper:
1. What is my state?
2. What is my base case?
3. What is my smaller problem?
4. What should I do before recursion?
5. What should I do after recursion?
6. What does the function return?

Ex. State:
l, r

Base case:
l >= r

Smaller problem:
l+1, r-1

Before recursion:
compare s[l] and s[r]

After recursion:
nothing

Return:
whether palindrome is true
*/

// Find the first occurrence of a target in an array using recursion.
int firstOccurrence(vector<int> &arr, int target, int i){
    // base case
    if(i == arr.size()){
        return -1;
    }

    // do something
    if(arr[i] == target){
        return i;
    }
    else return firstOccurrence(arr, target, i+1);

    // recurse
    // return firstOccurrence(arr, target, i+1);
}

// Check whether an array is a palindrome
bool isPalindrome(vector<int> &arr, int i){
    // base case
    if(i > arr.size() - 1 - i){
        return true;
    }

    // do something / current work
    if(arr[i] != arr[arr.size() - 1 - i]){
        return false;
    }
    
    // recurse
    return isPalindrome(arr, i+1);

}
// reverse array
void reverseArray(vector<int> &arr, int i){
    // base case
    // if(i > arr.size() - 1 - i){ // we end up swapping middle element even though it is harmless
    if(i >= arr.size() / 2){
        return;
    }

    // current work
    swap(arr[i], arr[arr.size() - 1 - i]);

    return reverseArray(arr, i+1);
}

// when we make a single recursive call every time it is also called as linear recursion
// but we can also make multiple recursive calls: all sequences probles
// each recursive call indicates a choice


// PROBLEM: Print all binary strings of length n.
void generate(string s, int n){
    if(s.size() == n){
        cout<< s << endl;
        return; // *** was missing return therefore recursion never ended
    }

    generate(s + '0', n); // this explores the choice of 0 as next character
    generate(s + '1', n); // this explores the choice of 1 as next character
}

// NOTE: **** make sure that base case ends i.e. put a return or have a proper condition otherwise recursion never ends

// try: generate all valid parentheses

// PROBLEM: Generate all subsequences
//  Given an array {1, 2, 3}, generate every possible subsequence while preserving element order.
void subsequences(vector<int> &arr, int i, vector<int> &current){
    if(i == arr.size()){
        for( int x: current){
            cout<< x << " ";
        }
        cout << endl;
        return;    // **** forgetting to put return remember otherwise recursion won't end
    }
    // we can either decide to take the element or skip it so 2 choices
    // CHOICE 1 skip the element
    subsequences(arr, i+1, current);

    // CHOICE 2 take the element
    current.push_back(arr[i]);
    
    // explore the choice
    subsequences(arr, i+1, current);

    // free current while coming up
    // BACKTRACK: Undo the choice
    current.pop_back();

}
// subsequence pattern: choose -> explore -> undo

// Question? Can we remove current.pop_back? -> Yes we can if we pass current by value
// i.e. void subsequences(vector<int> &arr, int i, vector<int> current)
// drawback: we end up copying current vector multiple times leading to more memory and time


// Problem: Count subsequences with a given sum

// NOTE: **** when passed by reference the variable is shared between fuction calls

// APPROACH 1: Using a global counter (global as we pass by reference)
void countSubsequences(vector<int> &arr, int i, int sum, int target, int &count){
    // start with base case
    // here we are talking about all subsequnces and i is index so when we are at the end of the array we should stop next time
    if(i == arr.size()){
        // base has 2 jobs one is to end the recursion and other is to solve the smallest subproblem
        // here the smallest subproblem is if sum == target we increment the count
        if(sum == target){
            count++;
        }
        return;
    }

    // We have 2 choices at each step, either take the element or not
    // Choice 1: take the element
    countSubsequences(arr, i+1, sum+arr[i], target, count);
    // Note: here we aren't using backtracking as count is global and sum is local variable

    // Choice 2: skip the element
    countSubsequences(arr, i+1, sum, target, count);
}

// without using count parameter
// we can just return the count for each branch then count = skip count + take count
int countSubsequences1(vector<int> &arr, int i, int sum, int target){
    if(i == arr.size()){
        if(sum == target){
            return 1;
        } else return 0;
    }

    // take branch
    int take = countSubsequences1(arr, i+1, sum + arr[i], target);

    // skip branch
    int skip = countSubsequences1(arr, i+1, sum, target);

    return take + skip;

}

// Problem: Given an array of positive integers and a target, determine whether any subsequence has the target sum.
bool validSubsequence(vector<int> &arr, int i, int sum, int target){
    if(i == arr.size()){
        if(sum == target){
            return 1;
        } else return 0;
    }

    bool take = validSubsequence(arr, i+1, sum + arr[i], target);
    bool skip = validSubsequence(arr, i+1, sum, target);

    // improvement scope: we explore both branches even if take is true -> soln is short circuit evaluation

    return take || skip;

}


bool findSubset(vector<int> &arr, int i, int sum, int target, vector<int> &current){
    // if(i == arr.size()){
    //     if(sum == target){
    //         return true;
    //     } else return false;
    // }
    // equivalently
    if(i == arr.size()){
        return sum == target;
    }


    current.push_back(arr[i]);
    if(findSubset(arr, i+1, sum + arr[i], target, current)){
        // for(int x: current){
        //     cout<< x << " ";
        // }
        return true;
    }
    // Note: Notice we pop back i.e undo the choice only in failure case as then subsequence is not valid
    current.pop_back();

    if(findSubset(arr, i+1, sum, target, current)){
    //     for(int x: current){
    //         cout << x << " ";
    //     }
    //     return true;
    // }
    return true;}

    return false;
}


int main(){
    // print(5);
    // f(5);
    // print1n(5);
    // cout<< factorial(4);

    // vector<int> arr = {1, 2, 3, 4, 5};
    // printArr(arr, 2);

    // vector<int> arr = {4, 7, 2, 7, 9};
    // int target = 9;
    // cout<< firstOccurrence(arr, target, 0);
    // cout<< boolalpha<< isPalindrome(arr, 0);
    // reverseArray(arr, 0);
    // for(int x: arr){
    //     cout << x << " ";
    // }

    // generate("", 2);

    // vector<int> arr = {1, 2, 3};
    // vector<int> current;
    // subsequences(arr, 0, current);

    // count subsequence
    // vector<int> arr = {1, 2, 3, 4, -1};
    // int count = 0;
    // countSubsequences(arr, 0, 0, 3, count);
    // cout << count;

    // find subset
    vector<int> arr = {1, 2, 3 , 4, -1};
    vector<int> current;
    if(findSubset(arr, 0, 0, 7, current)){
        for(int x: current){
            cout << x << " ";
        }
    } else cout<< "No subset found";

    return 0;
}