#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node *next;
};

void reverse(Node *&head){
    Node *prev = NULL;
    Node *current = head;
    Node *next;

    while(current!=NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev; // i had missed this case
}
int main(){


    return 0;
}