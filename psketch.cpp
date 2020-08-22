#include "psketch.h"
#include <iostream>
#include "util.h"

using namespace std;

CMSketch::CMSketch(double eps, double delta) :
    w(ceil(exp(1)/eps)),
    d(ceil(log(1/delta))) {
    C.resize(d);
    for (auto i = 0U; i < d; i++) {
        C[i].resize(w, 0);
    }
    //srand(time(NULL));
    srand(0);
    hashes.resize(d);
    for (auto i = 0U; i < d; i++) {
        hashes[i].first = rand_int();
        hashes[i].second = rand_int();
    }
}

void CMSketch::clear() {
    for (auto i = 0U; i < d; i++) {
        fill(C[i].begin(), C[i].end(), 0);
    }
}

void CMSketch::update(ull item, int c) {
    for (auto j = 0U; j < d; j++) {
        auto hashval = (hashes[j].first * item + hashes[j].second) % w;
        C[j][hashval] += c;
    }
}

void CMSketch::update(const char *str, int c) {
    update(hashstr(str), c);
}

int CMSketch::estimate(ull item) {
    auto val = numeric_limits<int>::max();
    for (auto j = 0U; j < d; j++) {
        auto hashval = (hashes[j].first * item + hashes[j].second) % w;
        val = min(val, C[j][hashval]);
    }
    return val;
}

int CMSketch::estimate(const char *str) {
    return estimate(hashstr(str));
}

unsigned long long CMSketch::memory_usage() {
    return d * w * sizeof(int);
}

PCMSketch::PCMSketch(double eps, double delta, genType const& gen) : CMSketch(eps, delta){
    pla.resize(d);
    for (auto i = 0U; i < d; i++) {
        pla[i].resize(w, nullptr);
        for (auto j = 0U; j < w; j++) {
            pla[i][j] = gen(i,j);
        }
    }
}

PCMSketch::~PCMSketch() {
    for (auto i = 0U; i < d; i++) {
        for (auto j = 0U; j < w; j++) {
            delete pla[i][j];
        }
    }
}

void PCMSketch::clear() {
    CMSketch::clear();
    for (auto i = 0U; i < d; i++) {
        for (auto j= 0U; j < w; j++) {
            pla[i][j]->clear();
        }
    }
}

void PCMSketch::update(ull t, ull item, int c) {
    assert(c > 0);
    for (auto j = 0U; j < d; j++) {
        auto hashval = (hashes[j].first * item + hashes[j].second) % w;
        C[j][hashval] += c;
        pla[j][hashval]->feed({t, (double)C[j][hashval]});
    }
}

double PCMSketch::estimate(ull item, ull t) {
    double vals[d];
    for (auto j = 0U; j < d; j++) {
        auto hashval = (hashes[j].first * item + hashes[j].second) % w;
        vals[j] = pla[j][hashval]->estimate(t);
    }
    sort(vals, vals + d);
    if (d & 1) { // d is odd
        return vals[d/2];
    } else {
        return (vals[d/2] + vals[(d/2)-1]) / 2;
    }
}

void PCMSketch::update(ull t, const char *str, int c) {
    update(t, hashstr(str), c);
}

double PCMSketch::estimate(const char *str, ull t) {
    return estimate(hashstr(str), t);
}

double PCMSketch::burstiness(ull item, ull t, ull tau) {
    auto c = estimate(item, t);
    if (t < tau) {
        return c;
    }
    else  {
        auto b = estimate(item, t - tau);
        if (t < 2 * tau) {
            return c - 2 * b;
        }
        else {
            auto a = estimate(item, t - 2 * tau);
            return c - 2 * b + a;
        }
    }
}

ull PCMSketch::memory_usage() {
    ull sum = 0;
    for (auto i = 0U; i < d; i++) {
        for (auto j = 0U; j < w; j++) {
            sum += pla[i][j]->memory_usage();
        }
    }
    return CMSketch::memory_usage() + sum;
}


