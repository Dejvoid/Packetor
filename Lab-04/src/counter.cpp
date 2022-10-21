#include "counter.h"
#include <fstream>

bool Counter::process(const std::string& filename, Statistics *stats){    // otevre ifstream, zavola jinou, ktera zpracuje obecny istream
    bool result = true;
    std::ifstream ifs;
    ifs.open(filename);
    if (!ifs.good()){ // ifs not good?
        return false;
    }
    result &= process(ifs, stats);
    ifs.close();
    return result;
}

bool Counter::process_line(const std::string &line, Statistics *stats){
    stats->line_count++;
    
}

bool Counter::process(std::istream& is, Statistics *stats){
    std::string line;
    while (std::getline(is, line)){
        process_line(line, stats);
    }
    return true;
}

bool Counter::print(const std::string& filename, const Statistics *stats){
    bool result = true;
    std::ofstream ofs;
    ofs.open(filename);
    if (!ofs.good()){
        return false;
    }
    result &= print(ofs, stats);
    return result;
}

bool Counter::print(std::ostream& os, const Statistics *stats){
    os << "Lines: " << stats->line_count << std::endl;
    os << "Sentences: " << stats->sentence_count << std::endl;
    os << "Words: " << stats->word_count << std::endl;
    os << "Numbers: " << stats->number_count << std::endl;
    os << "Letters: " << stats->letter_count << std::endl;
    os << "Digits: " << stats->digit_count << std::endl;
    os << "Spaces: " << stats->space_count << std::endl;
    os << "Symbols: " << stats->symbol_count << std::endl;
    os << "Integers: " << stats->int_sum << std::endl;
    os << "Floats: " << stats->float_sum << std::endl;
    return true;
}
