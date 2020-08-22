#ifndef APPROX_H
#define APPROX_H

#include "util.h"
#include <vector>


class Approx {

    public:
        
        virtual ~Approx() {};

        virtual void set_param(std::pair<int, int>) {}
		
		virtual void set_param(double) {}

        virtual void clear() = 0;

        virtual double estimate(ull) = 0;

        virtual void feed(point) = 0;

        virtual size_t memory_usage() = 0;

        double burstiness(ull t, ull tau) {
            auto c = estimate(t);
            if (t < tau) {
                return c;
            }
            else  {
                auto b = estimate(t - tau);
                if (t < 2 * tau) {
                    return c - 2 * b;
                }
                else {
                    auto a = estimate(t - 2 * tau);
                    return c - 2 * b + a;
                }
            }
        }

};

#endif
