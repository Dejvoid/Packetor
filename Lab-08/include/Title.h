#ifndef TITLE_H_
#define TITLE_H_

#include <string>
#include <set>
#include <iostream>

using namespace std;

class Title {
    private:
        string name_;
        unsigned short year_;
        string genre_;
        unsigned short rating_;
        set<string> actors_;
    public: 
        const string & name() const;
        const unsigned short year() const;
        const string & genre() const;
        const unsigned short rating() const;
        const set<string> & actors() const;
        Title() = default;
        Title(const string & name, unsigned short year, const string & genre, unsigned short ranking, const set<string> & actors);
        Title(string && name, unsigned short year, string && genre, unsigned short ranking, set<string> && actors);
        void print_json(ostream & os = std::cout) const;
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
inline const set<string> & Title::actors() const {
    return actors_;
}

#endif