#ifndef DATABASE_H_
#define DATABASE_H_
#include "Title.h"
#include <vector>
#include <memory>
#include "Movie.h"
#include "Series.h"
#include "Actor.h"
#include <map>
#include <unordered_map>

using namespace std;

class Database {
    private:
        static bool process_csv_line(const string& line, shared_ptr<Title>& m); 
        static bool process_number(const string& temp, unsigned short& value);
    public:
        static bool import(const string& filename, vector<shared_ptr<Title>>& db);
        static bool import(istream& is, vector<shared_ptr<Title>>& db);
};

class FilterPredicate{
    private:
        Actor actor_;
    public:
        FilterPredicate(Actor actor);
        bool operator()(const shared_ptr<Title>& title_ptr);
};

class Comparator{
    public:
        bool operator()(const shared_ptr<Title>& title_ptr_1, const shared_ptr<Title>& title_ptr_2){
            // sestupne podle roku natoceni
            return title_ptr_1->year() > title_ptr_2->year() || 
            (title_ptr_1->year() == title_ptr_2->year() && title_ptr_1->name() < title_ptr_2->name());
        } 
};

class CountIfPredicate{
    private: 
        int rating_sum_;
        int counter_;
        Type type_;
        string genre_;
    public:
        CountIfPredicate(Type type, const string genre);
        void operator()(const shared_ptr<Title>& title_ptr);
        inline int counter() { return counter_; }
        inline int rating_sum() {return rating_sum_; }
};

void db_index_titles(const std::vector<std::shared_ptr<Title>>& db, std::map<std::string, std::shared_ptr<Title>>& index);

void db_index_years(const vector<shared_ptr<Title>>& db, multimap<unsigned short, shared_ptr<Title>>& index);

void db_index_actors(const vector<shared_ptr<Title>>& db, unordered_multimap<Actor, shared_ptr<Title>>& index);

void db_query_1(const vector<shared_ptr<Title>>& db);

void db_query_2(const vector<shared_ptr<Title>>& db);

void db_query_3(const vector<shared_ptr<Title>>& db, unsigned short seasons, unsigned short episodes);

void db_query_4(const vector<shared_ptr<Title>>& db, const type_info& type, unsigned short begin, unsigned short end);

void db_query_5(const map<string, shared_ptr<Title>>& index, const string& name);

void db_query_6(const multimap<unsigned short, shared_ptr<Title>>& index, unsigned short year);

void db_query_7 (const multimap<unsigned short, shared_ptr<Title>>& index, unsigned short begin, unsigned short end);

void db_query_8 (const unordered_multimap<Actor, shared_ptr<Title>>& index, const Actor& actor);

void db_query_9(const vector<shared_ptr<Title>>& db, vector<shared_ptr<Title>>& result, const Actor& actor);

void db_query_10(const vector<shared_ptr<Title>>& db, vector<shared_ptr<Title>>& result, const string& genre);

void db_query_11(const vector<shared_ptr<Title>>& db, Type type, const string& genre, int& result);

void db_query_12(const vector<shared_ptr<Title>>& db, const string& genre, int& result);

#endif