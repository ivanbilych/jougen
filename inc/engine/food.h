#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <string>

#include <common.h>
#include <item.h>

class Food : public Item {
    public:
        Food(std::string name, uint64_t mass, uint64_t price, MeasureType measureType, uint64_t fats, uint64_t proteins, uint64_t carbohydrates, uint64_t calories);
        ~Food(void);
        Food& operator=(const Food& right);
};

std::ostream& operator<<(std::ostream& out, const Food& food);

#endif // FOOD_H
