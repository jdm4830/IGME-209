#include <stdio.h>
#include <iostream>
#include <queue>

using namespace std;

struct Node {
	int value = 0;
	Node* left = NULL;
	Node* right = NULL;

	Node() {

	}

	Node(int v) {
		value = v;
	}
};

void SwapChildren(Node* root) {
	//Write your code below

	//If the root, left leaf or right leaf are null, return!
	if (root == NULL || (root->left == NULL && root->right == NULL)) {	return;	}

	//make temp node to hold left and right
	Node* temp = root->left;

	//swap nodes, give right the temp
	root->left = root-> right;
	root->right = temp;

	//recursively go trough swapping left and right children of each subtree
	SwapChildren(root->left);
	SwapChildren(root->right);

	//Write your code above
}

void PrintBinaryTree(Node* root) {
	queue<Node*> m_queue;
	m_queue.push(root);

	while (m_queue.empty() == false) {
		Node* node = m_queue.front();
		m_queue.pop();
		if (node != NULL) {
			cout << node->value << " ";
			m_queue.push(node->left);
			m_queue.push(node->right);
		}
	}
	cout << endl;
}


int main() {

	Node* root = new Node(0);
	Node* node1 = new Node(1);
	Node* node2 = new Node(2);//0
	root->left = node1;//      / \ 
	root->right = node2;//    1   2  | 1 and 2 are the children of 0

	Node* node3 = new Node(3);
	Node* node4 = new Node(4);//1
	node1->left = node3;//     / \ 
	node1->right = node4;//   3   4  | 3 and 4 are the children of 1

	Node* node5 = new Node(5);//4
	//                        /
	node4->left = node5;//   5 | 5 is the child of 4

	Node* node6 = new Node(6);//2
	//                           \ 
	node2->right = node6;//       6  | 6 is the child of 2

	Node* node7 = new Node(7);//6
	//                        /
	node6->left = node7;//   7 | 7 is the child of 6

	//Visualize: 
	//           0
	//         /   \ 
	//        1     2
	//       / \     \
	//      3   4     6
	//         /     /
	//        5     7

	cout << "Original: ";
	PrintBinaryTree(root);
	SwapChildren(root);
	cout << "After: ";
	PrintBinaryTree(root);

	return 0;
}