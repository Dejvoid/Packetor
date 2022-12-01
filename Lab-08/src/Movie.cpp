#include "Movie.h"

Movie::Movie(const string & name, unsigned short year, const string & genre, unsigned short ranking, const set<Actor> & actors, unsigned short length)
    : Title(name, year, genre, ranking, actors), length_(length){};

Movie::Movie(string && name, unsigned short year, string && genre, unsigned short ranking, set<Actor> && actors, unsigned short length)
    : Title(name, year, genre, ranking, actors), length_(length) {};

Type Movie::type() const {
    return Type::MOVIE;
}

void Movie::print_json(ostream& os) const{
    os << "{ ";
    os << "type: \"MOVIE\", ";
    print_json_body(os);
    os << ", length: " << length_;
    os << " }" << std::endl;
};

std::ostream& operator<<(std::ostream& os, const Movie& movie){
    movie.print_json(os);
    return os;
}