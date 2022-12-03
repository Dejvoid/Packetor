#include "Actor.h"

bool operator<(const Actor& actor1, const Actor& actor2){
    return actor1.last_name() < actor2.last_name() || 
    ((actor1.last_name() == actor2.last_name()) && (actor1.first_name() < actor2.first_name())) || 
    ((actor1.first_name() == actor2.first_name()) && (actor1.birth_year() < actor2.birth_year()));
}

std::ostream& operator<<(std::ostream& os, const Actor& actor){
    actor.print_json(os);
    return os;
}

bool operator==(const Actor& a1, const Actor& a2){
    return a1.last_name() == a2.last_name() && a1.first_name() == a2.first_name() && a1.birth_year() == a2.birth_year();
}

std::istream& operator>>(std::istream& is, Actor& actor){
    std::string temp;
    is >> actor.first_name_ >> actor.last_name_ >> temp;
    size_t p;
    try{
     actor.birth_year_ = (unsigned short)std::stoi(temp, &p);
    } catch (...) {std::cout << "Some Error" << std::endl;};
    return is;
}

void Actor::print_json(std::ostream& os) const {
    os << "{ name: \"" << first_name() << "\", surname: \"" << last_name() << "\", year: " << birth_year() << " }";
}

Actor::Actor(const std::string& first_name, const std::string& last_name, unsigned short birth_year){
    first_name_ = first_name;
    last_name_ = last_name;
    birth_year_= birth_year;
}

Actor::Actor(std::string&& first_name, std::string&& last_name, unsigned short birth_year){
    first_name_ = first_name;
    last_name_ = last_name;
    birth_year_ = birth_year;
}

Actor::~Actor(){};