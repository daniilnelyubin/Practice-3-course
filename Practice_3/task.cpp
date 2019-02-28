//
// Created by daniilka on 27.02.19.
//

#include <iostream>
#include "task.h"
#include <algorithm>
#include <cmath>


int task(int N,int R,int r,point* points) {
    const double EPS = 1e-6;
    if (N < 1) {
        throw std::logic_error("Count of cities <1");
    }

    if (N > 100) {
        throw std::logic_error("Count of cities >100");
    }

    if (r < 1) {
        throw std::logic_error("City radius <1");
    }

    if (R < 1) {
        throw std::logic_error("Bomb radius <1");
    }

    if (r > 10000) {
        throw std::logic_error("City radius >10000");
    }

    if (R > 10000) {
        throw std::logic_error("Bomb radius >10000");
    }


    R -= r;
    int max = R >= 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int A = 0, B = 0;

            point m = (points[j] + points[i]) / 2;
            point v = points[j] - points[i];
            point perp = point(-v.y, v.x);
            double l = std::sqrt(
                    R * R - v.dist2() / 4);
            point a = m + perp.normalized() * l, b = m - perp.normalized() * l;

            for (int k = 0; k < N; k++) {
                if ((points[k] - a).dist() <= R + EPS)
                    A++;
                if ((points[k] - b).dist() <= R + EPS)
                    B++;
            }
            max = std::max({max, A, B});
        }
    }
    return max;
}
