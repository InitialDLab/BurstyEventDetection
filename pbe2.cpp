#include "../src/util.h"
#include "../src/pla.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

int main() {
    ofstream val("pbe2_football_val");
    ofstream st("pbe2_football_st");
    for (int i = 1; i <= 1000; ++i) {
        PLA s;
        s.set_param((double)i);
        ifstream f("../data/football.dat");
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

