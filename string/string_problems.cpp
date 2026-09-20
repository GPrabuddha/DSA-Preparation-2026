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

string removeCharacter(string s, char target){
    int i = 0;
    string result;
    while(i<s.size()){
        if(s[i] != target){
            result += s[i];
            i++;
        } else i++;
    }
    return result;
}

string removeDuplicates(string s){
    // Question to ask for duplicate is have i already seen this?
    // whenever have i seen this comes think of HASHSET
    unordered_set<char> seen;
    string result;

    for(char c:s){
        if(seen.count(c)){
            continue;
        }
        seen.insert(c);
        result += c;
    }
    return result;
}

bool isAnagram(string s, string t){
    // anagrams contain same freq of same char
    unordered_map<char,int> freq_s;
    unordered_map<char,int> freq_t;

    // can also be done with single map think of subtraction

    if(s.size() != t.size()){
        return false;
    }
    for(char c:s){
        freq_s[c]++;
    }
    for(char c:t){
        freq_t[c]++;
    }

    for(auto p:freq_s){
        if(p.second != freq_t[p.first]){
            return false;
        }
    }
    return true;
}

char firstUniqueChar(string s){
    // naive approach, as we are concerned with how many times i have seen this, think of HASHMAP
    // it is asking first unique element, ordering matters so use array for this (string is an array of char)

    unordered_map<char, int> freq;
    // generate frequency map first
    for(char c:s){
        freq[c]++;
    }

    // iterate over string to preserve order
    for(char c:s){
        if(freq[c]==1) return c;
    }
    return '\0';
    // '\0' is the null character, commonly used here to indicate "no character found."
}

// int longestSubstring(string s){
//     // duplicate is if i have already seen this char -> use HASHSET
//     int left = 0;
//     int right = 0;
//     unordered_set<char> seen;
//     int ans = 0;

//     for(int i=0; i<s.size(); i++){
//         // int length; 

// **********
// When shrinking, use a while, not necessarily an if, 
// because you may need to remove multiple elements before the window becomes valid.

//         if(seen.count(s[i])){
//             seen.erase(s[i]);
//             left++;
//         }
//         else {
//             right++;
//             seen.insert(s[i]);
//         }
//         ans = max(ans, right - left + 1);


//     }
//     return ans;
// }

int longestSubstring(string s){
    int left = 0;
    unordered_set<char> seen;
    int ans=0;

    for(int right=0; right<s.size(); right++){

        while(seen.count(s[right])){
            seen.erase(s[left]);
            left++;
        }
        seen.insert(s[right]);

        ans = max(ans, right - left + 1);
    }
}
// Sliding window pattern
// right → expand window

//         ↓

// condition violated?

//         ↓ yes

// left → shrink window

//         ↓

// condition valid again

//         ↓

// update answer

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


    // ### Problem 4: Remove a character
    // Given a string s and a character target, remove all occurrences of target and return the resulting string.

    // ### Problem 5: Remove Duplicate Characters
    // Given a string, remove duplicate characters while keeping the first occurrence of each character.

    // ### Problem 6: First Non-Repeating Character
    // Given a string s, return the first character that occurs exactly once.

    // ### Problem 7: Valid anagram
    // Given two strings s and t, determine whether t is an anagram of s.

    // ### Problem 8: Longest Substring Without Repeating Characters
    // Given a string s, find the length of the longest substring that contains no repeated characters.
    // what is a substring? -> it is a contiguous part of a string
    return 0;
}