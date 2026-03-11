#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define MAX_PERSONS 100
#define MAX_LINE_LENGTH 1024
// #define K 5

typedef struct {
    char id[12];
    char name[40];
    char sex[7];
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
    srand(time(NULL));
    Person dataset[MAX_PERSONS];
    int cnt = 0;
    int k = 0;
    FILE *file = fopen("CSS121_MBTI_2026_68.txt", "r");
    if (!file) { printf("Error opening file.\n"); return 1; }

    char line[MAX_LINE_LENGTH];
    double query[8];
    char target_id[] = "68090500420";
    int found_query = 0;
    char predicted_mbti[5];
    fgets(line, MAX_LINE_LENGTH, file);
    while (cnt < MAX_PERSONS && fgets(line, MAX_LINE_LENGTH, file)) {
        Person temp;
        int items = sscanf(line, "%s\t%[^\t]\t%s\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%s",
                   temp.id, temp.name, temp.sex,
                   &temp.cognitive_fn[0], &temp.cognitive_fn[1], &temp.cognitive_fn[2], &temp.cognitive_fn[3],
                   &temp.cognitive_fn[4], &temp.cognitive_fn[5], &temp.cognitive_fn[6], &temp.cognitive_fn[7],
                   temp.type);
        if (items < 12 ) {
            continue;
        }
        if(strcmp(temp.id, target_id) == 0){
            for(int i=0; i<8; i++) query[i] = temp.cognitive_fn[i];
            found_query = 1;
            continue;
        }
        dataset[cnt] = temp;
        cnt++;
    }
    fclose(file);
    if (!found_query) {
        printf("Target ID not found in file!\n");
    return 1;
    }
    for(int i=0; i<cnt; i++) {
        dataset[i].dist = calculate_distance(query, dataset[i].cognitive_fn);
    }
    for(int i=0;i<cnt;i++){
        printf("%s\n",dataset[i].name);
    }
    printf("Enter k : ");
    scanf("%d",&k);
    quick_select(dataset, 0, cnt - 1, k - 1);


    for(int p=0;p<4;p++){
        double cnt_a = 0.0, cnt_b = 0.0;
        char ch_a,ch_b;
        if(p==0) {ch_a = 'I'; ch_b = 'E';}
        else if(p==1) {ch_a = 'N'; ch_b = 'S';}
        else if(p==2) {ch_a = 'T'; ch_b = 'F';}
        else {ch_a = 'J'; ch_b = 'P';}
        for(int i=0;i<k;i++){
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
    printf("\n=== %d Nearest Neighbors Found ===\n", k);
    printf("%-15s | %-25s | %-10s | %-10s\n", "Student ID", "Name", "Distance", "MBTI");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < k; i++) {
        printf("%-15s | %-25s | %-10.4f | %-10s\n", 
               dataset[i].id, dataset[i].name, dataset[i].dist, dataset[i].type);
    }
    printf("--------------------------------------------------------------------------\n");

    printf("Predicted MBTI: %s\n",predicted_mbti);


    return 0;
}
