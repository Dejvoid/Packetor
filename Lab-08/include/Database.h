#ifndef DATABASE_H_
#define DATABASE_H_
#include "Title.h"
#include <vector>
#include <memory>

class Database {
    private:
        static bool process_csv_line(const std::string& line, Title& m); 
    public:
        static bool import(const std::string& filename, std::vector<Title>& db);
        static bool import(std::istream& is, std::vector<Title>& db);
};

void db_query_1(const std::vector<Title>& db);

void db_query_2(const std::vector<Title>& db);

#endif