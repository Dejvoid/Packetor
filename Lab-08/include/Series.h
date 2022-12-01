#ifndef SERIES_H_
#define SERIES_H_

#include "Title.h"

class Series : public Title{
    private:
        unsigned short seasons_;
        unsigned short episodes_;
    public: 
        Series() = default;
        Series(const string & name, unsigned short year, const string & genre, unsigned short ranking, const set<Actor> & actors, unsigned short seasons, unsigned short episodes);
        Series(string && name, unsigned short year, string && genre, unsigned short ranking, set<Actor> && actors, unsigned short seasons, unsigned short episodes);
        Type type() const override;
        void print_json(ostream& os = cout) const override;
        inline unsigned short seasons() const { return seasons_; };
        inline unsigned short episodes() const { return episodes_; };
};

#endif