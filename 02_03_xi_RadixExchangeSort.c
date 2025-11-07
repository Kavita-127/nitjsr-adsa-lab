#include <stdio.h>
#include <stdlib.h>

// Radix Exchange sort for long long numbers using bits
void radixExchange(long long arr[], int left, int right, int bit){
    //Base case: if subarray has 1 or 0 elements or no more bits to check
    if(left >= right || bit < 0) return;

    int i = left, j = right;
    long long temp;

    //Partition array based on the current bit
    while(i <= j){
        // Find left element with bit 1
        while(i <= j && !(arr[i] & (1LL<<bit))) i++;
        // Find right element with bit 0
        while(i <= j && (arr[j] & (1LL<<bit))) j--;

        // Swap elements if necessary
        if(i<j){
            temp = arr[i]; 
            arr[i] = arr[j]; 
            arr[j] = temp;
            i++; j--;
        }
    }

    // Recursively sort subarrays for next lower bit
    radixExchange(arr,left,j,bit-1); // Left partition (bit 0)
    radixExchange(arr,i,right,bit-1); // Right partition (bit 1)
}

int main(){
    FILE *fp; 
    char filename[100];
    long long *arr = NULL; 
    int capacity = 10,n = 0;
    
    //Allocate initial dynamic array
    arr = (long long*) malloc(capacity*sizeof(long long));
    if(!arr){
        printf("Memory allocation failed\n"); 
        return 0;
    }
    
    //Input filename
    printf("Enter input filename: "); 
    scanf("%s",filename);

    //open file for reading
    fp = fopen(filename,"r");
    if(!fp){ printf("File not found\n"); 
        free(arr); 
        return 0;
    }

    long long num, max = 0;

    // Read numbers dynamically from file
    while(1){
        if(n == capacity){ // Expand array if needed
            capacity *= 2; 
            arr = (long long*) realloc(arr,capacity*sizeof(long long));
            if(!arr){
                printf("Memory reallocation failed\n"); 
                fclose(fp); 
                return 0;
            } 
        }
        if(fscanf(fp,"%lld",&num) != 1) break;
        arr[n++] = num;
        if(num > max) max = num; // Find maximum value to determine number of bits
    }
    fclose(fp);

    // Find number of bits needed for maximum number
    int bits = 0; 
    long long tmp = max;
    while(tmp){ tmp >>= 1; // Shift right by 1
        bits++; 
    }
    
    // Perform radix exchange sort if array is not empty
    if(n>0) radixExchange(arr, 0, n-1, bits-1);

    printf("Sorted: ");
    for(int i = 0; i < n; i++) 
        printf("%lld ",arr[i]);
    printf("\n");

    free(arr); 
    return 0;
}
