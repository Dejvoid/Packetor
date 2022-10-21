#ifndef COUNTER_H_
#define COUNTER_H_

#include <string>
#include <iostream>

class Counter{
    public:
        static bool process(const std::string& filename, Statistics *stats);
        static bool process(std::istream& is, Statistics *stats);
        static bool print(const std::string& filename, const Statistics *stats);
        static bool print(std::ostream& os, const Statistics *stats);
};

class Statistics{
    public:
        size_t letter_count = 0;
        size_t word_count = 0;
        size_t line_count = 0;
        size_t symbol_count = 0;
        size_t sentence_count = 0;
        size_t space_count = 0;
        size_t number_count = 0;
        size_t digit_count = 0;
        long int_sum = 0;
        double float_sum = 0;
};

#endif