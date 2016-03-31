#include <debug.hpp>
#include <engineLimits.hpp>
#include <errors.hpp>
#include <food.hpp>

#include <algorithm>

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

Food::Food(std::string name, uint64_t mass, uint64_t price, Item::MeasureType measureType, uint64_t fats, uint64_t proteins, uint64_t carbohydrates, uint64_t calories, std::list<Item*>* itemList) :
    Item {name, mass, price, measureType, FOOD_MIN_MASS, FOOD_MAX_MASS,
          FOOD_MIN_PRICE, FOOD_MAX_PRICE, FOOD_MIN_FATS, FOOD_MAX_FATS,
          FOOD_MIN_PROTEINS, FOOD_MAX_PROTEINS, FOOD_MIN_CARBOHYDRATES,
          FOOD_MAX_CARBOHYDRATES, FOOD_MIN_CALORIES, FOOD_MAX_CALORIES,
          itemList} {

    setFats(fats);
    setProteins(proteins);
    setCarbohydrates(carbohydrates);
    setCalories(calories);

    PRINT_OBJ("Created food class " << NAME_ID);
}

Food::Food(std::string name, uint64_t mass, uint64_t price, Item::MeasureType measureType, uint64_t fats, uint64_t proteins, uint64_t carbohydrates, uint64_t calories, std::list<Food*>* foodList) :
    Item {name, mass, price, measureType, FOOD_MIN_MASS, FOOD_MAX_MASS,
          FOOD_MIN_PRICE, FOOD_MAX_PRICE, FOOD_MIN_FATS, FOOD_MAX_FATS,
          FOOD_MIN_PROTEINS, FOOD_MAX_PROTEINS, FOOD_MIN_CARBOHYDRATES,
          FOOD_MAX_CARBOHYDRATES, FOOD_MIN_CALORIES, FOOD_MAX_CALORIES} {

    setFats(fats);
    setProteins(proteins);
    setCarbohydrates(carbohydrates);
    setCalories(calories);

    addFoodList(foodList);

    PRINT_OBJ("Created food class " << NAME_ID);
}

Food::~Food(void) {
    for ( auto& dish: dishesWithFood ) {
        try {
            unregister = false;
            dish->removeFood(this);
            unregister = true;
        } catch (LastFoodInMap e) {
            delete dish;
        }
    }

    for ( auto& entry : listOfFoodLists ) {
        std::list<Food*>::iterator it = std::find(entry->begin(), entry->end(), this);

        PRINT_DEBUG("Removing food " << NAME_ID << " from list");

        if ( it != entry->end() ) {
            entry->erase(it);
        }
    }

    PRINT_OBJ("Destroyed food class " << NAME_ID);
}

Food& Food::operator=(const Food& right) {
    if ( this == &right ) {
        return *this;
    }

    Food::Item::operator=(right);

    return *this;
}

void Food::addFoodList(std::list<Food*>* foodList) {
    if ( foodList != nullptr ) {
        std::list<std::list<Food*>* >::iterator it = std::find(listOfFoodLists.begin(), listOfFoodLists.end(), foodList);

        if ( it == listOfFoodLists.end() ) {
            listOfFoodLists.push_back(foodList);

            PRINT_DEBUG("Register food list in food " << NAME_ID);
        }
    }
}

void Food::registerDish(Dish* dish) {
    std::list<Dish*>::iterator it = std::find(dishesWithFood.begin(), dishesWithFood.end(), dish);

    if ( it == dishesWithFood.end() ) {
        dishesWithFood.push_back(dish);

        PRINT_DEBUG("Register dish " << NAME_ID_CLASS(*dish) << " in " << *this << " food");
    }
}

void Food::unregisterDish(Dish* dish) {
    std::list<Dish*>::iterator it;

    if ( !unregister ) {
        return;
    }

    if ( (it = std::find(dishesWithFood.begin(), dishesWithFood.end(), dish)) != dishesWithFood.end() ) {
        dishesWithFood.erase(it);
    } else {
        PRINT_ERR("Could not unregister dish " << NAME_ID_CLASS(*dish) << " from " << *this << " food");

        throw WrongDishForUnregister();
    }
}

std::ostream& operator<<(std::ostream& out, const Food& food) {
#ifdef DEBUG
    out << dynamic_cast<const Item&>(food);
#else
    out << dynamic_cast<const Item&>(food);
#endif

    return out;
}
