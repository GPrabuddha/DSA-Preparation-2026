#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node *next;
};

void insertAfter(Node* current, int value) {
    Node* newNode = new Node();
    newNode->data = value;

    newNode->next = current->next;
    current->next = newNode;
}
// modify insertafter code to insertbefore
void insertBefore(Node* head, Node* current, int value){
    Node* newNode = new Node();
    newNode->data = value;

    // account for edge case: head == current
    if (head==current){
        newNode->next = current;
        head = newNode;
        return ;
    }

    newNode->next = current;
    Node* tmp = head;
    while(tmp->next != current){
        tmp = tmp->next;
    }
    tmp->next = newNode;
}

int main(){
    Node *head = new Node();
    head->data = 10;
    head->next = nullptr;

    cout<< "Data in node is " << head->data;



    return 0;
}

