#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

#define MAXIMUM_SIZE 100

int adjacentMatrix[MAXIMUM_SIZE][MAXIMUM_SIZE] = { 0 }; // adjacent matrix used to save the graph
int size_node; // the number of nodes

struct PlaySequence {
	int prerequisite;
	int card;
};
//The player needs to play prerequisite to play card.

// build the graph
void BuildGraph(int cardCount, int sequenceCount, PlaySequence* sequences) {
	size_node = cardCount;

	for (int i = 0; i < sequenceCount; i++) {
		adjacentMatrix[sequences[i].prerequisite][sequences[i].card] = 1;
	}
}

//Finialize this method. You may define new methods that are called by this method.
bool PlayCard(int initialCard, int targetCard) {

    queue<int> queue;

    bool visited[MAXIMUM_SIZE] = { false };
    int steps[MAXIMUM_SIZE] = { 0 };
    int prev[MAXIMUM_SIZE] = { -1 };

    visited[initialCard] = true;

    queue.push(initialCard);

    while (!queue.empty()) 
    {
        int curr = queue.front();
        queue.pop();

        if (curr == targetCard) 
        {
            cout << "Initial Card: " << initialCard << ". Target Card: " << targetCard << ". Play Sequence: ";
            stack<int> stack;
            int node = curr;

            while (node != initialCard) 
            {
                stack.push(node);
                node = prev[node];
            }
            cout << initialCard << " ";

            while (!stack.empty()) 
            {
                cout << stack.top() << " ";
                stack.pop();
            }

            cout << "\n# of played cards: " << steps[curr] + 1 << endl;

            return true;
        }

        for (int i = 0; i < size_node; i++) 
        {
            if (adjacentMatrix[curr][i] == 1 && !visited[i]) 
            {
                visited[i] = true;
                queue.push(i);
                prev[i] = curr;
                steps[i] = steps[curr] + 1;
            }
        }
    }

    cout << "Initial Card: " << initialCard << ". Target Card: " << targetCard << ". Can't play target card." << endl;

    return false;
}

int main() {
	PlaySequence sequences[] = {
		{0, 2}, {6, 2}, {6, 8}, {0, 3}, {1, 0}, {2, 1},
		{5, 6}, {8, 5}, {8, 7}, {1, 3}, {1, 5}, {5, 9},
		{3, 4}, {4, 9}, {4, 1}, {5, 4}, {9, 0}, {7, 9}
	};
	int cardCount = 10;
	int sequenceCount = 18;

	BuildGraph(cardCount, sequenceCount, sequences);

	PlayCard(0, 9);

	return 0;
}