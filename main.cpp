#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node *next;

    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }

    static Node *root;
};

//Functions
void insert(int value);

void radixSort();

int getMax();

void transversal();

Node *Node::root = nullptr;

int main() {
    insert(50);
    insert(152);
    insert(27);
    radixSort();
}


//Simple Linked List Insertion
void insert(int value) {
    //New Node to be inserted
    Node *newNode = new Node(value);

    //If Root is Empty inserted at root
    if (Node::root == nullptr) {
        Node::root = newNode;
        return;
    }

    Node *current = Node::root;

    //If it is not inserted in root, then we will go to the end node
    while (current->next != nullptr) {
        current = current->next;
    }
    //inserteing New Node to endNode
    current->next = newNode;
//    cout << "Inserted at End" << endl;

}


void radixSort() {

    //Getting the Maximum number in the List
    int max = getMax();
    if (max == -1) {
        cout << "List is empty" << endl;
        return;
    }

    //This will contain the number of digits for the maximum number in the list
    int numberOfDigits = 0;
    while (max != 0) {
        max = max / 10;
        numberOfDigits++;
    }

    transversal();

    int exp = 1;

    //Now the numberOfDigits tells us about , how much time we should loop
    //As it will get us the maximum number of digits
    while (numberOfDigits != 0) {

        //This will store the Node in buckets with similar digits
        Node *count[10] = {};

        Node *current = Node::root;

//        cout << "Exp: " << exp << endl;

        //Now go from the start of the list to the end of the list
        while (current != nullptr) {

            //We Store the next Node of Current in a Temp variable and Make Current next as Null
            Node *tempNext = current->next;
            current->next = nullptr;

            int digit = (current->data / exp) % 10;

//            cout << "Number: " << current->data << endl;
//            cout << "Digit: " << digit << endl;

//            Now inserting the Node into Buckets based on digit
            if (count[digit] == nullptr) {
                //If digit Bucket is Empty
                count[digit] = current;

            } else {
                //If digit Bucket is not Empty
                //We Insert the Node at the end of list of nodes of that digit place
                Node *temp = count[digit];

                //Going to the end Node
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = current;//Inserting at end Node

            }

            //Making current node as the next Node
            current = tempNext;
        }

        //Now We need to need to update the list based on buckets
        //GO from the count ( 0 to 9 )
        Node *tempRoot = nullptr;//Temp List
        Node *endNode = nullptr; //Will be the Node we want to join the next list of similar digits to
        for (int i = 0; i <= 9; ++i) {
            if (count[i] == nullptr) {
                continue;
            }

            //Checking if our new List is Empty
            if (tempRoot == nullptr) {
                tempRoot = count[i];
            } else {
                endNode->next = count[i];
            }

            endNode = count[i];
            while (endNode->next != nullptr) {
                endNode = endNode->next;
            }

        }

        //Updating the List
        Node::root = tempRoot;

        transversal();

        exp = exp * 10;
        numberOfDigits--;
    }

}

//Return -1, if no element exists
//Else returns the max value
int getMax() {

    int max = -1;

    Node *current = Node::root;
    //Now we check the whole list to get the Max value in list
    while (current != nullptr) {

        if (current->data > max) {
            max = current->data;
        }
        current = current->next;
    }

    return max;
}

void transversal() {
    Node *current = Node::root;
    cout << "Transversal" << endl;
    while (current != nullptr) {
        cout << "Data: " << current->data << endl;
        current = current->next;
    }
}
