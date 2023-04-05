#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

struct Node { // node of linked list
    int i_var = 0;      // data
    Node* next = NULL;  // link to the next node
    Node() {
    }
    Node(int value) {
        i_var = value;
    }
};

Node* head_ptr = NULL; // head pointer of the linked list

// at a node to the end of the linked list
void Append(Node* newNode_ptr) {
    //Write your code below
    if (head_ptr == NULL)
    {
        head_ptr = newNode_ptr;
    }

    else
    {
        Node* current_ptr = head_ptr;
        while (current_ptr->next != NULL)
        {
            current_ptr = current_ptr->next;
        }
        current_ptr->next = newNode_ptr;
    }
    // Write your code above
}

// insert a node at the given position
void InsertNodeAtPosition(Node* newNode_ptr, int position) {
    //Write your code below
    if (position < 0) {
        return;
    }

    Node* current_ptr = head_ptr;
    int currentPos = 0;

    if (head_ptr == NULL) 
    {
        head_ptr = newNode_ptr;
    }

    else if (position == 0)
    {
        newNode_ptr->next = head_ptr;
        head_ptr = newNode_ptr;
    }

    else 
    {
        while (current_ptr->next != NULL && currentPos < position - 1) 
        {
            current_ptr = current_ptr->next;
            currentPos++;
        }
        newNode_ptr->next = current_ptr->next;
        current_ptr->next = newNode_ptr;
    }
    // Write your code above
}

// remove a node at the given position
void RemoveNodeAtPosition(int position) {
    //Write your code below

    if (head_ptr == NULL)
    {
        return;
    }

    else if (position == 0)
    {
        head_ptr = head_ptr->next;
    }

    else
    {
        Node* prev_ptr = head_ptr;

        for (int i = 0; i < position - 1; i++)
        {
            prev_ptr = prev_ptr->next;
        }

        Node* current_ptr = prev_ptr->next;
        prev_ptr->next = current_ptr->next;
        delete current_ptr;
    }
    // Write your code above
}

// change the value at the given position
void ChangeValueAtPosition(int position, int value) {
    //Write your code below

    if (head_ptr == NULL)
    {
        return;
    }

    Node* current_ptr = head_ptr;
    int currentPos = 0;

    while (currentPos < position && current_ptr != NULL) 
    {
        current_ptr = current_ptr->next;
        currentPos++;
    }

    if (current_ptr != NULL) {
        current_ptr->i_var = value;
    }
    // Write your code above
}

// print the data of all nodes
void PrintAllNodes() {
    //Write your code below
    if (head_ptr == NULL)
    {
        printf("ERROR: LIST IS EMPTY!");
    }

    Node* i_ptr = head_ptr;

    while (i_ptr != NULL) 
    {
        printf("%d->", i_ptr->i_var);
        i_ptr = i_ptr->next;
    }

    printf("NULL\n");
    // Write your code above
}

int main()
{
    // add 5 nodes
    cout << "1) Append 5 nodes: " << endl;
    Append(new Node(0));
    Append(new Node(1));
    Append(new Node(2));
    Append(new Node(3));
    Append(new Node(4));

    PrintAllNodes();
    cout << endl;

    // remove the node at position 2 (the third node)
    cout << "2) Remove the node at position 2: " << endl;
    RemoveNodeAtPosition(2);
    PrintAllNodes();
    cout << endl;

    // insert a node at position 2
    cout << "3) Insert a node at position 2: " << endl;
    InsertNodeAtPosition(new Node(2), 2);
    PrintAllNodes();
    cout << endl;

    // change the value of node at position 2
    cout << "4) Change the value of node at position 2: " << endl;
    ChangeValueAtPosition(2, 20);
    PrintAllNodes();
    cout << endl;

    // insert a node at position 0 (head)
    cout << "5) Insert a node at position 0: " << endl;
    InsertNodeAtPosition(new Node(100), 0);
    PrintAllNodes();
    cout << endl;

    // remove a node at position 0 (remove the head)
    cout << "6) Remove the first node: " << endl;
    RemoveNodeAtPosition(0);
    PrintAllNodes();
    cout << endl;

    return 0;
}