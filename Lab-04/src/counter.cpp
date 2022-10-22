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

bool check_decimal(const std::string &line, Statistics *stats, size_t &index, std::string &number_str){
    if (line.length() > index + 2 && line[index] == '.' && isdigit(line[index + 1])){
        ++stats->symbol_count;
        ++index;
        while(isdigit(line[index])){
            number_str += line[index];
            ++stats->digit_count;
            ++index;
        }
        return true;
    }
    else 
        return false;
}

void Counter::process_number(const std::string &line, Statistics *stats, size_t &index){
    std::string num_str = "";
    while (isdigit(line[index])){
            num_str += line[index];
            ++stats->digit_count;
            ++index;
    }
    size_t ix;
    if (check_decimal(line, stats, index, num_str)){ // is float
        float num = std::stof(num_str, &ix);
        stats->float_sum += (double)num;
    }
    else {// is int
        int num = std::stoi(num_str, &ix);
        stats->float_sum += (double)num;
    }
}

void Counter::process_word(const std::string &line, Statistics *stats, size_t &index){
    std::string word = "";
    while (isalpha(line[index])){
        word += line[index];
        ++stats->letter_count;
        ++index;
    }
}

bool Counter::process_line(const std::string &line, Statistics *stats){
    ++stats->line_count;
    for(size_t i = 0; i < line.length(); ++i){
        if (isalpha(line[i]))
            process_word(line, stats, i);
        if (isdigit(line[i]))
            process_number(line, stats, i);
    }
    return true;
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
