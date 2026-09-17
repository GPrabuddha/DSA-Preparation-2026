#include<bits/stdc++.h>
using namespace std;

int missingNumber(vector<int>& arr){
    int n = arr.size();
    long long expected_sum = (1LL * n * (n+1)) / 2;

    //long long x = n * n;        // multiplication happens as int
// long long x = 1LL * n * n;  // multiplication happens as long long
    long long observed_sum=0;
    for(int i=0; i<n; i++){
        observed_sum += arr[i];
    }
    return expected_sum - observed_sum;
}

int main(){

    return 0;
}