#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

#include <common.hpp>
#include <stats.hpp>

class Item : public Stats {
    public:
        enum MeasureType {
            GRAM,
            PIECE,
            PACK,
            STICK,
            JAR,
            CAN,
            LOAF
        };

    private:
        static const std::string itemMeasureTypeNames[];
        MeasureType measureType;

    protected:
        Item(std::string name, uint64_t mass, uint64_t price, MeasureType measureType, uint64_t minMass, uint64_t maxMass, uint64_t minPrice, uint64_t maxPrice, uint64_t minFats, uint64_t maxFats, uint64_t minProteins, uint64_t maxProteins, uint64_t minCarbohydrates, uint64_t maxCarbohydrates, uint64_t minCalories, uint64_t maxCalories);

    public:
        Item(std::string name, uint64_t mass, uint64_t price, MeasureType measureType);
        virtual ~Item(void);
        Item& operator=(const Item& right);
        MeasureType getUnitType(void) const;
        std::string getUnitTypeName(void) const;
};

std::ostream& operator<<(std::ostream& out, const Item& item);

#endif // ITEM_H
