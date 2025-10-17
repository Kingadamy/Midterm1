#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; // declaration for min and max values

class DoublyLinkedList { // create doubly linked list class
private:
    struct Node {  // create node struct for doubly linked list

        int data; // int for data
        Node* prev; // points to previous node
        Node* next; // points to next node

        // creates new node with a value and option to go to previous and next nodes
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; // store value in data
            prev = p;   // points to previous node
            next = n;   // points to next node
            // these deault to nullptr if not given
        }
    };

    Node* head;    // points to head of list
    Node* tail;    // points to tail of list
public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }  // constructor to create an empty doubly linked list


    void insert_after(int value, int position) {  // inserts a new node with given value after the given position
        if (position < 0) { // check if the position is valid
            cout << "Position must be >= 0." << endl;
            return; // exits the function if position is invalid
        }

        Node* newNode = new Node(value); // creates memory for new node with the given value
        if (!head) {
            head = tail = newNode; // both head and tail point to the same node
            return; // exit function if list was empty
        }

        Node* temp = head; // temp pointer to traverse the list
        for (int i = 0; i < position && temp; ++i) // traverse to the given position
            temp = temp->next; // move to next node

        if (!temp) { // if temp = nullptr, we are past the end of the list
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // frees memory allocated for new node
            return; 
        }

        newNode->next = temp->next; // new node points to the node after temp
        newNode->prev = temp;       // new node points back to temp (node before it)
        if (temp->next)         // if temp is not the tail
            temp->next->prev = newNode;   // node after temp points back to new node
        else
            tail = newNode;       // if temp was the tail then we update tail to new node
        temp->next = newNode;      // temp now points to new node
    }



    void delete_val(int value) { // deletes the first node with the given value
        if (!head) return; // if list is empty, quit the function

        Node* temp = head;  // start search from head of list
        
        while (temp && temp->data != value)   // traverse the list to find the value
            temp = temp->next; // move to next node

        if (!temp) return; // if there is no value to delete, quit the function

        if (temp->prev)  //if the node to delete is not the head
            temp->prev->next = temp->next;  // previous node will skip over temp
        else
            head = temp->next; // if the temp is head then update head to next node

        if (temp->next) // if the node to delete is not the tail
            temp->next->prev = temp->prev; // next node will skip over temp
        else
            tail = temp->prev; // if the temp is tail then update tail to previous node

        delete temp; // free memory used for temp
    }


    void delete_pos(int pos) { // function to delete node at given position
        if (!head) { // check if list is empty
            cout << "List is empty." << endl;  
            return;  // if the list is empty exit the function
        }
    
        if (pos == 1) { // if position is 1 we need to delete the head
            pop_front(); // call for pop front to delete head
            return; 
        }
    
        Node* temp = head; // start from head to traverse the list
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}