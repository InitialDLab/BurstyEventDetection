#include <cstdint>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <cmath>
#include <iostream>
#include "../src/util.h"

using namespace std;

int get_val(ull t, const vector<point> &v) {
    auto len = v.size();
    //if (t < 0) return 0;
    if (t >= v[len - 1].x) return v[len - 1].y;
    int l = 0, r = len - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (v[m].x < t) {
            l = m + 1;
        }
        else {
            r = m;
        }
    }
    return v[l].y;
}

int point_query(ull t, ull tau, const vector<point> &v) {
    auto x1 = get_val(t, v);
    if (t < tau) return x1;
    auto x2 = get_val(t - tau, v);
    if (t < 2 * tau) return x1 - 2 * x2;
    auto x3 = get_val(t - 2 * tau, v);
    return x1 - 2 * x2 + x3;
}

vector<int> heavy_hitter(ull theta, ull tau, const vector<point> &v) {
    vector<int> res;
    for (int i = 0; i < v.size(); ++i) {
        if (point_query(i, tau, v) > theta) {
            res.push_back(i);
        }
    }
    return move(res);
}

void read_file(const char* filename, vector<point> &v) {
    ifstream f(filename);
    ull x, y, z;
    while (f) {
        f >> x >> y >> z;
        v.push_back({x, (double)z});
    }
}

vector<point> v;
int main(int argc, char **argv) {
    if (argc == 1) {
        read_file("../data/swimming.dat", v);
    }
    else {
        read_file(argv[1], v);
    }
    auto &of = cout;
    for (auto i = 0; i < 50000; i += 1440) {
        of << i << " " << point_query(i, 1440, v) << endl;
    }
}
