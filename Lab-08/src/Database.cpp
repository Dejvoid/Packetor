#include "Database.h"
#include <sstream>
#include <fstream>

bool Database::process_number(const std::string& temp, unsigned short& value){
    size_t p;
    try{
        value = (unsigned short)std::stoi(temp, &p);
    }
    catch (...){ return false; }
    if (p - temp.length() > 0)
        return false;
    return true;
};

bool Database::process_csv_line(const std::string& line, std::shared_ptr<Title>& m){
    char splitter = ';';
    char list_splitter = ',';
    bool ret_value = true;
    auto line_stream = std::istringstream(line);
    // process entry
    Type type;
    std::string name;
    unsigned short year;
    std::string genre;
    unsigned short rating;
    set<Actor> actors;
    std::string temp;

    // Type info: 
    std::getline(line_stream, temp, splitter);
    if (temp == "MOVIE")
        type = Type::MOVIE;
    else if (temp == "SERIES")
        type = Type::SERIES;
    else return false;
    // Title name:
    std::getline(line_stream, name, splitter); 
    // Title year:
    std::getline(line_stream, temp, splitter);
    if (!process_number(temp, year))
        return false;
    // Title genre
    std::getline(line_stream, genre, splitter);
    // Title rating
    std::getline(line_stream, temp, splitter);
    if(!process_number(temp, rating))
        return false;
    std::getline(line_stream, temp, splitter);
    stringstream ss = stringstream(temp);
    for (std::string act_str; std::getline(ss, act_str, list_splitter);){
        Actor actor;
        stringstream ss = stringstream(act_str);
        ss >> actor;
        actors.emplace(std::move(actor));
    }
    if (type == Type::MOVIE){
        unsigned short length;
        std::getline(line_stream, temp, splitter);
        if (!process_number(temp, length))
            return false;
        m = std::make_shared<Movie>(std::move(name), year, std::move(genre), rating, std::move(actors), length);
    }
    else if (type == Type::SERIES){
        unsigned short seasons;
        std::getline(line_stream, temp, splitter);
        if (!process_number(temp, seasons))
            return false;
        unsigned short episodes;
        std::getline(line_stream, temp, splitter);
        if (!process_number(temp, episodes))
            return false;
        
        m = std::make_shared<Series>(std::move(name), year, std::move(genre), rating, std::move(actors), seasons, episodes);
    }
    return ret_value;
};

bool Database::import(std::istream& is, std::vector<std::shared_ptr<Title>>& db){
    bool ret_value = true;
    for (std::string line; std::getline(is, line);){ // read all entries
        std::shared_ptr<Title> m;
        if (line.size() != 0){
            if (process_csv_line(line, m))
                //db.emplace_back(std::move(m));
                db.emplace_back(m);
            else 
                ret_value &= false;
        }
    }
    return ret_value;
};

bool Database::import(const std::string& filename, std::vector<std::shared_ptr<Title>>& db){
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
};

bool filter(const shared_ptr<Title> m){
    std::string desired_genre = "comedy";
    unsigned short desired_year = 2010;
    std::string desired_first_name1 = "Ivan";
    std::string desired_last_name1 = "Trojan";
    
    std::string desired_first_name2 = "Tereza";
    std::string desired_last_name2 = "Voriskova";
    bool ret_value = true;
    ret_value &= m->genre() == desired_genre;
    ret_value &= m->year() < desired_year;
    bool contains_actor = false;
    for (auto &&actor : m->actors()){
        contains_actor |= (actor.first_name() == desired_first_name1 && actor.last_name() == desired_last_name1)  ||
                        (actor.first_name() == desired_first_name2 && actor.last_name() == desired_last_name2);
    }
    ret_value &= contains_actor;
    return ret_value;
};

void db_query_1(const vector<shared_ptr<Title>>& db){
    for (auto it = db.begin(); it != db.end(); ++it){
        (*it)->print_json();
    }
};

void db_query_2(const vector<shared_ptr<Title>>& db){
    for (auto it = db.begin(); it != db.end(); ++it){
        if (filter(*it))
            std::cout << (*it)->name() << std::endl;
    }
};

void db_query_3(const vector<shared_ptr<Title>>& db, unsigned short seasons, unsigned short episodes){
    for(auto it = db.begin(); it != db.end(); ++it){
        if ((*it)->type() == Type::SERIES){
            auto s = std::dynamic_pointer_cast<Series>(*it);
            if (s->episodes() >= episodes || s->seasons() >= seasons)
                s->print_json();
        }
    }
};

void db_query_4(const vector<shared_ptr<Title>>& db, const type_info& type, unsigned short begin, unsigned short end){
    for(auto it = db.begin(); it != db.end(); ++it){
        if (type == typeid(**it) && (*it)->year() >= begin && (*it)->year() < end)
            std::cout << (*it)->name() << std::endl;
    }
};