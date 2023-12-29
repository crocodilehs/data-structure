#include <iostream>
#include <sstream>

using namespace std;

typedef struct node {
    int val;
    node* next;
    node(int x) : val(x), next(nullptr){};
} node;
node* head = nullptr;

void ADD(int num) {
    node* newNode = new node(num);
    if (!head) {
        head = newNode;
    } else {
        node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
void INSERT(int num, int index) {
    node* newNode = new node(num);
    node* temp = head;
    if (index == 0) {
        newNode->next = temp;
        head = newNode;
    } else {
        while (--index) {
            temp = temp->next;
            if (!temp) {
                cout << "Index is out of range!!"
                     << "\n";
                return;
            }
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}
void DELETE(int index) {
    node* dummyHead = new node(0);
    dummyHead->next = head;
    node* temp = dummyHead;
    while (--index) {
        temp = temp->next;
        if (!temp->next) {
            cout << "Index is out of range!!"
                 << "\n";
            return;
        }
    }
    node* ptr = temp->next;
    temp->next = temp->next->next;
    delete (ptr);
    head = dummyHead->next;
    delete (dummyHead);
}
void REVERSE() {
    node *pre = nullptr, *cur = head, *temp;
    while (cur) {
        temp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = temp;
    }
    head = pre;
}
void printList() {
    node* temp = head;
    cout << temp->val;
    temp = temp->next;
    while (temp) {
        cout << " " << temp->val;
        temp = temp->next;
    }
    cout << "\n";
}

int main() {
    string input;
    while (getline(cin, input)) {
        stringstream ss(input);
        string action;
        ss >> action;
        if (action == "ADD") {
            int val;
            ss >> val;
            ADD(val);
            printList();
        } else if (action == "INSERT") {
            int val, target;
            string behind;
            ss >> val >> behind >> target;
            INSERT(val, target);
            printList();
        } else if (action == "DELETE") {
            int target;
            ss >> target;
            DELETE(target);
            printList();
        } else if (action == "REVERSE") {
            REVERSE();
            printList();
        }
    }
}
/*
ADD 5
ADD 10
ADD 90
INSERT 11 BEHIND 1
DELETE 4
INSERT 9 BEHIND 5
REVERSE
*/
/*
out put
5
5 10
5 10 90
5 11 10 90
5 11 10
Index is out of range!!
5 11 10
10 11 5
*/
/*
ADD 10
INSERT 6 BEHIND 5
INSERT 6 BEHIND 0
REVERSE
ADD 1
REVERSE
ADD 3
DELETE 2
DELETE 5
INSERT 11 BEHIND 3
REVERSE
*/
/*out put
10
Index is out of range!!
10
6 10
10 6
10 6 1
1 6 10
1 6 10 3
1 10 3
Index is out of range!!
1 10 3
1 10 3 11
11 3 10 1
*/