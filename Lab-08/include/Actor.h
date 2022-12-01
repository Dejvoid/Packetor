#ifndef ACTOR_H_
#define ACTOR_H_

#include <string>
#include <iostream>

class Actor
{
private:
    std::string first_name_;
    std::string last_name_;
    unsigned short birth_year_;
public:
    inline const std::string& first_name() const { return first_name_; };
    inline const std::string& last_name() const { return last_name_; };
    inline const unsigned short birth_year() const { return birth_year_; };
    void print_json(std::ostream& os = std::cout) const;
    Actor() = default;
    Actor(const std::string& first_name, const std::string& last_name, unsigned short birth_year);
    Actor(std::string&& first_name, std::string&& last_name, unsigned short birth_year);
    ~Actor();
    friend std::istream& operator>>(std::istream& is, Actor& actor);
};


bool operator<(const Actor& actor1, const Actor& actor2);

bool operator==(const Actor& a1, const Actor& a2);

std::ostream& operator<<(std::ostream& os, const Actor& actor);

std::istream& operator>>(std::istream& is, Actor& actor);

#endif