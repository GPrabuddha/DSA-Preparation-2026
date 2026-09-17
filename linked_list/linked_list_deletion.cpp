#include<bits/stdc++.h>
using namespace std;

struct Node{
    int value;
    Node *next;
};

void deleteNode(Node *&head, Node *target){
    // start with edge case head = current
    if(head == target){
        Node *tmp = head;
        head = head->next;
        delete tmp; 
        return;
    }
    // Node *prev = new Node(); 
    Node *prev = NULL;
    Node *current = head;
    while(current!=NULL && current!=target){
        prev = current;
        current = current->next;  
    }

    // another edge case if current == NULL i.e. no element found
    if(current == NULL){
        return;
    }
///// ************** main idea is prev->next = current->next
    prev->next = current->next;
    delete current;
    return;

}
void deleteValue(Node *&head, int value){
    // start with edge case
    if(head == NULL) return; 

    if(head->value == value){
        // head = head->next;
        Node *tmp = head;
        head = head->next;
        delete tmp;

        return;
    }
    Node *current = head;
    // we need prev pointer in case of deletion always remember
    Node *prev = NULL;
    while(current!= NULL && current->value != value){
        prev = current;
        current = current->next;
    }
    if(current == NULL){
        cout<< "element not found.";
        return;
    }
    prev->next = current->next;
    delete current;
    return;
}

int main(){


    return 0;
}