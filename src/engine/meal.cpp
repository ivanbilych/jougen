#include <meal.hpp>
#include <engineLimits.hpp>
#include <debug.hpp>
#include <errors.hpp>

const std::string Meal::mealTypeNames[] = {
    "breakfast",
    "lunch",
    "dinner",
    "on day"
};

Meal::Meal(MealType mealType, const Dish& dish) :
        PeopleStats<Dish>(mealTypeNames[static_cast<uint32_t>(mealType)], MEAL_MIN_MASS, MEAL_MAX_MASS, MEAL_MIN_PRICE, MEAL_MAX_PRICE, MEAL_MIN_FATS, MEAL_MAX_FATS, MEAL_MIN_PROTEINS, MEAL_MAX_PROTEINS, MEAL_MIN_CARBOHYDRATES, MEAL_MAX_CARBOHYDRATES, MEAL_MIN_CALORIES, MEAL_MAX_CALORIES, MEAL_MIN_AMOUNT_OF_DISH, MEAL_MAX_AMOUNT_OF_DISH, MEAL_MIN_AMOUNT_OF_PEOPLE, MEAL_MAX_AMOUNT_OF_PEOPLE),
        mealType(mealType) {
    setAmountOfPeople(dish.getAmountOfPeople());

    addItem(dish);

    PRINT_OBJ("Meal " << NAME_ID << " created for " << getAmountOfPeople() << " people");
}

Meal::~Meal(void) {
    PRINT_OBJ("Meal " << NAME_ID << " destroyed");
}

Meal& Meal::operator=(const Meal& right) {
    if ( this == &right ) {
        return *this;
    }

    PeopleStats::operator=(right);

    this->mealType = right.getMealType();

    return *this;
}

Meal::MealType Meal::getMealType(void) const {
    return mealType;
}

std::ostream& operator<<(std::ostream& out, const Meal& meal) {
#ifdef DEBUG
    std::list<Dish> dishes = meal.getList();

    out << dynamic_cast<const PeopleStats<Dish>&>(meal) << std::endl;
    out << "        - meal type: " << meal.getName() << std::endl;
    out << "        DISHES (" << dishes.size() << "):" << std::endl;
    out << "        >>> >>> >>>" << std::endl;

    for ( auto& entry: dishes ) {
        out << "        dish " << entry << std::endl;
    }
    out << "        <<< <<< <<<";
#else
    out << meal.getName();
#endif

    return out;
}
