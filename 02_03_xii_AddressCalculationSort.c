//SET-2
//Q3 Implement the (xii) Address Calculation Sort.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> //For LLONG_MAX and LLONG_MIN

int main(){
    FILE *fp; 
    char filename[100];
    long long *arr = NULL; //Array to store input numbers
    int capacity = 10, n = 0;
    
    //Allocate initial dynamic array 
    arr = (long long*) malloc(capacity*sizeof(long long));
    if(!arr){ 
        printf("Memory allocation failed\n"); 
        return 0;
    }
    
    //input filename
    printf("Enter input filename: "); 
    scanf("%s",filename);

    //open the file
    fp = fopen(filename,"r");
    if(!fp){ 
        printf("File not found\n"); 
        free(arr); 
        return 0;
    }

    long long num, min = LLONG_MAX, max = LLONG_MIN;

    //read numbers from file and find minimum and maximum
    while(1){
        if(n == capacity){ //if array is full, double its capacity
            capacity *= 2; 
            arr = (long long*) realloc(arr,capacity*sizeof(long long));
            if(!arr){ 
                printf("Memory reallocation failed\n"); 
                fclose(fp); 
                return 0;
            } 
        }

        //read number from file, break if no more numbers
        if(fscanf(fp,"%lld",&num) != 1) break;

        arr[n++] = num;

        //update min and max values
        if(num<min) min = num;
        if(num>max) max = num;
    }
    fclose(fp);
    
    //calculate the range of values for address calculation
    int range = (int)(max-min+1);
    //create table (address array) to map values to their positions
    long long *table = (long long*) calloc(range,sizeof(long long));

    //Place elements into the table based on their value
    for(int i = 0; i < n; i++)
        table[arr[i]-min] = arr[i];

    printf("Sorted: ");
    for(int i = 0; i < range; i++){
        if(table[i] != 0) //skip empty slots
            printf("%lld ", table[i]);
    }
    printf("\n");

    //Free dynamically allocated memory
    free(arr); 
    free(table);
    return 0;
}

