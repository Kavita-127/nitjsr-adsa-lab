/*SET-9
  Q34. Implement Graham scan algorithm or Jarvis March algorithm to find a convex hull of a set of N points
        whose coordinates are given as (x1, y1), (x2, y2), … ,(xn, yn).
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

int orientation(Point a, Point b, Point c) {
    long long val = (long long)(b.y - a.y) * (c.x - b.x) -
                    (long long)(b.x - a.x) * (c.y - b.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// Function to find the convex hull using Jarvis March
void jarvisMarch(Point points[], int n) {
    if (n < 3) {
        printf("Convex hull not possible\n");
        return;
    }

    int *hull = (int*)malloc(n * sizeof(int));
    int hull_size = 0;

    // Step 1: Find the leftmost point
    int leftmost = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[leftmost].x ||
           (points[i].x == points[leftmost].x && points[i].y < points[leftmost].y))
            leftmost = i;

    int p = leftmost;

    // Step 2: Wrap around the points
    do {
        hull[hull_size++] = p;
        int q = (p + 1) % n;

        for (int i = 0; i < n; i++) {
            if (orientation(points[p], points[i], points[q]) == 2) {
                q = i;
            }
        }

        p = q;
    } while (p != leftmost);

    // Step 3: Print the convex hull points
    printf("Convex Hull Points in counter-clockwise order:\n");
    for (int i = 0; i < hull_size; i++) {
        printf("(%d, %d)\n", points[hull[i]].x, points[hull[i]].y);
    }

    free(hull);
}

int main() {
    Point points[] = {{0,3},{2,3},{1,1},{2,1},{3,0},{0,0},{3,3}};
    int n = sizeof(points) / sizeof(points[0]);

    jarvisMarch(points, n);

    return 0;
}

