#ifndef STAIRCASE_H
#define STAIRCASE_H

#include "util.h"
#include "approx.h"
#include <vector>

class Staircase : public Approx {

    public:
        
        Staircase() {}
        
        ~Staircase() {}

        void set_param(std::pair<int, int>);

        void clear();

        double estimate(ull);

        void feed(point);

        size_t memory_usage();

    private:
        unsigned buffer_size;
        unsigned eta;
        std::vector<point> pt;
        std::vector<point> buffer;
        void dp();
};

#endif
