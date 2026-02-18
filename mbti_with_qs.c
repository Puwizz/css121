#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define MAX_PERSONS 100
#define MAX_LINE_LENGTH 1024
#define K 5

typedef struct {
    char name[50];
    double cognitive_fn[8];
    char type[5];
    double dist;
} Person;

double calculate_distance(double a[], double b[]){
    double sum_of_diff_sqr = 0.0;
    for(int i=0;i<8;i++){
        sum_of_diff_sqr += pow(a[i]-b[i],2);
    }
    return sqrt(sum_of_diff_sqr);
}

void swap(Person *a, Person *b) {
    Person temp = *a;
    *a = *b;
    *b = temp;
}
int partition(Person arr[], int left, int right){
    int pivot_index = left + rand() % (right - left +1);
    swap(&arr[pivot_index], &arr[right]);
    int i = left;
    double pivot_val = arr[right].dist;
    for(int j = left; j<right;j++){
        if(arr[j].dist < pivot_val){
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[right]);
    return i;
}

void quick_select(Person *arr, int left, int right, int k){

    int pivot_index = partition(arr, left, right);
    if(k == pivot_index){
        return;
    }else if(k < pivot_index){
        return quick_select(arr, left, pivot_index-1, k);
    }else{
        return quick_select(arr, pivot_index+1, right, k);
    }
}
int main() {
    Person dataset[MAX_PERSONS];
    int cnt = 0;

    FILE *file = fopen("Mbti.txt", "r");
    if (!file) { printf("Error opening file.\n"); return 1; }

    char line[MAX_LINE_LENGTH];
    double query[8] = {32,32,27,36,29,31,28,23};
    char predicted_mbti[5];
    
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        int items = sscanf(line, "%50[^,],%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%[^,]",
               dataset[cnt].name,
               &dataset[cnt].cognitive_fn[0], &dataset[cnt].cognitive_fn[1], &dataset[cnt].cognitive_fn[2], &dataset[cnt].cognitive_fn[3],
               &dataset[cnt].cognitive_fn[4], &dataset[cnt].cognitive_fn[5], &dataset[cnt].cognitive_fn[6], &dataset[cnt].cognitive_fn[7],
               dataset[cnt].type);
        double d = calculate_distance(query, dataset[cnt].cognitive_fn);
        dataset[cnt].dist = d;
        
        cnt++;
    }
    fclose(file);
    
    quick_select(dataset, 0, cnt - 1, K - 1);
    
    
    for(int p=0;p<4;p++){
        double cnt_a = 0.0, cnt_b = 0.0;
        char ch_a,ch_b;
        if(p==0) {ch_a = 'I'; ch_b = 'E';}
        else if(p==1) {ch_a = 'N'; ch_b = 'S';}
        else if(p==2) {ch_a = 'T'; ch_b = 'F';}
        else {ch_a = 'J'; ch_b = 'P';}
        for(int i=0;i<K;i++){
            double w = 1.0 / (dataset[i].dist + 0.00001);
            if(dataset[i].type[p] == ch_a) cnt_a += w;
            else cnt_b += w;
        }
        if(cnt_a >= cnt_b){
            predicted_mbti[p] = ch_a;
        }else{
            predicted_mbti[p] = ch_b;
        }
    }
    predicted_mbti[4] = '\0';
    printf("Predicted MBTI: %s\n",predicted_mbti);
    printf("%d",cnt);

    return 0;
}
