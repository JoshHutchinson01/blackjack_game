#ifndef CARD_H
#define CARD_H

#include <string>

struct Card {

    std::string value;
    std::string suit;
    int bj_points;
    
    inline std::string get_name() const {
        std::string name = value;
        name += suit;
        return name;
    }

};

#endif