#include "List.hpp"



void List::add(string value) {
    Node * n = new Node;
    n->data = value;
    n->next = NULL;    
    if(head != NULL){
        last->next = n;
        last = n;
    }
    else{
        head = last = n;
    }
}

string List::take() {
    Node *n = new Node;
    n = head;
    head = head->next;
    string msg = n->data;
    delete n;
    return msg;
}
