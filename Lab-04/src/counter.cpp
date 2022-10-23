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

bool Counter::is_float(const std::string &line, Statistics *stats, size_t &index, std::string &number_str){
    if ((line.length() > (index + 1)) && (line[index] == '.') && isdigit(line[index + 1])){
        ++stats->symbol_count;
        number_str += line[index];
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
    if (is_float(line, stats, index, num_str)){ // is float
        float num = std::stof(num_str, &ix);
        stats->float_sum += (double)num;
    }
    else {// is int
        int num = std::stoi(num_str, &ix);
        stats->int_sum += (long)num;
    }
    ++stats->number_count;
    --index;
}

void Counter::process_word(const std::string &line, Statistics *stats, size_t &index){
    std::string word = "";
    while (isalpha(line[index])){
        word += line[index];
        ++stats->letter_count;
        ++index;
    }
    ++stats->word_count;
    --index;
}

bool Counter::process_line(const std::string &line, Statistics *stats, bool &in_sentence){
    ++stats->line_count;
    for(size_t i = 0; i < line.length(); ++i){
        if (isalpha(line[i])){
            process_word(line, stats, i);
            in_sentence = true;
        }
        else if (isdigit(line[i])){
            process_number(line, stats, i);
            in_sentence = true;
        }
        else if (line[i] == ' ')
            ++stats->space_count;
        else if (line[i] == '.' || line[i] == '!' || line[i] == '?'){
            ++stats->symbol_count;
            if (in_sentence){
                ++stats->sentence_count;
                in_sentence = false;
            }
        }
    }
    return true;
}

bool Counter::process(std::istream& is, Statistics *stats){
    std::string line;
    bool in_sentence = false;
    while (std::getline(is, line)){
        process_line(line, stats, in_sentence);
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
