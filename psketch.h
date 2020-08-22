#ifndef psketch_h
#define psketch_h

#include <cmath>
#include <cstring>
#include <limits>
#include <algorithm>
#include <vector>
#include <cassert>
#include <functional>
#include "approx.h"
#include "util.h"

class CMSketch {
    protected:
        const unsigned int w, d;
        std::vector<std::vector<int>> C;
        std::vector<std::pair<int, int>> hashes;

        inline unsigned int hashstr(const char *str) {
            unsigned long hash = 5381;
            int c;
            while ((c = *str++)) {
                hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
            }
            return hash;
        }

        inline int rand_int() {
            #define LONG_PRIME 32993
            return int(double(rand())*double(LONG_PRIME)/double(RAND_MAX) + 1);
        }

    public:
        CMSketch(double, double);

        void clear();

        void update(ull, int = 1);

        void update(const char *, int = 1);

        int estimate(ull);

        int estimate(const char *);

        unsigned long long memory_usage();
};

class PCMSketch : public CMSketch {
    private:
        std::vector<std::vector<Approx *>> pla;
        
    public:
        typedef std::function<Approx *(unsigned, unsigned)> genType;

        PCMSketch(double, double, genType const&);

        ~PCMSketch();

        void clear();
        
        void update(ull, ull, int = 1);

        void update(ull, const char *, int = 1);

        double estimate(ull, ull);

        double estimate(const char *, ull);

		double burstiness(ull, ull, ull);

        ull memory_usage();
};

#endif
