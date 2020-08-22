#ifndef pla_h
#define pla_h

#include <limits>
#include <vector>
#include <cmath>
#include <iostream>
#include <cassert>
#include "approx.h"

class PLA : public Approx {

    public:

		PLA();
        
        ~PLA() {}

        struct segment{
            unsigned long long start, end;
            double slope;
            double intercept;
        };

        void set_param(double);

        void clear();

        double estimate(ull);

        void feed(point);

        size_t memory_usage();

        std::vector<segment> result;

    private:

        int tollerance;

        double lower, upper;
        //available slope range : [lower, upper]
        point begin;
        //current time segment start point : begin
        point last;
        //last point
        
        bool initialized;

        double buffer_lower, buffer_upper;
        point buffer_begin, buffer_last;
        bool buffer_initialized;


        inline double valueAtTime(double slope, double intercept, unsigned long long time) {
            return slope * time + intercept;
        }

        inline double pointSlope(point pt1, point pt2) {
            assert(pt2.x > pt1.x);
            return (pt2.y - pt1.y) / (pt2.x - pt1.x);
        }
};

#endif
