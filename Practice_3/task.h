#ifndef PRACTICE_3_TASK_H
#define PRACTICE_3_TASK_H
#include <cmath>
struct point {
    double x, y;

    point(double x = 0, double y = 0) : x(x), y(y) {}

    point operator-(const point &p) const { return point(x - p.x, y - p.y); }

    point operator*(double t) const { return point(t * x, t * y); }

    point operator/(double t) const { return point(x / t, y / t); }

    point operator+(const point &p) const { return point(x + p.x, y + p.y); }

    point normalized() const { return point(x / dist(), y / dist()); }

    double dist2() const { return x * x + y * y; }

    double dist() const { return std::sqrt(x * x + y * y); }
};


int task(int N,int R,int r,point* points);



#endif //PRACTICE_3_TASK_H
