#include<bits/stdc++.h>
using namespace std;

// include<stack>

// ***** Key idea:
// Stack = maintain unresolved items where the newest unresolved item gets resolved first.

// bool isValid(string s){
//     stack<char> st;
//     for(char c: s){
//         // if(c!=')' || c!= '}' || c!=']'){  // **** this condition is always true silly mistake
//         // if(c!= ')' && c!= '}' && c!=']'){ // works 
//         if(c == '(' || c == '{' || c == '[') {// better as we are interested in open bracketes
//             st.push(c);
//         }
//         else if(st.top() == c){
//             st.pop();
//         }
//     }
//     if(st.empty()) return true;
//     else return false;

// }

bool isValid(string s){
    stack<char> st;
    for(char c:s){
        if(c == '(' || c=='[' || c=='{'){
            st.push(c);
        }
        else if(st.empty()) return false;
        else if(st.top() == '(' && c==')') st.pop();
        else if(st.top() == '[' && c==']') st.pop();
        else if(st.top() == '{' && c=='}') st.pop();
        else return false;
    }
    return st.empty();
}

string removeDuplicate(string s){
    stack<char> st;
    for(char c:s){
        if(st.empty()){
            st.push(c);
        } else if(st.top() == c){
            st.pop();
        } else st.push(c);

    }
    string result;
    while(!st.empty()){
        // char c = st.pop();  doesn't work
        result = st.top() + result;
        st.pop();
    }
    return result;
}

vector<int> greatestRightElement(vector<int> &nums){
    vector<int> result;
    stack<int> st;
    int max = INT_MIN;

    for(int x: nums){
        st.push(x);
    }
    max = st.top();
    result.push_back(-1);
    st.pop();
    while(!st.empty()){
        int temp = st.top();
        if(temp > max){
            max = temp;
            result.push_back(-1);
            st.pop();
        } else {
            result.push_back(max);
            st.pop();
        }
    }
    reverse(result.begin(), result.end());
    return result;
    
    //  this gives us greatest element to the right and not first great
}

vector<int> nextGreater(vector<int>& nums){
    stack<int> st;
    vector<int> result;

    for(int i=nums.size()-1; i>=0; i--){
        // idea is that if our top element is less than current element then it can't be the answer
        // as we are traversing from right to left
        while(!st.empty() && st.top() <= nums[i]){
            st.pop();
        }
        if(st.empty()) result.push_back(-1);
        else result.push_back(st.top());
        st.push(nums[i]);
    }
    reverse(result.begin(), result.end());
    // or can initialize result with(nums.size()) and add result[i]
    return result;
}

vector<int> dailyTemperatures(vector<int> &temperatures){
    stack<int> st;
    vector<int> result(temperatures.size());

    for(int i=temperatures.size()-1; i>=0; i--){

        // while(!st.empty() && st.top() <= temperatures[i]){
        while(!st.empty() && temperatures[st.top()] <= temperatures[i]){
            st.pop();
        }

        if(st.empty()){
            // result[i] = 0;
            result[i] = st.top() - i;
        }
        else result[i] = st.top();

        st.push(i);
    }

    // for(int i=0; i<result.size(); i++){
    //     result[i] = result[i] - i;
    // } 
    // no need for this loop, result[i] = st.top() - i;
    return result;
}

int main(){
    // stack<int> st;
    // st.push(10);
    // st.push(20);
    // st.push(30);

    // cout<< st.top;
    // st.pop();

    // ### Problem 1: valid parentheses


    // ### Problem 2: Remove adjacent duplicates
    // Given a string s, repeatedly remove adjacent equal characters.

    // ### Problem 3: Next Greater Element
    // For every element, find the first greater element to its right.
    // If no greater element exists, return -1.

    // ### Problem 4:Daily temperatures
    // For each day, find how many days you have to wait until a warmer temperature.

    return 0;
}