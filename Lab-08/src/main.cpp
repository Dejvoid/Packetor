#include <iostream>
#include "Database.h"
#include "Movie.h"
#include "Actor.h"



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
   db_query_4(db,typeid(Title), 2000, 2020);
  //  map<string, shared_ptr<Title>> mDb; 
  //  db_index_titles(db, mDb);
  //  std::cout << "Q5" <<std::endl;
  // db_query_5(mDb, "Vlastnici");
  // multimap<unsigned short, shared_ptr<Title>> index2;
  // db_index_years(db, index2);
  //  // unordered_multimap<Actor, shared_ptr<Title>> 
}