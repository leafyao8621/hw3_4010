typedef struct Point {
    int x;
    int y;
} Point;

Point* new_Point(int x, int y);
void add(Point* a, Point* b);
void sub(Point* a, Point* b);
void free_Point(Point* p);
