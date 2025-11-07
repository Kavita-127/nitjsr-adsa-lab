#include <stdio.h>
#include <stdlib.h>
#include<limits.h>

int main() {
    FILE *fp;
    char filename[100];
    long long *arr = NULL;
    int capacity = 10, n = 0;

    arr = (long long*) malloc(capacity*sizeof(long long));
    if(!arr){ 
        printf("Memory allocation failed!\n"); 
        return 0;
    }

    printf("Enter input filename: ");
    scanf("%s", filename);

    fp = fopen(filename,"r");
    if(!fp){ 
        printf("File not found!\n"); 
        free(arr); 
        return 0;
    }

    //LLONG_MAX ensures any number in the array is ≤ min initially.
    //LLONG_MIN ensures any number in the array is ≥ max initially.
    long long num;
    long long min = LLONG_MAX, max = LLONG_MIN;
    while(1){
        if(n == capacity){ 
            capacity *= 2; 
            arr = (long long*)realloc(arr,capacity*sizeof(long long));
            if(!arr){ 
                printf("Memory reallocation failed!\n"); 
                fclose(fp); 
                return 0;
            }
        }
        if(fscanf(fp,"%lld",&num) != 1) 
        break;
        arr[n++] = num;
        if(num < min) min = num;
        if(num > max) max = num;
    }
    fclose(fp);

    int range = (int)(max - min + 1);
    long long *count = (long long*) calloc(range, sizeof(long long));
    long long *output = (long long*) malloc(n*sizeof(long long));

    for(int i = 0; i < n; i++) 
        count[arr[i]-min]++;
    for(int i = 1; i < range; i++) 
        count[i] += count[i-1];
    for(int i = n-1; i >= 0; i--){
        output[count[arr[i]-min]-1] = arr[i];
        count[arr[i]-min]--;
    }

    printf("Sorted: ");
    for(int i = 0; i < n; i++) printf("%lld ", output[i]);
    printf("\n");

    free(arr); 
    free(count); 
    free(output);
    return 0;
}
