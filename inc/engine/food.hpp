#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <string>
#include <list>

#include <common.hpp>
#include <item.hpp>
#include <dish.hpp>

class Dish;

class Food : public Item {
    private:
        std::list<Dish *> dishesWithFood {};

    public:
        Food(std::string name, uint64_t mass, uint64_t price, MeasureType measureType, uint64_t fats, uint64_t proteins, uint64_t carbohydrates, uint64_t calories);
        ~Food(void);

        Food& operator=(const Food& right);

        void registerDish(Dish* dish);
        void unregisterDish(Dish* dish);
};

std::ostream& operator<<(std::ostream& out, const Food& food);

#endif // FOOD_H
