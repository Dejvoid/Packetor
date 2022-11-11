#include <vector>
#include "Movie.h"
#include "Database.h"

int main(int argc, char **argv){
    /*
    std::set<std::string> a1;
    a1.insert("Pepa");
    std::set<std::string> a2 = {"Pepa", "Honza", "Franta"};
    std::vector<Movie> db; 
    std::string n1 = "Film1";
    std::string g1 = "genre";

    Movie m1 = Movie(n1, 1999, g1, 90, std::set<std::string> {"Pepa", "Honza", "Franta"});

    db.push_back(std::move(m1));
    db.push_back(Movie("Film2", 2005, "genre2", 86, std::set<std::string>()));
    db.push_back(Movie(std::move(n1), 2006, std::move(g1), 11, std::move(a2)));
    db.emplace_back("Film3", 1829, "genre3", 70,std::set<std::string>{"herec1", "herec2"}); // vlozi se novy prvek nakonec, rovnou se vola konstruktor
    for (auto &&i : db){
        i.print_json();
    }
    return 0; // istringstream, getline
    */
   std::vector<Movie> db;
   Database::import("example.txt", db);
   db_query_1(db);
   std::cout<< std::endl;
   db_query_2(db);
   
}