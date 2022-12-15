#include <iostream>
#include "Database.h"
#include "Movie.h"
#include "Actor.h"

int main(int argc, char **argv)
{
    std::vector<shared_ptr<Title>> db;
    if (Database::import("example.txt", db))
        std::cout << "SUccess load" << std::endl;
    //std::cout << db.size();
    //std::cout << "Q1" << std::endl;
    //db_query_1(db);
    //// std::cout << "after query1" << std::endl;
    //std::cout << "Q2" << std::endl;
    //db_query_2(db);
    //std::cout << "Q3" << std::endl;
    //db_query_3(db, 1, 0);
    //std::cout << "Q4" << std::endl;
    //db_query_4(db, typeid(Movie), 2000, 2020);

    // --------------------

    map<string, shared_ptr<Title>> index1;
    multimap<unsigned short, shared_ptr<Title>> index2;
    unordered_multimap<Actor, shared_ptr<Title>> index3;
    db_index_titles(db, index1);
    db_index_years(db, index2);
    db_index_actors(db, index3);

    std::cout << "Q5" << std::endl;
    db_query_5(index1, "Vlastnici");

    std::cout << "Q6: " << std::endl;
    db_query_6(index2, 2019);
   
     std::cout << "Q7: " << std::endl;
    db_query_7(index2, 2009, 2019);

     std::cout << "Q8: " << std::endl;
    auto actor = *((*db.begin())->actors().begin());
    db_query_8(index3, actor);

     std::cout << "Q9: " << std::endl;
    vector<shared_ptr<Title>> result;
    db_query_9(db, result, actor);
    for (auto &&tit : result) {
        tit->print_json();
    }

    vector<shared_ptr<Title>> result2;
     std::cout << "Q10: " << std::endl;
    db_query_10(db, result2, "comedy");
    int af = result2.size();
    for (auto it = result2.begin(); it != result2.end(); ++it){
        (*it)->print_json();
    }

    int counter = 0;
     std::cout << "Q11: " << std::endl;
    db_query_11(db, Type::MOVIE, "comedy", counter);
    std::cout << "Movies and comedies (Q11): " << counter << endl;

     std::cout << "Q12: " << std::endl;
    db_query_12(db, "comedy", counter);
    std::cout << "comedies (Q12): " << counter << endl;
}