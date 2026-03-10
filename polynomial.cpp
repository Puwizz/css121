#include <iostream>
using namespace std;

class Node {
public:
    int coeff;
    int pow;
    Node* next;
    Node(int coeff, int pow) : coeff(coeff), pow(pow), next(nullptr) {}
};

class Polynomial {
private:
    Node* head;
    Node* tail; 

public:
    Polynomial() : head(nullptr), tail(nullptr) {}

    ~Polynomial() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

   
    void appendTerm(int c, int p) {
        if (c == 0) return;
        Node* newNode = new Node(c, p);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

   
    

    static Polynomial* add(const Polynomial& poly1, const Polynomial& poly2) {
        Polynomial* result = new Polynomial();
        Node* p1 = poly1.head;
        Node* p2 = poly2.head;

        while (p1 != nullptr || p2 != nullptr) {
            int c, p;
            if (p1 == nullptr) {
                c = p2->coeff; p = p2->pow; p2 = p2->next;
            } else if (p2 == nullptr) {
                c = p1->coeff; p = p1->pow; p1 = p1->next;
            } else if (p1->pow > p2->pow) {
                c = p1->coeff; p = p1->pow; p1 = p1->next;
            } else if (p2->pow > p1->pow) {
                c = p2->coeff; p = p2->pow; p2 = p2->next;
            } else {
                c = p1->coeff + p2->coeff;
                p = p1->pow;
                p1 = p1->next;
                p2 = p2->next;
            }

            if (c != 0) result->appendTerm(c, p); 
        }
        return result;
    }

    static Polynomial* multiply(const Polynomial& poly1, const Polynomial& poly2) {
        Polynomial* finalResult = new Polynomial();
        if (!poly1.head || !poly2.head) return finalResult;

        Node* p1 = poly1.head;
        while (p1 != nullptr) {
            Node* p2 = poly2.head;

            Node* cur = finalResult->head;
            Node* prev = nullptr;

            while (p2 != nullptr) {
                int p = p1->pow + p2->pow;
                int c = p1->coeff * p2->coeff;

                while (cur != nullptr && cur->pow > p) {
                    prev = cur;
                    cur = cur->next;
                }

                if (cur != nullptr && cur->pow == p) {
                    cur->coeff += c;
                    if (cur->coeff == 0) {
                        Node* temp = cur;
                        cur = cur->next;
                        if (prev == nullptr) finalResult->head = cur;
                        else prev->next = cur;
                        if (temp == finalResult->tail) finalResult->tail = prev;
                        delete temp;
                    } else {
                        prev = cur;
                        cur = cur->next;
                    }
                } else {
                    Node* newNode = new Node(c, p);
                    newNode->next = cur;
                    if (prev == nullptr) finalResult->head = newNode;
                    else prev->next = newNode;
                    if (cur == nullptr) finalResult->tail = newNode;
                    prev = newNode;
                }

                p2 = p2->next;
            }
            p1 = p1->next;
        }
        return finalResult;
    }

    void print() const {
        if (head == nullptr) {
            cout << "0" << endl;
            return;
        }

        Node* temp = head;
        bool first = true;

        while (temp != nullptr) {
            if (!first && temp->coeff > 0) cout << " + ";
            else if (temp->coeff < 0) cout << " - ";

            int absCoeff = (temp->coeff < 0) ? -temp->coeff : temp->coeff;
            if (absCoeff == 1) {
                if (temp->pow == 1) cout << "x";
                else if (temp->pow != 0) cout << "x^" << temp->pow;
                else cout << absCoeff;
            } else {
                cout << absCoeff;
                if (temp->pow == 1) cout << "x";
                else if (temp->pow != 0) cout << "x^" << temp->pow;
            }
            first = false;
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    Polynomial p1;
    int n;
    cout << "Enter number of terms in P1: ";
    cin >> n;
    cout << "Enter terms (coeff pow) in DESCENDING power order:\n";
    for (int i = 0; i < n; i++) {
        int c, p;
        cin >> c >> p;
        p1.appendTerm(c, p); 
    }
    cout << "Polynomial 1: ";
    p1.print();

    Polynomial p2;
    cout << "Enter number of terms in P2: ";
    cin >> n;
    cout << "Enter terms (coeff pow) in DESCENDING power order:\n";
    for (int i = 0; i < n; i++) {
        int c, p;
        cin >> c >> p;
        p2.appendTerm(c, p); 
    }
    cout << "Polynomial 2: ";
    p2.print();

    Polynomial* sum = Polynomial::add(p1, p2);
    cout << "Sum: ";
    sum->print();
    delete sum;

    Polynomial* product = Polynomial::multiply(p1, p2);
    cout << "Product: ";
    product->print();
    delete product;

    return 0;
}