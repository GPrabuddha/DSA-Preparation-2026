#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node *next;
};

Node* find_middle(Node *head){
    // Node *slow = head->next;
    // Node *fast = head->next->next;
    
    // while(slow!=NULL && fast != NULL){
    //     slow = slow->next;
    //     fast = fast->next->next;
    // }
    // return slow;

    Node *slow = head;
    Node *fast = head;
    while(fast!=NULL && fast->next!=NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
// find cycle given a linked list
bool find_cycle(Node *head){
    Node *slow = head;
    Node *fast = head;

    while(fast!=NULL && fast->next!=NULL){
        slow = slow->next;
        fast = fast->next->next;
        if(slow==fast) return true;
    }
    return false;
}

//find start of cycle
Node * start_of_cycle(Node *head){
    // Node *slow = head;
    // Node *fast = head;

    // while(fast!=NULL && fast->next!=NULL){
    //     slow = slow->next;
    //     fast = fast->next->next;
    //     if(slow==fast) return slow;
    // }
    // return NULL;


        Node *slow = head;
    Node *fast = head;

    while(fast!=NULL && fast->next!=NULL){
        slow = slow->next;
        fast = fast->next->next;
        if(slow==fast) break;
    }

    slow = head;
    while(slow!=fast){
        slow=slow->next;
        fast=fast->next;
    }
    return slow;
}

int main(){

    return 0;
}