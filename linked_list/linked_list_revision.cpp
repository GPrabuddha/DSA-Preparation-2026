#include<bits/stdc++.h>
using namespace std;


struct Node{
    int data;
    Node *next;
};

void InsertAfter(Node *current, int data){
    Node *tmp = new Node();
    tmp->data = data;
    tmp->next = current->next;
    current->next = tmp;
}

void InsertBefore(Node *head, Node *current, int data){
 // typical idea: 1. first create new node
 // 2. add data then think about which pointer to modify so that we don't lose info
 Node *tmp = new Node();
 tmp->data=data;
//edge case
 if(current ==head){
    tmp->next=head;
    head=tmp;
    return;
 }

 tmp->next=current;

 Node *curr = head;
 while(curr!=NULL && curr->next!=current){
    curr = curr->next;
 }
curr->next=tmp;
}

int main(){

    // make new node
    Node *head = new Node();
    Node *curr = head;
    for(int i=0; i<10; i++){
        curr -> data = i;
        if(i==9){
            curr->next = NULL;
        }
        else {
        // Node *temp = new Node();
        // curr -> next = temp;
        curr->next = new Node();
        curr = curr->next;
        }
    }
    Node *tmp = head;
    while(tmp!=NULL){
        cout<< tmp->data<<endl;
        tmp = tmp->next;
    }
    // cout << head->data<<endl<<head->next->data;

    return 0;
}