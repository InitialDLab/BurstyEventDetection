#include "heavyhitters.h"
#include "psketch.h"

using namespace std;

HeavyHitters::HeavyHitters(int level, PCMSketch::genType gen) : n_level(level), counter(0) {
    items.reserve(1<<n_level);
    pcm = new PCMSketch*[level];
    for (auto i = 0; i < level; ++i) {
        pcm[i] = new PCMSketch(0.0005, 0.1, gen);
    }
}

HeavyHitters::~HeavyHitters() {
    for (auto i = 0; i < n_level; ++i) {
        delete pcm[i];
    }
    delete [] pcm;
}

void HeavyHitters::update(ull t, ull x, int cnt) {
    auto id = get_count(x);
    for (auto i = 0; i < n_level; ++i) {
        auto j = id / (1 << i);
        pcm[i]->update(t, j, cnt);
    }
}

void HeavyHitters::hh(ull t, ull theta, vector<ull> &result, ull tau) {
    hh_rec(t, n_level - 1, 0, theta, result, tau);
}

void HeavyHitters::hh_rec(ull t, int l, ull x, int theta, vector<ull> &result, ull tau) {
    if (l == 0) {
        auto c = pcm[0]->burstiness(x, t, tau);
        if (c >= theta) {
            result.push_back(items[x]);
        }
    }
    else {
        auto x1 = x * 2;
        auto x2 = x * 2 + 1;
        auto c = pcm[l]->burstiness(x, t, tau);
        auto a = pcm[l-1]->burstiness(x1, t, tau);
        auto b = pcm[l-1]->burstiness(x2, t, tau);
        if (c * c - 2 * a * b >= theta * theta) {
            hh_rec(t, l - 1, x1, theta, result, tau);
            hh_rec(t, l - 1, x2, theta, result, tau);
        }
    }
}

int HeavyHitters::get_count(int x) {
    auto it = m.find(x);
    if (it == m.end()) {
        m[x] = counter;
        items.push_back(x);
        return counter++;
    }
    else {
        return it->second;
    }
}

