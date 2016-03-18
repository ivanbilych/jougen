#include <item.hpp>
#include <engineLimits.hpp>
#include <debug.hpp>
#include <errors.hpp>

const std::string Item::itemMeasureTypeNames[] = {
    "gram",
    "piece",
    "pack",
    "stick",
    "jar",
    "can",
    "loaf",
    ""
};

Item::Item(std::string name, uint64_t mass, uint64_t price, MeasureType measureType, uint64_t minMass, uint64_t maxMass, uint64_t minPrice, uint64_t maxPrice, uint64_t minFats, uint64_t maxFats, uint64_t minProteins, uint64_t maxProteins, uint64_t minCarbohydrates, uint64_t maxCarbohydrates, uint64_t minCalories, uint64_t maxCalories) :
    Stats {name, minMass, maxMass, minPrice, maxPrice, minFats, maxFats,
           minProteins, maxProteins, minCarbohydrates, maxCarbohydrates,
           minCalories, maxCalories},
    measureType {measureType} {

    if ( measureType == GRAM && mass != MIN_MASS_FOR_GRAM ) {
        PRINT_ERR("Wrong item mass for GRAM value provided");

        throw WrongItemMass();
    }

    setMass(mass);
    setPrice(price);

    PRINT_OBJ("Created item class " << NAME_ID);
}

Item::Item(std::string name, uint64_t mass, uint64_t price, MeasureType measureType) :
    Stats {name, ITEM_MIN_MASS, ITEM_MAX_MASS, ITEM_MIN_PRICE, ITEM_MAX_PRICE},
    measureType {measureType} {

    if ( measureType == GRAM && mass != MIN_MASS_FOR_GRAM ) {
        PRINT_ERR("Wrong item mass for GRAMM value provided");

        throw WrongItemMass();
    }

    setMass(mass);
    setPrice(price);

    PRINT_OBJ("Created item class " << NAME_ID);
}

Item::~Item(void) {
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
