#include "Database.h"
#include <sstream>
#include <fstream>

bool Database::process_csv_line(const std::string& line, Title& m){
    char splitter = ';';
    char list_splitter = ',';
    bool ret_value = true;
    auto line_stream = std::istringstream(line);
    // process entry
    std::string name;
    unsigned short year;
    std::string genre;
    unsigned short rating;
    set<string> actors;
    size_t p;
    // Title name:
    std::getline(line_stream, name, splitter); 
    std::string temp;
    // Title year:
    std::getline(line_stream, temp, splitter);
    try{
        year = (unsigned short)std::stoi(temp,&p);
    }
    catch(...){ return false; }
    if (p - temp.length() > 0)
        return false;
    // Title genre
    std::getline(line_stream, genre, splitter);
    // Title rating
    std::getline(line_stream, temp, splitter);
    try{
        rating = (unsigned short)std::stoi(temp, &p);
    }
    catch (...){ return false; }
    if (p - temp.length() > 0)
        return false;
    for (std::string actor; std::getline(line_stream, actor, list_splitter);){
        actors.emplace(std::move(actor));
    }
    m = Title(std::move(name), year, std::move(genre), rating, std::move(actors));
    return ret_value;
}

bool Database::import(std::istream& is, std::vector<Title>& db){
    bool ret_value = true;
    for (std::string line; std::getline(is, line);){ // read all entries
        Title m;
        if (process_csv_line(line, m))
            db.emplace_back(std::move(m));
        else 
            ret_value &= false;
    }
    return ret_value;
}

bool Database::import(const std::string& filename, std::vector<Title>& db){
    // open file (csv), import films, add to vector
    bool ret_val = true;
    std::ifstream fs;
    fs.open(filename, std::fstream::in);
    if (fs.good()){
        ret_val &= import(fs, db);
    }
    else 
        ret_val &= false;
    fs.close();
    return ret_val;
}

bool filter(const Title* m){
    std::string desired_genre = "comedy";
    unsigned short desired_year = 2010;
    std::string desired_actor1 = "Ivan Trojan";
    std::string desired_actor2 = "Tereza Voriskova";
    bool ret_value = true;
    ret_value &= m->genre() == desired_genre;
    ret_value &= m->year() < desired_year;
    //ret_value &= m.actors().contains("Ivan Trojan") || m.actors().contains("Tereza Voriskova"); - exists in c++20
    ret_value &= m->actors().find(desired_actor1) != m->actors().end() 
        || m->actors().find(desired_actor2) != m->actors().end();
    return ret_value;
}

void db_query_1(const std::vector<Title>& db){
    for (auto it = db.begin(); it != db.end(); ++it){
        it.base()->print_json();
    }
}

void db_query_2(const std::vector<Title>& db){
    for (auto it = db.begin(); it != db.end(); ++it){
        if (filter(it.base()))
            std::cout << it.base()->name() << std::endl;
    }
}