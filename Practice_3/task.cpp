//
// Created by daniilka on 27.02.19.
//

#include <iostream>
#include "task.h"
#include <algorithm>
#include <cmath>


void task() {
    point *points= new point[100];
    const double EPS = 1e-6;
    int N, x, y, R, r;
    std::cin >> N;
    if (N < 1) {
        throw std::logic_error("Count of cities <1");
    }

    if (N > 100) {
        throw std::logic_error("Count of cities >100");
    }
    for (int i = 0; i < N; i++)
        std::cin >> points[i].x >> points[i].y;
    std::cin >> R >> r;

    if (r <= 0) {
        throw std::logic_error("City radius <=0");
    }

    if (R <= 0) {
        throw std::logic_error("Bomb radius <=0");
    }

    if (r > 10000) {
        throw std::logic_error("City radius >10000");
    }

    if (R >= 10000) {
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
    std::cout << max;
}
