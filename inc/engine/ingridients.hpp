#ifndef INGRIDIENTS_H
#define INGRIDIENTS_H

#include <common.hpp>
#include <dish.hpp>
#include <food.hpp>
#include <item.hpp>

#include <list>
#include <QJsonObject>

class Ingridients {
    public:
        std::list<Item*> avaliableItems {};
        std::list<Dish*> avaliableDish {};

        Ingridients(void);
        ~Ingridients(void);

        Item* readItem(const QJsonObject& json);
        Food* readFood(const QJsonObject& json);
        Dish* readDish(const QJsonObject& json);
        void writeItem(QJsonObject& json, Item& item) const;
        void writeFood(QJsonObject& json, Food& food) const;
        void writeDish(QJsonObject& json, Dish& dish) const;

        void saveItems(QJsonObject& json);
        void saveFood(QJsonObject& json);
        void saveDish(QJsonObject& json);
        bool saveData(QString& fileName);

        void loadItems(const QJsonArray& jsonArray);
        void loadFood(const QJsonArray& jsonArray);
        void loadDish(const QJsonArray& jsonArray);
        bool loadData(QString& fileName);
};

#endif // INGRIDIENTS_H
