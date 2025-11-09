/* SET-3
   Q8. Implement a stack using two queues by Method 1 (making EnQueue operation costly) and by Method 2
       (making DeQueue operation costly in terms of time). */
//METHOD 1

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// Queue structure
struct Queue {
    int arr[MAX];
    int front, rear;
};

// Queue functions
void init(struct Queue *q){ 
    q->front = q->rear = -1; 
}

int isEmpty(struct Queue *q){ 
    return q->front == -1; 
}

int isFull(struct Queue *q){ 
    return (q->rear + 1) % MAX == q->front; 
}

void enqueue(struct Queue *q, int x){
    if (isFull(q)){ 
        printf("Queue Overflow\n"); 
        return; 
    }
    if (q->front == -1) 
        q->front = 0;
    q->rear = (q->rear + 1) % MAX;
    q->arr[q->rear] = x;
}

int dequeue(struct Queue *q){
    if (isEmpty(q)) 
        return -1;
    int x = q->arr[q->front];
    if (q->front == q->rear) 
        q->front = q->rear = -1;
    else 
        q->front = (q->front + 1) % MAX;
    return x;
}

void displayQueue(struct Queue *q){
    if (isEmpty(q)){ 
        printf("Stack is empty\n"); 
        return; 
    }

    int i = q->front;
    printf("(top -> bottom): ");
    while (1){
        printf("%d ", q->arr[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

// Stack using two queues (Push costly)
struct Stack {
    struct Queue q1, q2;
};

void initStack(struct Stack *s) {
    init(&s->q1); 
    init(&s->q2);
}

void push(struct Stack *s, int x) {
    while (!isEmpty(&s->q1)) 
        enqueue(&s->q2, dequeue(&s->q1));
    enqueue(&s->q1, x);
    while (!isEmpty(&s->q2)) 
        enqueue(&s->q1, dequeue(&s->q2));
    printf("Pushed %d\n", x);
}

int pop(struct Stack *s) {
    if (isEmpty(&s->q1)){ 
        printf("Stack Underflow\n"); 
        return -1; 
    }
    return dequeue(&s->q1);
}

void display(struct Stack *s) {
    displayQueue(&s->q1);
}

// Main menu
int main() {
    struct Stack s;
    initStack(&s);
    int choice, val;

    while (1) {
        printf("\n--- Stack (Push Costly) ---\n");
        printf("1. Push\n2. Pop\n3. Display\n4. Exit\n");
        printf("Enter choice: "); 
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value: "); 
                scanf("%d", &val);
                push(&s, val); 
                break;
            case 2:
                val = pop(&s);
                if(val != -1) 
                    printf("Popped %d\n", val);
                break;
            case 3: 
                display(&s); 
            break;
            case 4: 
                exit(0);
            default: 
                printf("Invalid choice\n");
        }
    }
    return 0;
}

