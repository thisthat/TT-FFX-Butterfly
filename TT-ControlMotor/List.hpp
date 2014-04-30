#include <string>

using namespace std;


class List {

    struct Node {
        string data;
        Node * next;
    };

    Node * head;
    Node * last;

public:
    List() {
        head = last = NULL;
    }

    ~List() {
        while(head != NULL) {
            Node * n = head->next;
            delete head;
            head = n;
        }
    }

    bool isEmpty(){ return head == NULL;}

    void add(string msg);
    string take();
};