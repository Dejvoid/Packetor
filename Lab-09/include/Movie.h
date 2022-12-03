#ifndef MOVIE_H_
#define MOVIE_H_

#include "Title.h"

class Movie : public Title{
    private: 
        unsigned short length_;
    public: 
        Movie() = default;
        Movie(const string & name, unsigned short year, const string & genre, unsigned short ranking, const set<Actor> & actors, unsigned short length);
        Movie(string && name, unsigned short year, string && genre, unsigned short ranking, set<Actor> && actors, unsigned short length);
        Type type() const override;
        void print_json(ostream& os = cout) const override;
};

#endif