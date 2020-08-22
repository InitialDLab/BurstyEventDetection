#include "staircase.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

void Staircase::set_param(pair<int, int> p) {
    eta = p.first;
    buffer_size = p.second;
}

void Staircase::clear() {
    pt.clear();
    buffer.clear();
}

size_t Staircase::memory_usage() {
    return (pt.size() * sizeof(point));
}

void Staircase::feed(point p) {
    if (!buffer.empty() && buffer[buffer.size() - 1].x >= p.x) {
        assert(buffer[buffer.size() - 1].x == p.x);
        buffer[buffer.size() - 1].y = p.y;
    }
    else {
        if (!buffer.empty()) {
            assert(buffer[buffer.size() - 1].y <= p.y);
        }
        if (buffer.size() == buffer_size) {
            dp();
        }
        buffer.push_back(p);
    }
}

double Staircase::estimate(ull x) {
    auto t = &pt;
    if (!buffer.empty() && x >= buffer[0].x) {
        t = &buffer;
    }
    auto pos = upper_bound(t->begin(), t->end(), x, [](unsigned v, point p) {return v < p.x;});
    if (pos == t->begin()) {
        return 0;
    }
    else {
		auto x2 = pos->x;
		auto y2 = pos->y;
		auto x1 = (pos - 1)->x;
		auto y1 = (pos - 1)->y;
        return y1 + (y2 - y1) / (x2 - x1) * (x - x1);
    }
}

void Staircase::dp() {

	assert(buffer.size() >= 2);
	
    ull **f = (ull **)malloc(buffer.size() * sizeof(ull *));
    int **p = (int **)malloc(buffer.size() * sizeof(int *));
    for (auto i = 0; i < buffer.size(); ++i) {
        f[i] = (ull *)malloc((eta + 1) * sizeof(ull));
        p[i] = (int *)malloc((eta + 1) * sizeof(int));
    }

    auto m = buffer.size() - 1;

    f[0][0] = 0;
    for (auto i = 0U; i < m; ++i) {
        assert(buffer[i+1].y >= buffer[i].y);
        assert(buffer[i+1].x >= buffer[i].x);
        f[0][0] += (buffer[i+1].x - buffer[i].x) * (buffer[i].y - buffer[0].y);
    }

    auto min_cost = inf;
    auto min_i = 0;

    for (auto i = 1U; i < m; ++i) {

        f[i][0] = inf;
        for (auto j = 1U; j <= min(i, eta); ++j) {
            f[i][j] = inf;
            for (auto k = j - 1; k < i; ++k) {
                auto delta = (buffer[m].x - buffer[i].x) * (buffer[i].y - buffer[k].y);
                auto t = f[k][j-1] - delta;
                if (t < f[i][j]) {
                    p[i][j] = k;
                    f[i][j] = t;
                }
            }
        }
        if (i >= eta && f[i][eta] <= min_cost) {
            min_cost = f[i][eta];
            min_i = i;
        }
    }
    vector<int> tmp;
    tmp.reserve(eta + 2);
    auto i = min_i;
    auto j = eta;
    tmp.push_back(m);
    while (i > 0) {
        tmp.push_back(i);
        i = p[i][j];
        --j;
    }
    tmp.push_back(0);
    for (auto it = tmp.rbegin(); it != tmp.rend(); ++it) {
        pt.push_back(buffer[*it]);
    }
    for (auto i = 0; i < buffer.size(); ++i) {
        free(f[i]);
        free(p[i]);
    }
    free(f);
    free(p);
    buffer.clear();
}
