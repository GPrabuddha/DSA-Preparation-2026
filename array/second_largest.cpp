#include<bits/stdc++.h>
using namespace std;

// int secondLargest(vector<int>& arr){
// // ** first try

//     // int max = 0; int sec_max = 0;
//     int max = INT_MIN; int sec_max = INT_MIN;
//     for(int i=0; i<arr.size(); i++){
//         if(arr[i]>max) {
//             sec_max = max;
//             max = arr[i];
//         }
//     }
// return sec_max;
// }

// int secondLargest(vector<int>& arr){
//     int max = arr[0];
//     int second_max;
//     for(int i=1; i<arr.size(); i++){
//         if(arr[i] > max){
//             second_max = max;
//             max = arr[i];
//         }
//     }
//     return second_max;
// }

int secondLargest(vector<int> &arr){
    int max, second_max;
    if(arr[0]>arr[1]){
        max = arr[0];
        second_max = arr[1];
    } else {
        max = arr[1];
        second_max = arr[0];
    }

    for(int i=2; i<arr.size(); i++){
        if(arr[i]>max){
            second_max = max;
            max = arr[i];
           
        }
        else if(arr[i]>second_max){
            second_max = arr[i];
        }
    }
    if(max == second_max) return 0;
    return second_max;
}

int main(){
    vector<int> arr;
    for(int i=0; i<10; i++){
        arr.push_back(i);
    }
    for(int i=0; i<arr.size(); i++){
        cout<<arr[i];
    }
    int sec_lar = secondLargest(arr);
    cout<<endl<<"second largest in an array: "<<sec_lar;
    return 0;
}