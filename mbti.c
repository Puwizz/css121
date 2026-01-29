#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <float.h>

#define MAX_PERSONS 100
#define MAX_LINE_LENGTH 1024


typedef struct {
    char name[50];
    double cognitive_fn[8];
    char type[10];
    double distance;
} Person;

double calculate_distance(Person a, Person b){
    double sum_of_diff_sqr;
    for(int i=0;i<8;i++){
        sum_of_diff_sqr += pow(a.cognitive_fn[i]-b.cognitive_fn[i],2);
    }
    return sqrt(sum_of_diff_sqr);
}
int main() {
    Person dataset[MAX_PERSONS];
    int cnt = 0;

    FILE *file = fopen("Mbti.txt", "r");
    if (!file) { printf("Error opening file.\n"); return 1; }

    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, file) && cnt < MAX_PERSONS) {
        int items = sscanf(line, "%[^,],%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%[^,]",
               dataset[cnt].name,
               &dataset[cnt].cognitive_fn[0], &dataset[cnt].cognitive_fn[1], &dataset[cnt].cognitive_fn[2], &dataset[cnt].cognitive_fn[3],
               &dataset[cnt].cognitive_fn[4], &dataset[cnt].cognitive_fn[5], &dataset[cnt].cognitive_fn[6], &dataset[cnt].cognitive_fn[7],
               dataset[cnt].type);

        if (items >= 9) {
            cnt++;
        }
    }
    fclose(file);
    Person query;
    strcpy(query.name,"Query");
    for(int i=0;i<8;i++){
        scanf("%lf",&query.cognitive_fn[i]);
    }
    Person neighbors[3];
    for(int i=0;i<3 ; i++) { neighbors[i].distance = DBL_MAX; }
    for(int i=0;i<cnt;i++){
        dataset[i].distance = calculate_distance(dataset[i], query);
        double d = dataset[i].distance;
        if(d < neighbors[0].distance){
            neighbors[2] = neighbors[1];
            neighbors[1] = neighbors[0];
            neighbors[0] = dataset[i];
        }else if(d < neighbors[1].distance){
            neighbors[2] = neighbors[1];
            neighbors[1] = dataset[i];
        }else if(d < neighbors[2].distance){
            neighbors[3] = dataset[i];
        }
    }

    for(int p=0;p<4;p++){
        int cnt_a = 0, cnt_b = 0;
        char ch_a,ch_b;
        if(p==0) {ch_a = 'I'; ch_b = 'E';}
        else if(p==1) {ch_a = 'N'; ch_b = 'S';}
        else if(p==2) {ch_a = 'T'; ch_b = 'F';}
        else {ch_a = 'J'; ch_b = 'P';}
        for(int i=0;i<3;i++){
            if(neighbors[i].type[p] == ch_a) cnt_a++;
            else if(neighbors[i].type[p] == ch_b) cnt_b++;
        }
        if(cnt_a >= cnt_b){
            query.type[p] = ch_a;
        }else{
            query.type[p] = ch_b;
        }
    }
    printf("Predicted MBTI: %s\n",query.type);

    return 0;
}
