#include "../src/util.h"
#include "../src/staircase.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

int main() {
    ofstream val("pbe1_swimming_val");
    ofstream st("pbe1_swimming_st");
    for (int i = 2; i < 73; ++i) {
        Staircase s;
        s.set_param({i, 1500});
        ifstream f("../data/swimming.dat");
        auto start = clock();
        while (f) {
            ull x, y, z;
            f >> x >> y >> z;
            s.feed({x, (double)z});
        }
        auto duration = (clock() - start) / (double)CLOCKS_PER_SEC;

		for (int ts = 0; ts < 50000; ts += 1440) {
            val << i << " " << ts;
            val << " " << s.burstiness(ts, 1440);
            val << endl;
        }
        st << i << " " << s.memory_usage() << " " << duration << endl;
	}
}

