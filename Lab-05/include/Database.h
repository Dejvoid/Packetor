#ifndef DATABASE_H_
#define DATABASE_H_
#include "Movie.h"
#include <vector>

class Database {
    private:
        static bool process_csv_line(const std::string& line, Movie& m); 
    public:
        static bool import(const std::string& filename, std::vector<Movie>& db);
        static bool import(std::istream& is, std::vector<Movie>& db);
};

void db_query_1(const std::vector<Movie>& db);

void db_query_2(const std::vector<Movie>& db);

#endif