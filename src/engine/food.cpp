#include <food.hpp>
#include <engineLimits.hpp>
#include <debug.hpp>
#include <errors.hpp>

Food::Food(std::string name, uint64_t mass, uint64_t price, Item::MeasureType measureType, uint64_t fats, uint64_t proteins, uint64_t carbohydrates, uint64_t calories) :
    Item {name, mass, price, measureType, FOOD_MIN_MASS, FOOD_MAX_MASS,
          FOOD_MIN_PRICE, FOOD_MAX_PRICE, FOOD_MIN_FATS, FOOD_MAX_FATS,
          FOOD_MIN_PROTEINS, FOOD_MAX_PROTEINS, FOOD_MIN_CARBOHYDRATES,
          FOOD_MAX_CARBOHYDRATES, FOOD_MIN_CALORIES, FOOD_MAX_CALORIES} {

    setFats(fats);
    setProteins(proteins);
    setCarbohydrates(carbohydrates);
    setCalories(calories);

    PRINT_OBJ("Created food class " << NAME_ID);
}

Food::~Food(void) {
    PRINT_OBJ("Destroyed food class " << NAME_ID);
}

Food& Food::operator=(const Food& right) {
    if ( this == &right ) {
        return *this;
    }

    Food::Item::operator=(right);

    return *this;
}

std::ostream& operator<<(std::ostream& out, const Food& food) {
#ifdef DEBUG
    out << dynamic_cast<const Item&>(food);
#else
    out << dynamic_cast<const Item&>(food);
#endif

    return out;
}
