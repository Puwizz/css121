#include <iostream>
#include <string>

using namespace std;


class Player {
public:
    string name;
    int score;
    Player* prev;
    Player* next;

     
    Player(string n, int s) : name(n), score(s), prev(nullptr), next(nullptr) {}
};

class ScoreBoard {
private:
    Player* head;
    Player* tail;
    int curSize;
    int maxSize;

    
    void removeTail() {
        if (head->next == tail) return;

        Player* temp = tail->prev;
        cout << temp->name << " was removed from the score board." << endl;

        temp->prev->next = tail;
        tail->prev = temp->prev;
        
        delete temp;
        curSize--;
    }

public:
    
    ScoreBoard(int size) : maxSize(size), curSize(0) {
        head = new Player("HEAD", 9999999);
        tail = new Player("TAIL", -9999999);
        head->next = tail;
        tail->prev = head;
    }

    
    ~ScoreBoard() {
        Player* cur = head;
        while (cur != nullptr) {
            Player* nextNode = cur->next;
            delete cur;
            cur = nextNode;
        }
    }

    void addScore(string name, int score) {
        
        if (curSize == maxSize && head->next != tail && score <= tail->prev->score) {
            return;
        }

        Player* newPlayer = new Player(name, score);
        Player* cur = head->next;

        
        while (cur != tail && cur->score >= score) {
            cur = cur->next;
        }

        newPlayer->next = cur;
        newPlayer->prev = cur->prev;
        cur->prev->next = newPlayer;
        cur->prev = newPlayer;
        curSize++;

        if (curSize > maxSize) {
            removeTail();
        }
    }

    void printBoard() {
        Player* cur = head->next;
        int rank = 1;
        cout << "\n---- Score Board ----" << endl;
        while (cur != tail) {
            cout << rank << ". " << cur->name << " : " << cur->score << endl;
            cur = cur->next;
            rank++;
        }
    }
};

int main() {
    
    ScoreBoard sb(4);

    sb.addScore("A", 100);
    sb.addScore("B", 98);
    sb.addScore("C", 95);
    sb.addScore("D", 94);
    sb.addScore("C", 94); 
    
    sb.printBoard();

    sb.addScore("E", 97);
    sb.addScore("F", 101);
    
    sb.printBoard();

    return 0;
}