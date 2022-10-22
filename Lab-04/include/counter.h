#ifndef COUNTER_H_
#define COUNTER_H_

#include <string>
#include <iostream>

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

class Counter{
    private:
        static bool check_decimal(const std::string &line, Statistics *stats, size_t & index, std::string &number_str);
        static void process_number(const std::string &line, Statistics *stats, size_t &index);
        static void process_word(const std::string &line, Statistics *stats, size_t &index);
        static bool process_line(const std::string &line, Statistics *stats);
    public:
        static bool process(const std::string& filename, Statistics *stats);
        static bool process(std::istream& is, Statistics *stats);
        static bool print(const std::string& filename, const Statistics *stats);
        static bool print(std::ostream& os, const Statistics *stats);
};

#endif