#ifndef FOOD_H
#define FOOD_H

#include <common.hpp>
#include <dish.hpp>
#include <item.hpp>

#include <iostream>
#include <list>
#include <string>

class Dish;

class Food : public Item {
    private:
        std::list<Dish*> dishesWithFood {};
        std::list<std::list<Food*>*> listOfFoodLists {};
        bool unregister {true};

    public:
        Food(std::string name, uint64_t mass, uint64_t price, MeasureType measureType, uint64_t fats, uint64_t proteins, uint64_t carbohydrates, uint64_t calories);
        Food(std::string name, uint64_t mass, uint64_t price, MeasureType measureType, uint64_t fats, uint64_t proteins, uint64_t carbohydrates, uint64_t calories, std::list<Item*>* itemList);
        Food(std::string name, uint64_t mass, uint64_t price, MeasureType measureType, uint64_t fats, uint64_t proteins, uint64_t carbohydrates, uint64_t calories, std::list<Food*>* foodList);
        ~Food(void);

        Food& operator=(const Food& right);

        void addFoodList(std::list<Food*>* itemList);

        void registerDish(Dish* dish);
        void unregisterDish(Dish* dish);
};

std::ostream& operator<<(std::ostream& out, const Food& food);

#endif // FOOD_H
