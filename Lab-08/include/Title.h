#ifndef TITLE_H_
#define TITLE_H_

#include <string>
#include <set>
#include <iostream>
#include "Actor.h"

using namespace std;

enum class Type 
{
    MOVIE, SERIES
};

class Title {
    private:
        string name_;
        unsigned short year_;
        string genre_;
        unsigned short rating_;
        set<Actor> actors_;
    protected:
        virtual void print_json_body(ostream& os = std::cout) const;
    public: 
        const string & name() const;
        const unsigned short year() const;
        const string & genre() const;
        const unsigned short rating() const;
        const set<Actor> & actors() const;
        Title() = default;
        Title(const string & name, unsigned short year, const string & genre, unsigned short ranking, const set<Actor> & actors);
        Title(string && name, unsigned short year, string && genre, unsigned short ranking, set<Actor> && actors);
        virtual ~Title() = default;
        virtual void print_json(ostream & os = std::cout) const = 0;
        virtual Type type() const = 0;
};

inline const string & Title::name() const {
    return name_;
}
inline const unsigned short Title::year() const {
    return year_;
}
inline const string & Title::genre() const {
    return genre_;
}
inline const unsigned short Title::rating() const {
    return rating_;
}
inline const set<Actor> & Title::actors() const {
    return actors_;
}

#endif