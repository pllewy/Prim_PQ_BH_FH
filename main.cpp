#include <iostream>
#include "FibonacciHeap.h"

using namespace std;

void FH_Use() {
    FH fibonacciHeap;

    // FH_Insert nodes into the Fibonacci Heap
    auto node1 = FH_Node(5);
    auto node2 = FH_Node(3);
    auto node3 = FH_Node(7);

    fibonacciHeap = FH_Insert(&fibonacciHeap, &node1);
    fibonacciHeap = FH_Insert(&fibonacciHeap, &node2);
    fibonacciHeap = FH_Insert(&fibonacciHeap, &node3);

    FH_Print(&fibonacciHeap);

    // Extract the FH_Minimum FH_Node
    FH_Node minNode = FH_Extract_Min(&fibonacciHeap);
    cout << "FH_Minimum FH_Node: " << minNode.key << endl;
    FH_Print(&fibonacciHeap);

    // Decrease key of a FH_Node
    FH_Decrease_Key(&fibonacciHeap, &node3, 2);
    FH_Print(&fibonacciHeap);

    // Extract the new FH_Minimum FH_Node
    minNode = FH_Extract_Min(&fibonacciHeap);
    cout << "New FH_Minimum FH_Node: " << minNode.key << endl;
    FH_Print(&fibonacciHeap);

    // FH_Delete a FH_Node
    FH_Delete(&fibonacciHeap, &node1);
    FH_Print(&fibonacciHeap);

    // Extract the new FH_Minimum FH_Node after deletion
    minNode = FH_Extract_Min(&fibonacciHeap);
    cout << "FH_Minimum FH_Node after deletion: " << minNode.key << endl;
}

int main() {

    FH_Use();

    cin.ignore();
    return 0;
}
