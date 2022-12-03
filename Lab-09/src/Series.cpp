#include "Series.h"

Series::Series(const string & name, unsigned short year, const string & genre, unsigned short ranking, const set<Actor> & actors, unsigned short seasons, unsigned short episodes)
    : Title(name, year, genre, ranking, actors), seasons_(seasons), episodes_(episodes) {};

Series::Series(string && name, unsigned short year, string && genre, unsigned short ranking, set<Actor> && actors, unsigned short seasons, unsigned short episodes)
    : Title(name, year, genre, ranking, actors), seasons_(seasons), episodes_(episodes) {};

Type Series::type() const {
    return Type::SERIES;
}

void Series::print_json(ostream& os) const{
    os << "{ ";
    os << "type: \"SERIES\", ";
    print_json_body(os);
    os << ", seasons: " << seasons_;
    os << ", episodes: " << episodes_;
    os << " }" << std::endl;
};

std::ostream& operator<<(std::ostream& os, const Series& series){
    series.print_json(os);
    return os;
}