#include <iostream>
#include "FibonacciHeap.h"
#include "BinomialHeap.h"


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

void BH_Use() {
    BH binomialHeap1 = BH();
    BH binomialHeap2 = BH();

    for (int i=1; i<10; i++) {
        auto newNode = (BH_Node*)malloc(sizeof(BH_Node));
        newNode->key = i;
        binomialHeap1 = BH_Insert(binomialHeap1, newNode);
    }

    // BH_Insert some nodes into binomialHeap1
    auto node1 = BH_Node(5);
    binomialHeap1 = BH_Insert(binomialHeap1, &node1);

    auto node2 = BH_Node(8);
    binomialHeap1 = BH_Insert(binomialHeap1, &node2);

    auto node3 = BH_Node(3);
    binomialHeap1 = BH_Insert(binomialHeap1, &node3);

    // BH_Insert some nodes into binomialHeap2
    auto node4 = BH_Node(12);
    binomialHeap1 = BH_Insert(binomialHeap1, &node4);

    auto node5 = BH_Node(7);
    binomialHeap2 = BH_Insert(binomialHeap2, &node5);

    cout << "Heap print: " << endl;
    BH_Print(binomialHeap1.head);
//    BH_Print(binomialHeap2.head);
    cout << "printed" << endl;


    // BH_Merge binomialHeap1 and binomialHeap2
    BH mergedHeap = BH_Union(binomialHeap1, binomialHeap2);

//    cout << "Heap print merged: " << endl;
//    BH_Print(mergedHeap.head);
//    cout << "printed" << endl;

    // Extract the BH_Minimum BH_Node from the merged heap
    mergedHeap = BH_ExtractMin(mergedHeap);

    // Decrease the key of a BH_Node in the merged heap
    BH_DecreaseKey(&node2, 4);

    // BH_Delete a BH_Node from the merged heap
    mergedHeap = BH_Delete(mergedHeap, &node3);
    cout << "After BH_Delete" << endl;

    BH_Print(mergedHeap.head);
}


int main() {
    BH_Use();
    FH_Use();
    cin.ignore();
    return 0;
}
