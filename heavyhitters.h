#ifndef HEAVYHITTERS_H
#define HEAVYHITTERS_H
#include <map>
#include <vector>
#include "util.h"
#include "psketch.h"

class HeavyHitters {

    public:
        HeavyHitters(int level, PCMSketch::genType gen);

        ~HeavyHitters();

        void update(ull, ull, int = 1);

        void hh(ull, ull, std::vector<ull> &, ull = 100);

    private:
        int n_level;
        PCMSketch **pcm;
        int counter;
        std::map<int, int> m;
        std::vector<ull> items;
        void hh_rec(ull, int, ull, int, std::vector<ull> &, ull);
        int get_count(int x);
};


#endif
