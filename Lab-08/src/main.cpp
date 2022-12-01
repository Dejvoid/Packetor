#include <iostream>
#include "Database.h"
#include "Movie.h"

int main(int argc, char **argv){
    std::vector<shared_ptr<Title>> db;
   if (Database::import("example.txt", db))
    std::cout << "SUccess load" << std::endl;
    std::cout << db.size();
    std::cout << "Q1" <<std::endl;
   db_query_1(db);
   //std::cout << "after query1" << std::endl;
   std::cout << "Q2" <<std::endl;
   db_query_2(db);
   std::cout << "Q3" <<std::endl;
   db_query_3(db, 1, 0);
   std::cout << "Q4" <<std::endl;
   db_query_4(db,typeid(Movie), 2000, 2020);
}