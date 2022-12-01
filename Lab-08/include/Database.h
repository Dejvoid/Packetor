#ifndef DATABASE_H_
#define DATABASE_H_
#include "Title.h"
#include <vector>
#include <memory>
#include "Movie.h"
#include "Series.h"

using namespace std;

class Database {
    private:
        static bool process_csv_line(const string& line, shared_ptr<Title>& m); 
        static bool process_number(const string& temp, unsigned short& value);
    public:
        static bool import(const string& filename, vector<shared_ptr<Title>>& db);
        static bool import(istream& is, vector<shared_ptr<Title>>& db);
};

void db_query_1(const vector<shared_ptr<Title>>& db);

void db_query_2(const vector<shared_ptr<Title>>& db);

void db_query_3(const vector<shared_ptr<Title>>& db, unsigned short seasons, unsigned short episodes);

void db_query_4(const vector<shared_ptr<Title>>& db, const type_info& type, unsigned short begin, unsigned short end);

#endif