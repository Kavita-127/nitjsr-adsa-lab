#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// Stack structure
struct Stack {
    int arr[MAX];
    int top;
};

// Initialize stack
void init(struct Stack *s) {
    s->top = -1;
}

// Check if empty
int isEmpty(struct Stack *s) {
    return s->top == -1;
}

// Check if full
int isFull(struct Stack *s) {
    return s->top == MAX - 1;
}

// Push into stack
void push(struct Stack *s, int x) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->arr[++s->top] = x;
}

// Pop from stack
int pop(struct Stack *s) {
    if (isEmpty(s)) {
        return -1;
    }
    return s->arr[s->top--];
}

// Queue using two stacks (Pop costly)
struct Queue {
    struct Stack s1, s2;
};

void initQueue(struct Queue *q) {
    init(&q->s1);
    init(&q->s2);
}

// Enqueue simple
void enqueue(struct Queue *q, int x) {
    push(&q->s1, x);
    printf("Inserted %d\n", x);
}

// Dequeue costly
int dequeue(struct Queue *q) {
    if (isEmpty(&q->s1)) {
        printf("Queue Underflow\n");
        return -1;
    }

    // Move everything except last element s1 → s2
    while (q->s1.top != 0) {
        push(&q->s2, pop(&q->s1));
    }

    // last inserted = front of queue
    int deleted = pop(&q->s1);

    // Move everything back to s1
    while (!isEmpty(&q->s2)) {
        push(&q->s1, pop(&q->s2));
    }

    return deleted;
}

// Display queue front → rear
void display(struct Queue *q) {
    if (isEmpty(&q->s1)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue (front -> rear): ");
    for (int i = 0; i <= q->s1.top; i++) {
        printf("%d ", q->s1.arr[i]);
    }
    printf("\n");
}

int main() {
    struct Queue q;
    initQueue(&q);
    int choice, val;

    while (1) {
        printf("\n--- Queue (Pop Costly) ---\n");
        printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value: ");
            scanf("%d", &val);
            enqueue(&q, val);
            break;
        case 2:
            val = dequeue(&q);
            if (val != -1) printf("Deleted %d\n", val);
            break;
        case 3:
            display(&q);
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}
