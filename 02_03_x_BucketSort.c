#include <stdio.h>
#include <stdlib.h>
#include<limits.h>

typedef struct Node {
    long long value;
    struct Node *next;
} Node;

void insert(Node **head, long long val){
    Node *newnode = (Node*) malloc(sizeof(Node));
    newnode->value = val;
    newnode->next = NULL;

    if(!*head || (*head)->value >= val){
        newnode->next = *head;
        *head = newnode;
        return;
    }

    Node *curr = *head;
    while(curr->next && curr->next->value < val) curr = curr->next;
    newnode->next = curr->next;
    curr->next = newnode;
}

int main(){
    FILE *fp;
    char filename[100];
    long long *arr = NULL;
    int capacity = 10,n = 0;

    arr = (long long*) malloc(capacity*sizeof(long long));
    if(!arr){ 
        printf("Memory allocation failed\n"); 
        return 0;
    }

    printf("Enter input filename: "); 
    scanf("%s", filename);
    fp = fopen(filename,"r");
    if(!fp){ 
        printf("File not found\n"); 
        free(arr); 
        return 0;
    }
    
    //determining the maximum value in the input array to scale bucket indices
    long long num, max = LLONG_MIN;
    while(1){
        if(n == capacity){ 
            capacity *= 2; 
            arr = (long long*) realloc(arr,capacity*sizeof(long long));
            if(!arr){ printf("Memory reallocation failed\n"); 
                fclose(fp); 
            return 0;} 
        }
        if(fscanf(fp,"%lld",&num)!=1) break;
        arr[n++] = num;
        if(num > max) max = num;
    }
    fclose(fp);

    int bucket_count = n;
    Node **buckets = (Node**) calloc(bucket_count, sizeof(Node*));
    for(int i = 0; i < n; i++){
        int idx = (int)((arr[i]*bucket_count)/(max+1));
        insert(&buckets[idx], arr[i]);
    }

    printf("Sorted: ");
    for(int i = 0; i < bucket_count; i++){
        Node *curr = buckets[i];
        while(curr){
            printf("%lld ", curr->value);
            Node *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    printf("\n");
    free(arr); free(buckets);
    return 0;
}
