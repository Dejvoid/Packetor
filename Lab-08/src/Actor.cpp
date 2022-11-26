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

std::istream& operator>>(std::istream& is, Actor& actor){
    is >> actor.first_name_ >> actor.last_name_ >> actor.birth_year_;
    return is;
}

void Actor::print_json(std::ostream& os) const {
    os << "{ name: \"" << actor.first_name() << "\", surname: \"" << actor.last_name() << "\", year: " << actor.birth_year() << " }";
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