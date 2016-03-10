#ifndef MEAL_H
#define MEAL_H

#include <iostream>

#include <common.hpp>
#include <peopleStats.hpp>
#include <dish.hpp>

class Meal : public PeopleStats<Dish> {
    public:
        enum MealType {
            BREAKFAST,
            LUNCH,
            DINNER,
            ONDAY
        };

    private:
        static const std::string mealTypeNames[];
        MealType mealType;

    public:
        Meal(MealType mealType, const Dish& dish);
        ~Meal(void);
        Meal& operator=(const Meal& right);
        MealType getMealType(void) const;
};

std::ostream& operator<<(std::ostream& out, const Meal& meal);

#endif // MEAL_H
