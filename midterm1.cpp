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
    
        for (int i = 1; i < pos; i++){ // traverse to the given position we use i < pos because we start at 1
            if (!temp) {    // check if we reached the end of the list
                cout << "Position doesn't exist." << endl;
                return; // exit the function if position is invalid
            }
            else
                temp = temp->next;  // moves to next node
        }
        if (!temp) { // after the loop check if position is valid
            cout << "Position doesn't exist." << endl;
            return;  // ewxit the function if position is invalid
        }
    
        if (!temp->next) { // this is a special case if we need to delete the tail
            pop_back(); // use function for deleting the tail
            return;  
        }
    
        Node* tempPrev = temp->prev; // store pointer to previous node
        tempPrev->next = temp->next; // the next node skips over temp and points to the node after temp
        temp->next->prev = tempPrev; // the previous node skips over temp and points back to the node before temp
        delete temp;
    }

    void push_back(int v) { // adds new node with value "v" to the end of the list
        Node* newNode = new Node(v); // create new node with value v
        if (!tail)      // if list is empty
            head = tail = newNode; // becomes both head and tail
        else {
            tail->next = newNode; // if the list is not empty then tail's next points to new node
            newNode->prev = tail; // new nodes prev points to current tail
            tail = newNode; // update tail to new node 
        }
    }
    
    void push_front(int v){  // adds new node "v" to the front of the list
        Node* newNode = new Node(v);  // create new node with value v
        if (!head)  // if list is empty
            head = tail = newNode; // becomes both head and tail
        else {
            newNode->next = head; // since the list is not empty we add before the current head
            head->prev = newNode; // current head's prev points to new node
            head = newNode; // update head to new node
        }
    }
    
    void pop_front() {  // removes the node at the front of the list

        if (!head) { // check if list is empty
            cout << "List is empty." << endl;
            return; // exits function if list is empty
        }

        Node * temp = head; // stores the pointer to the current head

        if (head->next) { // if there is more than one node in the list
            head = head->next; // move head to next node
            head->prev = nullptr; // new head has no previous node
        }
        else
            head = tail = nullptr; // if there was only one node then list is now empty
        delete temp; // free memory used for old head
    }

    void pop_back() { //removes last node from the list
        if (!tail) { // check if list is empty
            cout << "List is empty." << endl;
            return; // if list is empty exit function
        }
        Node * temp = tail; // stores pointer at tail node

        if (tail->prev) { // if there is more than one node in the list 
            tail = tail->prev; // move tail to previous node
            tail->next = nullptr; // new tail has no next node
        }
        else
            head = tail = nullptr; // if there was only one node then list is now empty
        delete temp; // free memory used for old tail
    }

    ~DoublyLinkedList() { // creates a free function to delete all nodes when the list is destroyed also prevents memory leaks
        while (head) { // while there are still nodes in the list
            Node* temp = head; // store pointer to current head
            head = head->next; // move head to next node
            delete temp; // delete old head node
        }
    }
    void print() { // prints the list from head to tail
        Node* current = head; // start from head
        if (!current) { // check if list is empty
            cout << "List is empty." << endl;
            return; // if list is empty exit function
        }
        while (current) { // traverse the list 
            cout << current->data << " "; // prints current node
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