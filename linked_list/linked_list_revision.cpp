// #include<bits/stdc++.h>
// using namespace std;


// struct Node{
//     int data;
//     Node *next;
// };

// void InsertAfter(Node *current, int data){
//     Node *tmp = new Node();
//     tmp->data = data;
//     tmp->next = current->next;
//     current->next = tmp;
// }

// void InsertBefore(Node *head, Node *current, int data){
//  // typical idea: 1. first create new node
//  // 2. add data then think about which pointer to modify so that we don't lose info
//  Node *tmp = new Node();
//  tmp->data=data;
// //edge case
//  if(current ==head){
//     tmp->next=head;
//     head=tmp;
//     return;
//  }

//  tmp->next=current;

//  Node *curr = head;
//  while(curr!=NULL && curr->next!=current){
//     curr = curr->next;
//  }
// curr->next=tmp;
// }

// int main(){

//     // make new node
//     Node *head = new Node();
//     Node *curr = head;
//     for(int i=0; i<10; i++){
//         curr -> data = i;
//         if(i==9){
//             curr->next = NULL;
//         }
//         else {
//         // Node *temp = new Node();
//         // curr -> next = temp;
//         curr->next = new Node();
//         curr = curr->next;
//         }
//     }
//     Node *tmp = head;
//     while(tmp!=NULL){
//         cout<< tmp->data<<endl;
//         tmp = tmp->next;
//     }
//     // cout << head->data<<endl<<head->next->data;

//     return 0;
// }



#include<bits/stdc++.h>
using namespace std;

// Todo: 1. Create SL Node and SL2. Iterate through SL 3. InsertAfter 4. InsertBefore 5.Delete a node by address
// 6. Delete a node by value

// 1.1 Create a node 
struct Node{
    int data;
    Node *next;
};


// 3 InsertAfter
void insertAfter(Node *current, int data){
    Node *tmp = new Node();
    tmp->data = data;
    tmp->next = current->next;
    current->next = tmp;
}

// 4 InsertBefore
void insertBefore(Node *head, Node *current, int data){
    Node *tmp = new Node();
    // insert before current can be though of as insertAfter prev of current

    // Goal 1 find previous of current, run insertAfter after that
    Node *ite = head;
    while(ite->next!=current){
        ite=ite->next; // we check fot the node whose next is current therefore after loop ends we have our desired pointer
    }
    // Goal 2 insertAfter ite
    insertAfter(ite, data);
}
// doesn't handle the case where we are updating head


// 5. Delete node by address
void deleteNode(Node *&head, Node *target){  // do &head otherwise head is passed by value, need with edge case head==target
    Node *tmp = head;  // always create a temp variable while iterating a sl, to preserve head ptr

    // think about whose pointer need to change and what pointer need to change
    // here prev node's next need to point to target next


    // edge cases
    if(head == nullptr || target == nullptr){
        return;
    }

    if(head==target){
        head = head->next;
        delete target;
        return;
    }

    // goal 1: find prev. of target
    while(tmp->next != target){
        tmp=tmp->next;
    }
    // tmp now has ptr to prev node of target

    // goal 2: delete target
    tmp->next = target->next;
    // delete tmp; // tmp is prev node we don't want to delete it **bug
    delete target;
}

// 6. Delete Node by value
void deleteValue(Node *&head, int data){
    Node *tmp = head;
    // edge cases
    if(head == NULL){
        return;
    }
    if(head->data == data){
        head= head->next;
        delete tmp;
        return;
    }

    // while(tmp->next->data != data){  // causes error if tmp->next is NULL
    while(tmp->next != NULL && tmp->next->data !=data){
        tmp = tmp->next;
    }
    if(tmp->next == NULL){
        return; // value not found
    }
    // tmp is prev pointer now
    Node *toDelete = tmp->next;
    tmp->next = toDelete->next;
    delete toDelete;
}

int main(){
    // 1.2 Create a singly linked list
    Node *head = new Node();
    Node *tmp = head;

    for(int i=0; i<10; i++){
         tmp->data = i;
         if(i!=9){
         Node *new1 = new Node();
         tmp->next = new1;
         tmp = new1;
         }
    }

    // 2. Iterate through SL
    Node* ite = head;
    while(ite!=NULL){
        // print sl data
        cout << ite->data << ", ";
        cout << ite<<", "<< endl;
        ite = ite->next;
    }

}