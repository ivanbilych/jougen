#ifndef ITEM_H
#define ITEM_H

#include <common.hpp>
#include <stats.hpp>

#include <iostream>
#include <list>
#include <string>

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
        std::list<std::list<Item*>* > listOfItemLists {};

    protected:
        Item(std::string name, uint64_t mass, uint64_t price, MeasureType measureType, uint64_t minMass, uint64_t maxMass, uint64_t minPrice, uint64_t maxPrice, uint64_t minFats, uint64_t maxFats, uint64_t minProteins, uint64_t maxProteins, uint64_t minCarbohydrates, uint64_t maxCarbohydrates, uint64_t minCalories, uint64_t maxCalories, std::list<Item*>* itemList = nullptr);

    public:
        Item(std::string name, uint64_t mass, uint64_t price, MeasureType measureType, std::list<Item*>* itemList = nullptr);
        virtual ~Item(void);

        Item& operator=(const Item& right);

        void addItemList(std::list<Item*>* itemList);

        void setItemUnitType(MeasureType measureType);
        void setItemMass(uint64_t mass);
        void setItemPrice(uint64_t price);
        void setItemFats(uint64_t fats);
        void setItemProteins(uint64_t proteins);
        void setItemCarbohydrates(uint64_t carbohydrates);
        void setItemCalories(uint64_t calories);

        MeasureType getUnitType(void) const;
        std::string getUnitTypeName(void) const;

        static const std::string* getItemMeasureTypeNamesList(void);
};

std::ostream& operator<<(std::ostream& out, const Item& item);

#endif // ITEM_H
