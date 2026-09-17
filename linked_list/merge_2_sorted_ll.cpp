#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node *next;
};

Node * merge_2_ll(Node *&head1, Node *&head2){
    Node *current1 = head1;
    Node *current2 = head2;
    Node *merged_head = NULL;
    if(current1->data < current2->data) merged_head = head1;
    else merged_head = head2;

    Node *merged_tail = NULL;

    while(current1!=NULL || current2!=NULL){
        if(current1 == NULL){
            merged_tail = current2;
            return merged_head;
        }

        if(current2 ++ NULL){
            merged_tail = current1;
            return merged_head;
        }

        if(current1->data < current2->data){
            current1->next = current2;
            current1 = current1->next;
            merged_tail = current2;
        } else {
            current2->next = current1;
            current2 = current2->next;
            merged_tail = current1;
        }
        // if(current1 != NULL){
        //     current1 = current1->next;
        // }
        // if(current2 != NULL){
        //     current2 = current2->next;
        // } // I had written this first but looks like it is unnecessary
    }
    return merged_head;
}



int main(){
    Node *l1 = new Node();
    Node *l2 = new Node();

    
    // for(int i=1; i<=7; i=i+2){
    //     l1->data = i;
    //     if(i!=7){
    //     Node *tmp = new Node();
    //     l1->next = tmp;
    //     l1 = tmp;}
    // }  // **** Remember not to modify the original head
    Node *tmp1 = l1;


    // **** remember in for loop they are statements therefore use ; and not ,
    for(int i=1; i<=7; i=i+2){
        tmp1->data=i;
        if(i!=7){
            Node *tmp = new Node();
            tmp1->next = tmp;
            tmp1 = tmp;
        }
    }

    Node *tmp2 = l2;
    for(int i=2; i<=8; i=i+2){
        tmp2->data = i;
        if(i!=8){
            Node *tmp = new Node();
            tmp2->next = tmp;
            tmp2 = tmp;
        }
    }


    Node *current1 = l1;
    while(current1!=NULL){
        cout<<current1->data<<"->";
        current1 = current1->next;
    }

    cout<< endl;
    Node *current2 = l2;
    while(current2!=NULL){
        cout<< current2->data<<"->";
        current2 = current2->next;
    }
    Node *merged = merge_2_ll(l1, l2);
    Node *current3 = merged;
    while(current3!=NULL){
    cout<<current3->data<<"->";
    current3 = current3->next;
    }

    return 0;
}