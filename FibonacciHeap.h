//
// Created by Lewy on 30.01.2024.
//

#ifndef FIBONACCIHEAP_FIBONACCIHEAP_H
#define FIBONACCIHEAP_FIBONACCIHEAP_H

#include <climits>

using namespace std;

struct FH_Node {
    int key;
    FH_Node *p;
    FH_Node *child;
    FH_Node *left;
    FH_Node *right;
    int degree;
    bool mark;

    explicit FH_Node(int k) {
        key = k;
        p = nullptr;
        child = nullptr;
        left = nullptr;
        right = nullptr;
        degree = 0;
        mark = false;
    }
};

struct FH {
    FH_Node *min;
    int n;

    FH() {
        min = nullptr;
        n = 0;
    }
};

FH_Node FH_Minimum(FH *H) {
    return *(H->min);
}

FH FH_Insert(FH *H, FH_Node *x) {
    x->degree = 0;
    x->p = nullptr;
    x->child = nullptr;
    x->left = x;
    x->right = x;
    x->mark = false;
    if (H->min == nullptr) {
        H->min = x;
    } else {
        x->left = H->min->left;
        x->right = H->min;
        H->min->left->right = x;
        H->min->left = x;
        if (x->key < H->min->key) {
            H->min = x;
        }
    }
    H->n++;
    return *H;
}

FH FH_Union(FH *H1, FH *H2) {
    FH *H = new FH();
    H->min = H1->min;
    if (H->min == nullptr || (H2->min != nullptr && H2->min->key < H1->min->key)) {
        H->min = H2->min;
    }
    H->n = H1->n + H2->n;
    return *H;
}

void Fib_Heap_Link(FH *H, FH_Node *y, FH_Node *x) {
    y->left->right = y->right;
    y->right->left = y->left;
    if (x->child == nullptr) {
        x->child = y;
        y->left = y;
        y->right = y;
    } else {
        y->left = x->child->left;
        y->right = x->child;
        x->child->left->right = y;
        x->child->left = y;
    }
    y->p = x;
    x->degree++;
    y->mark = false;
}

void FH_Consolidate(FH *H) {
    int D = H->n;
    FH_Node *A[D];
    for (int i = 0; i < D; i++) {
        A[i] = nullptr;
    }
    FH_Node *w = H->min;
    FH_Node *x = w;
    FH_Node *y;
    FH_Node *temp;
    int d;
    do {
        x = x->right;
        d = x->degree;
        while (A[d] != nullptr) {
            y = A[d];
            if (x->key > y->key) {
                temp = x;
                x = y;
                y = temp;
            }
            Fib_Heap_Link(H, y, x);
            A[d] = nullptr;
            d++;
        }
        A[d] = x;
    } while (x != w);
    H->min = nullptr;
    for (int i = 0; i < D; i++) {
        if (A[i] != nullptr) {
            if (H->min == nullptr) {
                H->min = A[i];
            } else {
                A[i]->left = H->min->left;
                A[i]->right = H->min;
                H->min->left->right = A[i];
                H->min->left = A[i];
                if (A[i]->key < H->min->key) {
                    H->min = A[i];
                }
            }
        }
    }
}

FH_Node FH_Extract_Min(FH *H) {
    FH_Node *z = H->min;
    if (z != nullptr) {
        FH_Node *x = z->child;
        FH_Node *temp;
        if (x != nullptr) {
            do {
                temp = x->right;
                x->left->right = x->right;
                x->right->left = x->left;
                x->left = H->min->left;
                x->right = H->min;
                H->min->left->right = x;
                H->min->left = x;
                x->p = nullptr;
                x = temp;
            } while (x != z->child);
        }
        z->left->right = z->right;
        z->right->left = z->left;
        if (z == z->right) {
            H->min = nullptr;
        } else {
            H->min = z->right;
            FH_Consolidate(H);
        }
        H->n--;
    } else {
        // Handle the case where z is nullptr (empty heap)
        cout << "Fibonacci Heap is empty. Cannot extract FH_Minimum." << endl;
    }
    return (z != nullptr) ? *z : FH_Node(0); // Return a default-constructed FH_Node if z is nullptr
}


void FH_Cut(FH *H, FH_Node *x, FH_Node *y) {
    if (x == x->right) {
        y->child = nullptr;
    } else {
        x->left->right = x->right;
        x->right->left = x->left;
        if (x == y->child) {
            y->child = x->right;
        }
    }
    y->degree--;
    x->left = H->min->left;
    x->right = H->min;
    H->min->left->right = x;
    H->min->left = x;
    x->p = nullptr;
    x->mark = false;
}

void FH_Cascading_Cut(FH *H, FH_Node *y) {
    FH_Node *z = y->p;
    if (z != nullptr) {
        if (y->mark == false) {
            y->mark = true;
        } else {
            FH_Cut(H, y, z);
            FH_Cascading_Cut(H, z);
        }
    }
}

void FH_Decrease_Key(FH *H, FH_Node *x, int k) {
    if (k > x->key) {
        cout << "new key is greater than current key" << endl;
        return;
    }
    x->key = k;
    FH_Node *y = x->p;
    if (y != nullptr && x->key < y->key) {
        FH_Cut(H, x, y);
        FH_Cascading_Cut(H, y);
    }
    if (x->key < H->min->key) {
        H->min = x;
    }
}

void FH_Delete(FH *H, FH_Node *x) {
    FH_Decrease_Key(H, x, INT_MIN);
    FH_Extract_Min(H);
}

void FH_Print_Node(FH_Node* node) {
    if (node != nullptr) {
        std::cout << node->key << " ";
        FH_Node* child = node->child;
        if (child != nullptr) {
            FH_Node* start = child;
            do {
                FH_Print_Node(child);
                child = child->right;
            } while (child != start);
        }
    }
}

void FH_Print(FH* H) {
    if (H->min != nullptr) {
        FH_Node* start = H->min;
        FH_Node* current = H->min;
        do {
            FH_Print_Node(current);
            current = current->right;
        } while (current != start);
        std::cout << std::endl;
    } else {
        std::cout << "Fibonacci Heap is empty." << std::endl;
    }
}



#endif //FIBONACCIHEAP_FIBONACCIHEAP_H
