#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Player
{
    char name[50];
    int score;
    struct Player* prev;
    struct Player* next;
};

struct ScoreBoard
{
    struct Player* head;
    struct Player* tail;
    int curSize;
    int maxSize;

};

struct Player* createPlayer(char* name, int score)
{
    struct Player* newPlayer = (struct Player*)malloc(sizeof(struct Player));
    strcpy(newPlayer->name, name);
    newPlayer->score = score;
    newPlayer->prev = NULL;
    newPlayer->next = NULL;
    return newPlayer;
}

void initScoreBoard(struct ScoreBoard* sb, int size)
{
    sb->head = createPlayer("HEAD",9999999);
    sb->tail = createPlayer("TAIL",-9999999);
    sb->head->next = sb->tail;
    sb->tail->prev = sb->head;
    sb->maxSize = size;
    sb->curSize = 0;
};

void removeTail(struct ScoreBoard* sb)
{
    if(sb->head->next == sb->tail) return;
    struct Player *temp = sb->tail->prev;
    printf("%s was removed from the score board.\n",temp->name);
    temp->prev->next = sb->tail;
    sb->tail->prev = temp->prev;
    free(temp);
    sb->curSize--;
};

void addScore(struct ScoreBoard* sb, char* name, int score)
{
    if (sb->curSize == sb->maxSize && sb->head->next != sb->tail && score <= sb->tail->prev->score) return;
    struct Player *newPlayer = createPlayer(name, score);
    struct Player *cur = sb->head->next;
    while(cur != sb->tail && cur->score >= score)
    {
        cur = cur->next;
    }
    newPlayer->next = cur;
    newPlayer->prev = cur->prev;
    cur->prev->next = newPlayer;
    cur->prev = newPlayer;
    sb->curSize++;

    if(sb->curSize > sb->maxSize)
    {
        removeTail(sb);
    }
}
void printBoard(struct ScoreBoard* sb)
{
    struct Player *cur = sb->head->next;
    int rank = 1;
    printf("---- Score Board----\n");
    while (cur != sb->tail)
    {
        printf("%d. %s : %d\n",rank, cur->name, cur->score);
        cur = cur->next;
        rank++;
    }
    
};


int main() {
    struct ScoreBoard sb;
    initScoreBoard(&sb,4);
    addScore(&sb, "A", 100);
    addScore(&sb,"B",98);
    addScore(&sb,"C",95);
    addScore(&sb,"D",94);
    addScore(&sb,"C",94);
    printBoard(&sb);
    addScore(&sb, "E", 97);
    addScore(&sb, "F",101);
    printBoard(&sb);
    return 0;
}