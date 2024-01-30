//
// Created by Lewy on 30.01.2024.
//

#ifndef BINOMIALHEAP_BINOMIALHEAP_H
#define BINOMIALHEAP_BINOMIALHEAP_H

#include <climits>

using namespace std;

struct BH_Node {
    int key;
    BH_Node *parent;
    BH_Node *child;
    BH_Node *sibling;
    int degree;

    explicit BH_Node(int k) {
        key = k;
        parent = nullptr;
        child = nullptr;
        sibling = nullptr;
        degree = 0;
    }
};

struct BH {
    BH_Node *head;

    BH() {
        head = nullptr;
    }
};

BH_Node BH_Minimum(BH H) {
    BH_Node *y = nullptr;
    BH_Node *x = H.head;
    int min = INT_MAX;

    while (x != nullptr) {
        if (x->key < min) {
            min = x->key;
            y = x;
        }
        x = x->sibling;
    }
    return *y;
}

BH_Node BH_Link(BH_Node *y, BH_Node *z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
    return *z;
}

BH_Node * BH_Merge(BH H1, BH H2) {
    if (H1.head == nullptr) { return H2.head; }
    else if (H2.head == nullptr) { return H1.head; }
    else {
        BH_Node *x = H1.head;
        BH_Node *y = H2.head;
        BH_Node *head;
        BH_Node *tail;

        if (x->degree < y->degree) {
            head = x;
            x = x->sibling;
        } else {
            head = y;
            y = y->sibling;
        }
        tail = head;

        while (x != nullptr && y != nullptr) {
            if (x->degree < y->degree) {
                tail->sibling = x;
                x = x->sibling;
            } else {
                tail->sibling = y;
                y = y->sibling;
            }
            tail = tail->sibling;
        }

        if (x != nullptr) { tail->sibling = x; }
        else { tail->sibling = y; }

        return head;
    }
}

BH BH_Union(BH H1, BH H2) {
    BH H = BH();
    H.head = BH_Merge(H1, H2);
    if (H.head == nullptr) { return H; }

    BH_Node *px = nullptr;
    BH_Node *x = H.head;
    BH_Node *nx = x->sibling;

    while (nx != nullptr) {
        if ((x->degree != nx->degree) || ((nx->sibling != nullptr) && (nx->sibling)->degree == x->degree)) {
            px = x;
            x = nx;
        } else if (x->key <= nx->key) {
            x->sibling = nx->sibling;
            BH_Link(nx, x);
        } else {
            if (px == nullptr) { H.head = nx; }
            else { px->sibling = nx; }
            BH_Link(x, nx);
            x = nx;
        }
        nx = x->sibling;
    }

    return H;
}

// Przed insertem trzeba zrobić nowy węzeł i nadać wartość klucza
BH BH_Insert(BH H, BH_Node *x) {
    BH Hx = BH();

    x->parent = nullptr;
    x->child = nullptr;
    x->sibling = nullptr;
    x->degree = 0;
    Hx.head = x;
    return BH_Union(H, Hx);
}

BH BH_ExtractMin(BH H) {
    BH_Node x = BH_Minimum(H);
    cout << "BH_Minimum: " << x.key << endl;
//    usuń x z listy korzeni H
    BH_Node *z = H.head;

    if (z->key == x.key) {
        H.head = z->sibling;
    } else {
        while (z->sibling->key != x.key) {
            z = z->sibling;
        }
        z->sibling = z->sibling->sibling;
    }

//    dla każdego dziecka y x
    BH_Node *y = nullptr;
    if(x.child != nullptr) {
        y = x.child;
    }
    while (y != nullptr) {
        y-> parent = nullptr;
        y = y->sibling;
    }

//        H' = MakeHeap()
    BH Hx = BH();
// Odwróć kolejność elementów na liście synów węzła x (prev, current, next)
    BH_Node *p = nullptr;
    BH_Node *c = x.child;
    BH_Node *n = nullptr;
    if (c != nullptr) { n = c->sibling; }

    while (c != nullptr) {
        c->sibling = p;  // Odwrócenie kierunku currenta z nexta na preva
        p = c; // Nowym prevem jest current
        c = n; // Nowym currentem jest next
        if (n != nullptr) { n = n->sibling; }
    }
    Hx.head = p;

    H = BH_Union(H, Hx);
    return H;
}

void BH_DecreaseKey(BH_Node *x, int k) {
    if (k > x->key) {
        cout << "Nowy klucz jest większy od obecnego" << endl;
    } else {
        x->key = k;  // Update the key of the BH_Node
        BH_Node *y = x->parent;
        while (y != nullptr && x->key < y->key) {
            int temp = x->key;
            x->key = y->key;
            y->key = temp;
            x = y;
            y = y->parent;
        }
    }
}


BH BH_Delete(BH H, BH_Node *x) {
    BH_DecreaseKey(x, INT_MIN);
    BH H1 = BH_ExtractMin(H);

    return H1;
}

void BH_Print(BH_Node *h) {
    while (h) {
        cout << h->key << " ";
        if (h->child) {
            BH_Print(h->child);
        }
        cout << endl;

        h = h->sibling;
    }
}

#endif //BINOMIALHEAP_BINOMIALHEAP_H
