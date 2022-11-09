#include "Movie.hpp"

using namespace std;

Movie::Movie(const string &name, unsigned short year, const string &genre, unsigned short ranking, const set<string> &actors) 
    : name_(name), year_(year), genre_(genre), ranking_(ranking), actors_(actors) {}

Movie::Movie(string &&name, unsigned short year, string &&genre, unsigned short ranking, set<string> &&actors) 
    : name_(name), year_(year), genre_(genre), ranking_(ranking), actors_(actors) {}

void Movie::print_json(ostream &os) const
{
    os << "{ ";
    os << "name: \"" << name_ << "\", ";
    os << "year: " << year_ << ", ";
    os << "genre: \"" << genre_ << "\", ";
    os << "rating: " << ranking_;
    if (actors_.size() > 0){
        os << ", actors: [ ";
        for (auto it = actors_.begin(); it != actors_.end(); ++it){
            os << "\"" << *it << "\"";
            auto it2 = it;
            if (++it2 != actors_.end())
                os << ",";
            os << " ";
        }
        os << "]";
    }
    os << " }" << std::endl;
}
