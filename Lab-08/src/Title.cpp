#include "Title.h"

using namespace std;

Title::Title(const string &name, unsigned short year, const string &genre, unsigned short rating, const set<Actor> &actors) 
    : name_(name), year_(year), genre_(genre), rating_(rating), actors_(actors) {}

Title::Title(string &&name, unsigned short year, string &&genre, unsigned short rating, set<Actor> &&actors) 
    : name_(name), year_(year), genre_(genre), rating_(rating), actors_(actors) {}

void Title::print_json_body(ostream &os) const
{
    os << "name: \"" << name_ << "\", ";
    os << "year: " << year_ << ", ";
    os << "genre: \"" << genre_ << "\", ";
    os << "rating: " << rating_;
    if (actors_.size() > 0){
        os << ", actors: [ ";
        for (auto it = actors_.begin(); it != actors_.end(); ++it){
            os /*<< "\""*/ << *it /*<< "\""*/;
            auto it2 = it;
            if (++it2 != actors_.end())
                os << ",";
            os << " ";
        }
        os << "]";
    }
}
