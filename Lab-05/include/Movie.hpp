#ifndef MOVIE_H

#define MOVIE_H

#include <string>
#include <set>
#include <iostream>

using namespace std;

class Movie {
    private:
        string name_;
        unsigned short year_;
        string genre_;
        unsigned short ranking_;
        set<string> actors_;
    public: 
        const string & name() const;
        const unsigned short year() const;
        const string & genre() const;
        const unsigned short rating() const;
        const set<string> & actors() const;
        Movie(const string & name, unsigned short year, const string & genre, unsigned short ranking, const set<string> & actors);
        Movie(string && name, unsigned short year, string && genre, unsigned short ranking, set<string> && actors);
        void print_json(ostream & os = std::cout) const;
};

inline const string & Movie::name() const{
    return name_;
}

#endif