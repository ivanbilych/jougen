#include <cmath>

#include <dish.hpp>
#include <item.hpp>
#include <engineLimits.hpp>
#include <debug.hpp>
#include <errors.hpp>

Dish::Dish(std::string name, Food* food, uint64_t foodMass, uint64_t amountOfPeople) :
    Stats {name, DISH_MIN_MASS, DISH_MAX_MASS, DISH_MIN_PRICE, DISH_MAX_PRICE,
           DISH_MIN_FATS, DISH_MAX_FATS, DISH_MIN_PROTEINS, DISH_MAX_PROTEINS,
           DISH_MIN_CARBOHYDRATES, DISH_MAX_CARBOHYDRATES, DISH_MIN_CALORIES,
           DISH_MAX_CALORIES} {

    setMass(foodMass);
    setPrice(std::round(food->getPrice()/food->getMass()*foodMass));
    setFats(std::round(food->getFats()*foodMass/HUNDRED_GRAM));
    setProteins(std::round(food->getProteins()*foodMass/HUNDRED_GRAM));
    setCarbohydrates(std::round(food->getCarbohydrates()*foodMass/HUNDRED_GRAM));
    setCalories(std::round(food->getCalories()*foodMass/HUNDRED_GRAM));
    setAmountOfPeople(amountOfPeople);

    ingridients.insert(std::pair<Food*, uint64_t>(food, foodMass));
    food->registerDish(this);

    PRINT_OBJ("Created dish class " << NAME_ID);
}

Dish::~Dish(void) {
    PRINT_OBJ("Destroyed dish basic class " << NAME_ID);
}

Dish& Dish::operator=(const Dish& right) {
    if ( this == &right ) {
        return *this;
    }

    Dish::Stats::operator=(right);

    ingridients.clear();

    for ( auto& entry: right.getIngridientMap() ) {
        addFood(entry.first, entry.second);
    }

    return *this;
}

void Dish::addFood(Food* const food, uint64_t foodMass) {
    uint64_t newMass, newPrice, newFats, newProteins, newCarbohydrates, newCalories;

    if ( foodMass < minMass || foodMass > maxMass ) {
        PRINT_ERR("Wrong food " << NAME_ID_CLASS(*food) << " mass value provided [" << foodMass << "]");

        throw WrongDishMass();
    }

    if ( ingridients.count(food) ) {
        PRINT_ERR("Could not add " << NAME_ID_CLASS(*food) << " food that is already in the dish");

        throw AlreadySuchFoodInList();
    }

    if ( ingridients.size() >= maxListItemsAmount ) {
        PRINT_ERR("Could not add new food " << NAME_ID_CLASS(*food) << " to the dish");

        throw TooMuchFoodInMap();
    }

    newMass = getMass() + foodMass;
    newPrice = getPrice() + std::round(food->getPrice()*foodMass/food->getMass());
    newFats = getFats() + std::round(food->getFats()*foodMass/HUNDRED_GRAM);
    newProteins = getProteins() + std::round(food->getProteins()*foodMass/HUNDRED_GRAM);
    newCarbohydrates = getCarbohydrates() + std::round(food->getCarbohydrates()*foodMass/HUNDRED_GRAM);
    newCalories = getCalories() + std::round(food->getCalories()*foodMass/HUNDRED_GRAM);

    if ( newMass > maxMass ) {
        PRINT_ERR("Could not add new food " << NAME_ID_CLASS(*food) << " to the dish. Result mass is too big [" << newMass << "]");

        throw TooBigDishMass();
    }

    if ( newPrice > maxPrice ) {
        PRINT_ERR("Could not add new food " << NAME_ID_CLASS(*food) << " to the dish. Result price is too big [" << newPrice << "]");

        throw TooBigDishPrice();
    }

    if ( newFats > maxFats ) {
        PRINT_ERR("Could not add new food " << NAME_ID_CLASS(*food) << " to the dish. Result fats are too big [" << newFats << "]");

        throw TooBigDishFats();
    }

    if ( newProteins > maxProteins ) {
        PRINT_ERR("Could not add new food " << NAME_ID_CLASS(*food) << " to the dish. Result proteins are too big [" << newProteins << "]");

        throw TooBigDishProteins();
    }

    if ( newCarbohydrates > maxCarbohydrates ) {
        PRINT_ERR("Could not add new food " << NAME_ID_CLASS(*food) << " to the dish. Result carbohydrates are too big [" << newCarbohydrates << "]");

        throw TooBigDishCarbohydrates();
    }

    if ( newCalories > maxCalories ) {
        PRINT_ERR("Could not add new food " << NAME_ID_CLASS(*food) << " to the dish. Result calories are too big [" << newCalories << "]");

        throw TooBigDishCalories();
    }

    setMass(newMass);
    setPrice(newPrice);
    setFats(newFats);
    setProteins(newProteins);
    setCarbohydrates(newCarbohydrates);
    setCalories(newCalories);

    ingridients.insert(std::pair<Food *, uint64_t>(food, foodMass));
    food->registerDish(this);

    PRINT_INFO("Food " << NAME_ID_CLASS(*food) << " was added to dish " << NAME_ID << "");
}

void Dish::removeFood(Food* const food) {
    uint64_t newMass, newPrice, newFats, newProteins, newCarbohydrates, newCalories;
    uint64_t foodMass = ingridients[food];

    if ( !ingridients.count(food) ) {
        PRINT_ERR("Could not remove food " << NAME_ID_CLASS(*food) << " that is not in the dish");

        throw NoSuchFoodInMap();
    }

    if ( ingridients.size() <= minListItemsAmount) {
        PRINT_ERR("Could not remove last " << NAME_ID_CLASS(*food) << " food in the dish");

        throw LastFoodInMap();
    }

    newMass = getMass() - foodMass;
    newPrice = getPrice() - std::round(food->getPrice()*foodMass/food->getMass());
    newFats = getFats() - std::round(food->getFats()*foodMass/HUNDRED_GRAM);
    newProteins = getProteins() - std::round(food->getProteins()*foodMass/HUNDRED_GRAM);
    newCarbohydrates = getCarbohydrates() - std::round(food->getCarbohydrates()*foodMass/HUNDRED_GRAM);
    newCalories = getCalories() - std::round(food->getCalories()*foodMass/HUNDRED_GRAM);

    setMass(newMass);
    setPrice(newPrice);
    setFats(newFats);
    setProteins(newProteins);
    setCarbohydrates(newCarbohydrates);
    setCalories(newCalories);

    ingridients.erase(food);
    food->unregisterDish(this);

    PRINT_INFO("Food " << NAME_ID_CLASS(*food) << " was removed from dish " << NAME_ID << "");
}

void Dish::changeFoodAmount(Food* const food, uint64_t foodMass) {
    uint64_t newMass, newPrice, newFats, newProteins, newCarbohydrates, newCalories;
    int64_t currentFoodMass = ingridients[food];

    if ( foodMass < minMass || foodMass > maxMass ) {
        PRINT_ERR("Wrong food " << NAME_ID_CLASS(*food) << " mass value provided [" << foodMass << "]");

        throw WrongDishMass();
    }

    if ( !ingridients.count(food) ) {
        PRINT_ERR("Could not change " << NAME_ID_CLASS(*food) << " food that is not in the dish");

        throw NoSuchFoodInMap();
    }

    newMass = getMass() + foodMass * amountOfPeople - currentFoodMass * amountOfPeople;
    newPrice = getPrice() + std::round(food->getPrice()*foodMass/food->getMass()) -
               std::round(food->getPrice()*currentFoodMass/food->getMass());
    newFats = getFats() + std::round(food->getFats()*foodMass/HUNDRED_GRAM*amountOfPeople) -
              std::round(food->getFats()*currentFoodMass/HUNDRED_GRAM*amountOfPeople);
    newProteins = getProteins() + std::round(food->getProteins()*foodMass/HUNDRED_GRAM*amountOfPeople) -
                  std::round(food->getProteins()*currentFoodMass/HUNDRED_GRAM*amountOfPeople);
    newCarbohydrates = getCarbohydrates() + std::round(food->getCarbohydrates()*foodMass/HUNDRED_GRAM*amountOfPeople) -
                       std::round(food->getCarbohydrates()*currentFoodMass/HUNDRED_GRAM*amountOfPeople);
    newCalories = getCalories() + std::round(food->getCalories()*foodMass/HUNDRED_GRAM*amountOfPeople) -
                  std::round(food->getCalories()*currentFoodMass/HUNDRED_GRAM*amountOfPeople);

    if ( newMass > maxMass ) {
        PRINT_ERR("Could not change food " << NAME_ID_CLASS(*food) << ". Result mass is too big [" << newMass << "]");

        throw TooBigDishMass();
    }

    if ( newPrice > maxPrice ) {
        PRINT_ERR("Could not change food " << NAME_ID_CLASS(*food) << ". Result price is too big [" << newPrice << "]");

        throw TooBigDishPrice();
    }

    if ( newFats > maxFats ) {
        PRINT_ERR("Could not change food " << NAME_ID_CLASS(*food) << ". Result fats are too big [" << newFats << "]");

        throw TooBigDishFats();
    }

    if ( newProteins > maxProteins ) {
        PRINT_ERR("Could not change food " << NAME_ID_CLASS(*food) << ". Result proteins are too big [" << newProteins << "]");

        throw TooBigDishProteins();
    }

    if ( newCarbohydrates > maxCarbohydrates ) {
        PRINT_ERR("Could not change food " << NAME_ID_CLASS(*food) << ". Result carbohydrates are too big [" << newCarbohydrates << "]");

        throw TooBigDishCarbohydrates();
    }

    if ( newCalories > maxCalories ) {
        PRINT_ERR("Could not change food " << NAME_ID_CLASS(*food) << ". Result calories are too big [" << newCalories << "]");

        throw TooBigDishCalories();
    }

    setMass(newMass);
    setPrice(newPrice);
    setFats(newFats);
    setProteins(newProteins);
    setCarbohydrates(newCarbohydrates);
    setCalories(newCalories);

    ingridients[food] = foodMass;

    PRINT_INFO("Food " << NAME_ID_CLASS(*food) << " was changed in dish " << NAME_ID << "");
}

void Dish::changeAmountOfPeople(uint64_t amountOfPeople) {
    uint64_t newMass, newPrice, newFats, newProteins, newCarbohydrates, newCalories;
    uint64_t currentAmountOfPeople = getAmountOfPeople();

    if ( amountOfPeople < minAmountOfPeople || amountOfPeople > maxAmountOfPeople ) {
        PRINT_ERR("Wrong dish amount of people provided [" << amountOfPeople << "]");

        throw WrongDishAmountOfPeople();
    }

    newMass = std::round(getMass()*amountOfPeople/currentAmountOfPeople);
    newPrice = std::round(getPrice()*amountOfPeople/currentAmountOfPeople);
    newFats = std::round(getFats()*amountOfPeople/currentAmountOfPeople);
    newProteins = std::round(getProteins()*amountOfPeople/currentAmountOfPeople);
    newCarbohydrates = std::round(getCarbohydrates()*amountOfPeople/currentAmountOfPeople);
    newCalories = std::round(getCalories()*amountOfPeople/currentAmountOfPeople);

    if ( newMass > maxMass ) {
        PRINT_ERR("Could not change amount of people in the dish. Result mass is too big [" << newMass << "]");

        throw TooBigDishMass();
    }

    if ( newPrice > maxPrice ) {
        PRINT_ERR("Could not change amount of people in the dish. Result price is too big [" << newPrice << "]");

        throw TooBigDishPrice();
    }

    if ( newFats > maxFats ) {
        PRINT_ERR("Could not change amount of people in the dish. Result fats are too big [" << newFats << "]");

        throw TooBigDishFats();
    }

    if ( newProteins > maxProteins ) {
        PRINT_ERR("Could not change amount of people in the dish. Result proteins are too big [" << newProteins << "]");

        throw TooBigDishProteins();
    }

    if ( newCarbohydrates > maxCarbohydrates ) {
        PRINT_ERR("Could not change amount of people in the dish. Result carbohydrates are too big [" << newCarbohydrates << "]");

        throw TooBigDishCarbohydrates();
    }

    if ( newCalories > maxCalories ) {
        PRINT_ERR("Could not change amount of people in the dish. Result calories are too big [" << newCalories << "]");

        throw TooBigDishCalories();
    }

    setMass(newMass);
    setPrice(newPrice);
    setFats(newFats);
    setProteins(newProteins);
    setCarbohydrates(newCarbohydrates);
    setCalories(newCalories);
    setAmountOfPeople(amountOfPeople);

    for ( auto& entry: ingridients ) {
        entry.second = entry.second * amountOfPeople / currentAmountOfPeople;
    }

    PRINT_INFO("Dish " << NAME_ID << " now have " << amountOfPeople << " people");
}

void Dish::setAmountOfPeople(uint64_t amountOfPeople) {
    if ( amountOfPeople < minAmountOfPeople || amountOfPeople > maxAmountOfPeople ) {
        PRINT_ERR("Wrong dish amount of people provided [" << amountOfPeople << "]");

        throw WrongPeopleStatsAmountOfPeople();
    }
    this->amountOfPeople = amountOfPeople;

    PRINT_INFO("Dish class " << NAME_ID << " amount of people set to " << amountOfPeople);
}

uint64_t Dish::getAmountOfPeople(void) const {
    return amountOfPeople;
}

const std::map<Food*, uint64_t, Stats::Compare>& Dish::getIngridientMap(void) const {
    return ingridients;
}

std::ostream& operator<<(std::ostream& out, const Dish& dish) {
#ifdef DEBUG
    std::map<Food*, uint64_t, Stats::Compare> dishMap = dish.getIngridientMap();

    out << dynamic_cast<const Stats&>(dish) << std::endl;
    out << "        INGRIDIENTS (" << dishMap.size() << "):" << std::endl;
    out << "        >>> >>> >>>" << std::endl;

    for ( auto& entry: dishMap ) {
        out << "        ingridient " << *entry.first << std::endl;
        out << "        - mass in dish: " << entry.second << " gram" << std::endl;
    }
    out << "        <<< <<< <<<";
#else
    out << dish.getName();
#endif

    return out;
}
