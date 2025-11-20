/*SET-9
  Q34. Implement Graham scan algorithm or Jarvis March algorithm to find a convex hull of a set of N points
       whose coordinates are given as (x1, y1), (x2, y2), … ,(xn, yn). 
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

Point P0;   // global reference point

Point nextToTop(Point* stack, int top) {
    return stack[top - 1];
}

void swap(Point* a, Point* b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

int orientation(Point a, Point b, Point c) {
    long long val = (long long)(b.y - a.y) * (c.x - b.x) -
                    (long long)(b.x - a.x) * (c.y - b.y);

    if (val == 0) return 0;          // collinear
    return (val > 0) ? 1 : 2;        // 1 = clockwise, 2 = counter-clockwise
}

// Distance squared
long long distSq(Point a, Point b) {
    return (long long)(a.x - b.x) * (a.x - b.x) +
           (long long)(a.y - b.y) * (a.y - b.y);
}

// Comparator for qsort (increasing polar angle)
int compare(const void* p1, const void* p2) {
    Point a = *(Point*)p1;
    Point b = *(Point*)p2;

    int o = orientation(P0, a, b);
    if (o == 0) {
        // Keep farthest point last
        return (distSq(P0, b) >= distSq(P0, a)) ? -1 : 1;
    }
    return (o == 2) ? -1 : 1; 
}

// Graham Scan Convex Hull
void convexHull(Point points[], int n) {
    // Step 1: Find lowest y (and leftmost in tie)
    int min_idx = 0;
    for (int i = 1; i < n; i++) {
        if ((points[i].y < points[min_idx].y) ||
            (points[i].y == points[min_idx].y && points[i].x < points[min_idx].x))
            min_idx = i;
    }

    swap(&points[0], &points[min_idx]);
    P0 = points[0];

    // Step 2: Sort points by polar angle w.r.t P0
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // Step 3: Remove collinear points except farthest
    int m = 1;  
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(P0, points[i], points[i + 1]) == 0)
            i++;
        points[m++] = points[i];
    }

    if (m < 3) {
        printf("Convex hull not possible\n");
        return;
    }

    // Step 4: Use stack (array) to build hull
    Point stack[m];
    int top = 0;

    stack[top++] = points[0];
    stack[top++] = points[1];
    stack[top++] = points[2];

    for (int i = 3; i < m; i++) {
        while (top >= 2 && orientation(nextToTop(stack, top), stack[top - 1], points[i]) != 2)
            top--;
        stack[top++] = points[i];
    }

    // Output hull
    printf("Convex Hull Points:\n");
    for (int i = 0; i < top; i++)
        printf("(%d, %d)\n", stack[i].x, stack[i].y);
}

int main() {
    Point points[] = {{0,3},{2,3},{1,1},{2,1},{3,0},
                      {0,0},{3,3}};
    int n = sizeof(points) / sizeof(points[0]);

    convexHull(points, n);
    return 0;
}

