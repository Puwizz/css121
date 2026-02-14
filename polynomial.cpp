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

public:
    Polynomial() : head(nullptr) {}

    ~Polynomial() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertTerm(int c, int p) {
        if (c == 0) return;

        if (head == nullptr || head->pow < p) {
            Node* newNode = new Node(c, p);
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* cur = head;
        Node* prev = nullptr;

        while (cur != nullptr && cur->pow > p) {
            prev = cur;
            cur = cur->next;
        }

        if (cur != nullptr && cur->pow == p) {
            cur->coeff += c;
            if (cur->coeff == 0) {
                if (prev == nullptr) head = cur->next;
                else prev->next = cur->next;
                delete cur;
            }
        } else {
            Node* newNode = new Node(c, p);
            newNode->next = cur;
            if (prev != nullptr) prev->next = newNode;
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
            result->insertTerm(c, p);
        }
        return result;
    }
    static Polynomial* multipy(const Polynomial& poly1, const Polynomial& poly2){
        Polynomial* finalResult = new Polynomial();
        Node* p1 = poly1.head;
        while(p1 != nullptr){
            Polynomial tempPoly;
            Node* p2 = poly2.head;
            while(p2 != nullptr)
            {
                int c = p1->coeff * p2->coeff;
                int p = p1->pow + p2->pow;
                tempPoly.insertTerm(c,p);
                p2 = p2->next;
            }
            Polynomial* oldResult = finalResult;
            finalResult = Polynomial::add(*oldResult, tempPoly);
            delete oldResult;
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
            if(absCoeff == 1){
                if(temp->pow == 1) cout << "x";
                else if(temp->pow != 0) cout << "x^" << temp->pow;
            }else{
                cout << absCoeff;
                if(temp->pow == 1) cout << "x";
                else if(temp->pow != 0) cout << "x^" << temp->pow;
            }
            first = false;
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    Polynomial p1;
    p1.insertTerm(2, 0);
    p1.insertTerm(4, 3);
    p1.insertTerm(3, 2);
    p1.insertTerm(5, 0);
    
    cout << "Polynomial 1: ";
    p1.print();

    Polynomial p2;
    p2.insertTerm(1, 3);
    p2.insertTerm(-3, 2);
    p2.insertTerm(4, 1);
    
    cout << "Polynomial 2: ";
    p2.print();

    Polynomial* sum = Polynomial::add(p1, p2);
    cout << "Sum: ";
    sum->print();

    delete sum;
    Polynomial* Product = Polynomial::multipy(p1, p2);
    cout << "Product: ";
    Product->print();
    return 0;
}