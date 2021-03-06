#include <debug.hpp>
#include <engineLimits.hpp>
#include <errors.hpp>
#include <item.hpp>

#include <algorithm>

const std::string Item::itemMeasureTypeNames[] = {
    "kg",
    "piece",
    "pack",
    "stick",
    "jar",
    "can",
    "loaf",
    ""
};

Item::Item(std::string name, uint64_t mass, uint64_t price, MeasureType measureType, uint64_t minMass, uint64_t maxMass, uint64_t minPrice, uint64_t maxPrice, uint64_t minFats, uint64_t maxFats, uint64_t minProteins, uint64_t maxProteins, uint64_t minCarbohydrates, uint64_t maxCarbohydrates, uint64_t minCalories, uint64_t maxCalories, std::list<Item*>* itemList) :
    Stats {name, minMass, maxMass, minPrice, maxPrice, minFats, maxFats,
           minProteins, maxProteins, minCarbohydrates, maxCarbohydrates,
           minCalories, maxCalories},
    measureType {measureType} {

    if ( measureType == KGRAM && mass != MIN_MASS_FOR_KGRAM ) {
        PRINT_ERR("Wrong item mass for KGRAM value provided");

        throw WrongItemMass();
    }

    setMass(mass);
    setPrice(price);

    addItemList(itemList);

    PRINT_OBJ("Created item class " << NAME_ID);
}

Item::Item(std::string name, uint64_t mass, uint64_t price, MeasureType measureType, std::list<Item*>* itemList) :
    Stats {name, ITEM_MIN_MASS, ITEM_MAX_MASS, ITEM_MIN_PRICE, ITEM_MAX_PRICE},
    measureType {measureType} {

    if ( measureType == KGRAM && mass != MIN_MASS_FOR_KGRAM ) {
        PRINT_ERR("Wrong item mass for KGRAM value provided");

        throw WrongItemMass();
    }

    setMass(mass);
    setPrice(price);

    addItemList(itemList);

    PRINT_OBJ("Created item class " << NAME_ID);
}

Item::~Item(void) {
    for ( auto& entry: listOfItemLists ) {
        std::list<Item*>::iterator it = std::find(entry->begin(), entry->end(), this);

        PRINT_DEBUG("Removing item " << NAME_ID << " from list");

        if ( it != entry->end() ) {
            entry->erase(it);
        }
    }

    PRINT_OBJ("Destroyed item class " << NAME_ID);
}

Item& Item::operator=(const Item& right) {
    if ( this == &right ) {
        return *this;
    }

    Item::Stats::operator=(right);

    measureType = right.getUnitType();

    return *this;
}

void Item::addItemList(std::list<Item*>* itemList) {
    if ( itemList != nullptr ) {
        std::list<std::list<Item*>* >::iterator it = std::find(listOfItemLists.begin(), listOfItemLists.end(), itemList);

        if ( it == listOfItemLists.end() ) {
            listOfItemLists.push_back(itemList);

            PRINT_DEBUG("Register item list in item " << NAME_ID);
        }
    }
}

void Item::setItemUnitType(MeasureType measureType) {
    this->measureType = measureType;
}

void Item::setItemMass(uint64_t mass) {
    setMass(mass);
}

void Item::setItemPrice(uint64_t price) {
    setPrice(price);
}

void Item::setItemFats(uint64_t fats) {
    setFats(fats);
}

void Item::setItemProteins(uint64_t proteins) {
    setProteins(proteins);
}

void Item::setItemCarbohydrates(uint64_t carbohydrates) {
    setCarbohydrates(carbohydrates);
}

void Item::setItemCalories(uint64_t calories) {
    setCalories(calories);
}

Item::MeasureType Item::getUnitType(void) const {
    return measureType;
}

std::string Item::getUnitTypeName(void) const {
    return itemMeasureTypeNames[static_cast<uint32_t>(getUnitType())];
}

const std::string* Item::getItemMeasureTypeNamesList(void) {
    return itemMeasureTypeNames;
}

std::ostream& operator<<(std::ostream& out, const Item& item) {
#ifdef DEBUG
    out << dynamic_cast<const Stats&>(item) << std::endl;
    out << "        - measure type: " << item.getUnitTypeName();
#else
    out << dynamic_cast<const Stats&>(item);
#endif

    return out;
}
