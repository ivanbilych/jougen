#ifndef DISH_H
#define DISH_H

#include <iostream>
#include <string>
#include <map>

#include <common.hpp>
#include <peopleStats.hpp>
#include <food.hpp>

#define HUNDRED_GRAM 100

class Dish : public Stats {
    private:
        uint64_t amountOfPeople;
        std::map<Food*, uint64_t, Stats::Compare> ingridients;

        void setAmountOfPeople(uint64_t amountOfPeople);

    public:
        const uint64_t minListItemsAmount {DISH_MIN_AMOUNT_OF_FOOD};
        const uint64_t maxListItemsAmount {DISH_MAX_AMOUNT_OF_FOOD};
        const uint64_t minAmountOfPeople {DISH_MIN_AMOUNT_OF_PEOPLE};
        const uint64_t maxAmountOfPeople {DISH_MAX_AMOUNT_OF_PEOPLE};

        Dish(std::string name, Food* food, uint64_t foodMass, uint64_t amountOfPeople = 1);
        ~Dish(void);

        Dish& operator=(const Dish& right);

        void addFood(Food* const food, uint64_t foodMass);
        void removeFood(Food* const food);
        void changeFoodAmount(Food* const food, uint64_t foodMass);
        void changeAmountOfPeople(uint64_t amountOfPeople);
        uint64_t getAmountOfPeople(void) const;
        const std::map<Food*, uint64_t, Stats::Compare>& getIngridientMap(void) const;
};

std::ostream& operator<<(std::ostream& out, const Dish& dish);

#endif // DISH_H
