#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <float.h>

#define MAX_PERSONS 100
#define MAX_LINE_LENGTH 1024
#define K 5

typedef struct {
    char name[50];
    double cognitive_fn[8];
    char type[5];
    
} Person;

typedef struct 
{
    int index;
    double dist;
} Neighbor;


double calculate_distance(double a[], double b[]){
    double sum_of_diff_sqr;
    for(int i=0;i<8;i++){
        sum_of_diff_sqr += pow(a[i]-b[i],2);
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
    double query[8] = {32,32,27,36,29,31,28,23};
    char predicted_mbti[5];
    
    Neighbor neighbors[K];
    for(int i=0;i<K ; i++) { 
        neighbors[i].dist = DBL_MAX;
        neighbors[i].index = -1; 
    }
    
    for(int i=0; i<cnt;i++){
        double d = calculate_distance(query, dataset[i].cognitive_fn);
        if(d < neighbors[K-1].dist){
            int pos = K-1;
            while(pos > 0 && d < neighbors[pos-1].dist){
                neighbors[pos].dist = neighbors[pos-1].dist;
                pos--;
            }
            neighbors[pos].dist = d;
            neighbors[pos].index = i;
        }
    }
    for(int p=0;p<4;p++){
        int cnt_a = 0, cnt_b = 0;
        char ch_a,ch_b;
        if(p==0) {ch_a = 'I'; ch_b = 'E';}
        else if(p==1) {ch_a = 'N'; ch_b = 'S';}
        else if(p==2) {ch_a = 'T'; ch_b = 'F';}
        else {ch_a = 'J'; ch_b = 'P';}
        for(int i=0;i<K;i++){
            int id = neighbors[i].index;
            if(dataset[id].type[p] == ch_a) cnt_a++;
            else if(dataset[id].type[p] == ch_b) cnt_b++;
        }
        if(cnt_a >= cnt_b){
            predicted_mbti[p] = ch_a;
        }else{
            predicted_mbti[p] = ch_b;
        }
    }
    printf("Predicted MBTI: %s\n",predicted_mbti);

    return 0;
}