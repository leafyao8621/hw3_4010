typedef struct Car {
    double time_arr;
    double time_start;
    double time_out;
    double tiq;
    double tis;
    int dir;
    double delay;
    struct Car* next;
} Car;

Car* new_Car(double time_arr, int dir);
int leave_queue(Car* c, double time_start);
int leave_sys(Car* c, double time_out);
int print_Car(Car* c);
