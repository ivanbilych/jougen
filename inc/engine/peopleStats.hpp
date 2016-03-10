#ifndef PEOPLE_STATS_H
#define PEOPLE_STATS_H

#include <iostream>
#include <string>
#include <list>

#include <common.hpp>
#include <stats.hpp>
#include <engineLimits.hpp>
#include <debug.hpp>
#include <errors.hpp>

template<typename T>
class PeopleStats : public Stats {
    private:
        uint64_t amountOfPeople;
        std::list<T> items;

    protected:
        void setAmountOfPeople(uint64_t amountOfPeople);

    public:
        const uint64_t minListItemsAmount;
        const uint64_t maxListItemsAmount;
        const uint64_t minAmountOfPeople;
        const uint64_t maxAmountOfPeople;

        PeopleStats(std::string name, uint64_t minMass, uint64_t maxMass, uint64_t minPrice, uint64_t maxPrice, uint64_t minFats, uint64_t maxFats, uint64_t minProteins, uint64_t maxProteins, uint64_t minCarbohydrates, uint64_t maxCarbohydrates, uint64_t minCalories, uint64_t maxCalories, uint64_t minListItemsAmount, uint64_t maxListItemsAmount, uint64_t minAmountOfPeople, uint64_t maxAmountOfPeople);
        ~PeopleStats(void);

        PeopleStats& operator=(const PeopleStats& right);

        uint64_t getAmountOfPeople(void) const;
        const std::list<T>& getList(void) const;
        void addItem(const T& statsItem);
        void removeItem(const T& statsItem);
        void changeAmountOfPeople(uint64_t amountOfPeople);
};

template<typename T>
PeopleStats<T>::PeopleStats(std::string name, uint64_t minMass, uint64_t maxMass, uint64_t minPrice, uint64_t maxPrice, uint64_t minFats, uint64_t maxFats, uint64_t minProteins, uint64_t maxProteins, uint64_t minCarbohydrates, uint64_t maxCarbohydrates, uint64_t minCalories, uint64_t maxCalories, uint64_t minListItemsAmount, uint64_t maxListItemsAmount, uint64_t minAmountOfPeople, uint64_t maxAmountOfPeople) :
        Stats {name, minMass, maxMass, minPrice, maxPrice, minFats, maxFats,
               minProteins, maxProteins, minCarbohydrates, maxCarbohydrates,
               minCalories, maxCalories},
        minListItemsAmount {minListItemsAmount},
        maxListItemsAmount {maxListItemsAmount},
        minAmountOfPeople {minAmountOfPeople},
        maxAmountOfPeople {maxAmountOfPeople} {

    PRINT_OBJ("Created people stats class " << NAME_ID);
}

template<typename T>
PeopleStats<T>::~PeopleStats(void) {
    PRINT_OBJ("Destroyed people stats class " << NAME_ID);
}

template<typename T>
PeopleStats<T>& PeopleStats<T>::operator=(const PeopleStats& right) {
    if ( this == &right ) {
        return *this;
    }

    PeopleStats::Stats::operator=(right);

    amountOfPeople = right.getAmountOfPeople();

    items.clear();
    for ( typename std::list<T>::iterator it = items.begin(); it != items.end(); it++ ) {
        addItem(*it);
    }

    return *this;
}

template<typename T>
void PeopleStats<T>::setAmountOfPeople(uint64_t amountOfPeople) {
    if ( amountOfPeople < minAmountOfPeople || amountOfPeople > maxAmountOfPeople ) {
        PRINT_ERR("Wrong people stats amount of people provided [" << amountOfPeople << "]");

        throw WrongPeopleStatsAmountOfPeople();
    }
    this->amountOfPeople = amountOfPeople;

    PRINT_INFO("People stats class " << NAME_ID << " amount of people set to " << amountOfPeople);
}

template<typename T>
void PeopleStats<T>::addItem(const T& item) {
    uint64_t newMass, newPrice, newFats, newProteins, newCarbohydrates, newCalories;

    if ( items.size() >= maxListItemsAmount ) {
        PRINT_ERR("Could not add new item to the list");

        throw TooMuchDishInList();
    }

    newMass = getMass() + item.getMass();
    newPrice = getPrice() + item.getPrice();
    newFats = getFats() + item.getFats();
    newProteins = getProteins() + item.getProteins();
    newCarbohydrates = getCarbohydrates() + item.getCarbohydrates();
    newCalories = getCalories() + item.getCalories();

    if ( newMass > maxMass ) {
        PRINT_ERR("Could not add new item to " << NAME_ID << ". Result mass is too big");

        throw TooBigMealMass();
    }

    if ( newPrice > maxPrice ) {
        PRINT_ERR("Could not add new item to " << NAME_ID << ". Result price is too big");

        throw TooBigMealPrice();
    }

    if ( newFats > maxFats ) {
        PRINT_ERR("Could not add new item to " << NAME_ID << ". Result fats are too big");

        throw TooBigMealFats();
    }

    if ( newProteins > maxProteins ) {
        PRINT_ERR("Could not add new item to " << NAME_ID << ". Result proteins are too big");

        throw TooBigMealProteins();
    }

    if ( newCarbohydrates > maxCarbohydrates ) {
        PRINT_ERR("Could not add new item to " << NAME_ID << ". Result carbohydrates are too big");

        throw TooBigMealCarbohydrates();
    }

    if ( newCalories > maxCalories ) {
        PRINT_ERR("Could not add new item to " << NAME_ID << ". Result calories are too big");

        throw TooBigMealCalories();
    }

    items.push_back(item);

    setMass(newMass);
    setPrice(newPrice);
    setFats(newFats);
    setProteins(newProteins);
    setCarbohydrates(newCarbohydrates);
    setCalories(newCalories);

    PRINT_INFO(NAME_ID_CLASS(item) << " was added to meal " << NAME_ID);
}

template<typename T>
void PeopleStats<T>::removeItem(const T& item) {
    uint64_t newMass, newPrice, newFats, newProteins, newCarbohydrates, newCalories;
    bool erased = false;

    if ( items.size() <= minListItemsAmount ) {
        PRINT_ERR("Could not remove item from the list");

        throw LastDishInList();
    }

    newMass = getMass() - item.getMass();
    newPrice = getPrice() - item.getPrice();
    newFats = getFats() - item.getFats();
    newProteins = getProteins() - item.getProteins();
    newCarbohydrates = getCarbohydrates() - item.getCarbohydrates();
    newCalories = getCalories() - item.getCalories();

    for ( typename std::list<T>::iterator it = items.begin(); it != items.end(); it++ ) {
        if ( it->getId() == item.getId() ) {
            items.erase(it);
            erased = true;
        }
    }

    if ( !erased ) {
        PRINT_ERR("Could not remove item that is not in the " << NAME_ID);

        throw NoSuchDishInList();
    }

    setMass(newMass);
    setPrice(newPrice);
    setFats(newFats);
    setProteins(newProteins);
    setCarbohydrates(newCarbohydrates);
    setCalories(newCalories);
}

template<typename T>
void PeopleStats<T>::changeAmountOfPeople(uint64_t amountOfPeople) {
    uint64_t newMass, newPrice, newFats, newProteins, newCarbohydrates, newCalories;
    typename std::list<T>::iterator it = items.begin();

    PRINT_INFO("Recalculating people amount for " << NAME_ID);

    newMass = getMass() * amountOfPeople / getAmountOfPeople();
    newPrice = getPrice() * amountOfPeople / getAmountOfPeople();
    newFats = getFats() * amountOfPeople / getAmountOfPeople();
    newProteins = getProteins() * amountOfPeople / getAmountOfPeople();
    newCarbohydrates = getCarbohydrates() * amountOfPeople / getAmountOfPeople();
    newCalories = getCalories() * amountOfPeople / getAmountOfPeople();

    if ( newMass > maxMass ) {
        PRINT_ERR("Could not add new item to " << NAME_ID << ". Result mass is too big");

        throw TooBigMealMass();
    }

    if ( newPrice > maxPrice ) {
        PRINT_ERR("Could not add new item to " << NAME_ID << ". Result price is too big");

        throw TooBigMealPrice();
    }

    if ( newFats > maxFats ) {
        PRINT_ERR("Could not add new item to " << NAME_ID << ". Result fats are too big");

        throw TooBigMealFats();
    }

    if ( newProteins > maxProteins ) {
        PRINT_ERR("Could not add new item to " << NAME_ID << ". Result proteins are too big");

        throw TooBigMealProteins();
    }

    if ( newCarbohydrates > maxCarbohydrates ) {
        PRINT_ERR("Could not add new item to " << NAME_ID << ". Result carbohydrates are too big");

        throw TooBigMealCarbohydrates();
    }

    if ( newCalories > maxCalories ) {
        PRINT_ERR("Could not add new item to " << NAME_ID << ". Result calories are too big");

        throw TooBigMealCalories();
    }

    try {
        for ( ; it != items.end(); it++ ) {
            it->changeAmountOfPeople(amountOfPeople);
        }
    } catch ( const DishException& e ) {
        PRINT_ERR("Could not recalculate people amount for " << NAME_ID << ". Fixing...");

        for ( typename std::list<T>::iterator fixIt = items.begin(); fixIt != it; fixIt++ ) {
            fixIt->changeAmountOfPeople(amountOfPeople);
        }

        throw SetMealPeopleAmountError();
    }

    setMass(newMass);
    setPrice(newPrice);
    setFats(newFats);
    setProteins(newProteins);
    setCarbohydrates(newCarbohydrates);
    setCalories(newCalories);
    setAmountOfPeople(amountOfPeople);
}

template<typename T>
uint64_t PeopleStats<T>::getAmountOfPeople(void) const {
    return amountOfPeople;
}

template<typename T>
const std::list<T>& PeopleStats<T>::getList(void) const {
    return items;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const PeopleStats<T>& peopleStats) {
#ifdef DEBUG
    out << static_cast<const Stats&>(peopleStats) << std::endl;
    out << "        - amount of people: " << peopleStats.getAmountOfPeople();
#else
    out << peopleStats.getName();
#endif

    return out;
}

#endif // PEOPLE_STATS_H
