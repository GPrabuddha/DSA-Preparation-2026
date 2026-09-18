#include<bits/stdc++.h>
using namespace std;

int countVowels(string s){
    int count = 0;
    for(int i=0; i < s.size(); i++){
        if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u'){
            count++;
        }
    }
    return count;
}

bool isPalindrome(string s){
    int left = 0;
    int right = s.size() - 1;

    while(left<right){
        // if(!isalnum(tolower(s[left]))){ //lower not needed as it works on any character and digit
        if(!isalnum(s[left])){
            left++;
            continue;
        }
        if(!isalnum(s[right])){
            right--;
            continue;
        }
        if(tolower(s[left]) == tolower(s[right])){
            left++;
            right--;
        } else return false;
    }
    return true;
}

vector<string> getWords(string s){
    // flow is we are outside a word -> encounter nonspace -> word starts at i -> encounter space -> word ends at i-1 -> add the word
    vector<string> words;
    // for(char c: s){ // need indexes so don't use this
    // for(int i=0; i<s.size(); i++){
    int i=0;
    while(i < s.size()){
        // we are outside a word (when we encounter nonspace we enter the word)
        if(!isspace(s[i])){
            // we are inside a word
            int start = i;
            // int end = i; not needed as we are recording i in start
            // while(!isspace(s[i+1])){ // i was accessing i+1 without checking what it is, wrong
            

            while(i<s.size() && !isspace(s[i])){
                i++;
            }
            // loop end means word ends it is a space there we get our word
            words.push_back(s.substr(start, i-start));

        }
        else i++;

    }
    return words;
}

string reverseWords(string s){
    vector<string> words = getWords(s);
    string result;
    // for(string s: words){ //need reverse string
    //     result += s;
    // }

    for(int i=words.size()-1; i>0; i--){
        result += words[i];

        if(i!=0){
            result+= " ";
        }
    }
    return result;

}

int main(){
    // string s = "hello";

    // cout<<s[0]<< endl;
    // cout<<s[1]<<endl;

    // // we can also modify string 
    // s[0] = 'H';
    // cout<<"string length: "<< s.length()<<endl; // for string length s.size() or s.length() both work

    // // Traverse a string
    // for(char c: s){
    //     cout<<c;
    // }
    // cout<<('h');

    // problem 1 : count vowels a, e, i, o, u


    // string s = "Hello123 World!";
    // count:
    //     Number of alphabets
    //     Number of digits
    //     Number of spaces
    //     Number of other characters
    // int alpha=0, digi=0, spac=0, othc = 0;
    // for(int i=0; i<s.size(); i++){
    //     if(isalpha(s[i])){
    //         alpha++;
    //     }
    //     if(isdigit(s[i])){
    //         digi++;
    //     }
    //     if(isspace(s[i])){
    //         spac++;
    //     }
    //     if(!isalnum(s[i]) && !isspace(s[i])){
    //         othc++;
    //     }
    // }
    // cout<< alpha<<digi<<spac<<othc;


    // ### problem 2 Valid palindrome
    // Given a string s, determine whether it is a palindrome after:

    //     converting uppercase letters to lowercase
    //     ignoring all non-alphanumeric characters
    //     Input:  "A man, a plan, a canal: Panama"
    //     Output: true

    // ### Problem 3: Reverse words in a string
    return 0;
}