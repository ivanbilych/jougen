#include <debug.hpp>
#include <itemsForm.hpp>

#include <algorithm>
#include <string>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>
#include <QFile>

ItemForm::ItemForm(void) {
    PRINT_OBJ("ItemForm created");
}

ItemForm::~ItemForm(void) {
    for ( std::list<Item*>::iterator it = avaliableItems.begin(); it != avaliableItems.end(); ) {
        std::list<Item*>::iterator oldit = it++;

        delete *oldit;
    }

    PRINT_OBJ("ItemForm destroyed");
}

Item * ItemForm::readItem(const QJsonObject &json) {
    return new Item(json["name"].toString().toStdString(),
                    json["mass"].toInt(),
                    json["price"].toInt(),
                    static_cast<Item::MeasureType>(json["measureType"].toInt()));
}

Food * ItemForm::readFood(const QJsonObject &json) {
    return new Food(json["name"].toString().toStdString(),
                    json["mass"].toInt(),
                    json["price"].toInt(),
                    static_cast<Item::MeasureType>(json["measureType"].toInt()),
                    json["fats"].toInt(),
                    json["proteins"].toInt(),
                    json["carbohydrates"].toInt(),
                    json["calories"].toInt());
}

Dish * ItemForm::readDish(const QJsonObject &json) {
    QJsonArray itemsList = json["items"].toArray();
    Food * newFood = readFood(itemsList[0].toObject()["food"].toObject());
    Dish * newDish = new Dish(json["name"].toString().toStdString(), newFood,
                              itemsList[0].toObject()["amount"].toInt());

    avaliableItems.push_back(newFood);
    newFood->addItemList(&avaliableItems);

    for ( int index = 1; index < itemsList.size(); index++ ) {
        newFood = readFood(itemsList[index].toObject()["food"].toObject());
        newDish->addFood(newFood, itemsList[index].toObject()["amount"].toInt());
        std::list<Item*>::iterator it;

        for ( it = avaliableItems.begin(); ; it++ ) {
            if ( !(*it)->getName().compare(newFood->getName()) ) {
                delete newFood;

                break;
            } else if ( it == avaliableItems.end() ) {
                avaliableItems.push_back(newFood);
                newFood->addItemList(&avaliableItems);
            }
        }
    }

    return newDish;
}

void ItemForm::writeItem(QJsonObject &json, Item &item) const {
    json["name"] = QString::fromStdString(item.getName());
    json["mass"] = static_cast<qint64>(item.getMass());
    json["price"] = static_cast<qint64>(item.getPrice());
    json["measureType"] = static_cast<int>(item.getUnitType());
}

void ItemForm::writeFood(QJsonObject &json, Food &food) const {
    json["name"] = QString::fromStdString(food.getName());
    json["mass"] = static_cast<qint64>(food.getMass());
    json["price"] = static_cast<qint64>(food.getPrice());
    json["measureType"] = static_cast<int>(food.getUnitType());
    json["fats"] = static_cast<qint64>(food.getFats());
    json["proteins"] = static_cast<qint64>(food.getProteins());
    json["carbohydrates"] = static_cast<qint64>(food.getCarbohydrates());
    json["calories"] = static_cast<qint64>(food.getCalories());
}

void ItemForm::writeDish(QJsonObject &json, Dish &dish) const {
    QJsonArray itemsList;

    json["name"] = QString::fromStdString(dish.getName());
    json["amountOfPeople"] = static_cast<qint64>(dish.getAmountOfPeople());

    for ( auto &entry: dish.getIngridientMap() ) {
        QJsonObject mapEntry;
        QJsonObject food;

        writeFood(food, *(entry.first));

        mapEntry["food"] = food;
        mapEntry["amount"] = static_cast<qint64>(entry.second);

        itemsList.append(mapEntry);
    }

    json["items"] = itemsList;
}

void ItemForm::saveItems(QJsonObject &json) {
    QJsonArray itemsList;

    for ( auto &entry: avaliableItems ) {
        QJsonObject itemObj;

        if ( !dynamic_cast<Food *>(entry) ) {
            writeItem(itemObj, *entry);

            itemsList.append(itemObj);
        }
    }

    json["itemList"] = itemsList;
}

void ItemForm::saveFood(QJsonObject &json) {
    QJsonArray foodList;

    for ( auto &entry: avaliableItems ) {
        QJsonObject foodObj;

        if ( dynamic_cast<Food *>(entry) ) {
            writeFood(foodObj, *dynamic_cast<Food *>(entry));

            foodList.append(foodObj);
        }
    }

    json["foodList"] = foodList;
}

void ItemForm::saveDish(QJsonObject &json) {
    QJsonArray dishList;

    for ( auto &entry: avaliableDish ) {
        QJsonObject itemObj;

        writeDish(itemObj, *entry);

        dishList.append(itemObj);
    }

    json["dishList"] = dishList;
}

bool ItemForm::saveData(QString &fileName) {
    QJsonObject saveObj;
    QFile saveFile(fileName);

    if ( !saveFile.open(QIODevice::WriteOnly) ) {
        PRINT_ERR("Couldn't open save file.");

        return false;
    }

    saveItems(saveObj);
    saveFood(saveObj);
    saveDish(saveObj);

    QJsonDocument saveDoc(saveObj);

    if ( !fileName.right(5).compare(".json") ) {
        saveFile.write(saveDoc.toJson());
    } else {
        saveFile.write(saveDoc.toBinaryData());
    }

    return true;
}

void ItemForm::loadItems(const QJsonArray &jsonArray) {
    for ( int i = 0; i < jsonArray.size(); i++ ) {
        Item * newItem = readItem(jsonArray[i].toObject());
        std::list<Item*>::iterator it = std::find(avaliableItems.begin(), avaliableItems.end(), newItem);

        if ( it == avaliableItems.end() ) {
           avaliableItems.push_back(newItem);
           newItem->addItemList(&avaliableItems);
        }
    }
}

void ItemForm::loadFood(const QJsonArray &jsonArray) {
    for ( int i = 0; i < jsonArray.size(); i++ ) {
        Food * newFood = readFood(jsonArray[i].toObject());
        std::list<Item*>::iterator it;

        for ( it = avaliableItems.begin(); ; it++ ) {
            if ( !(*it)->getName().compare(newFood->getName()) ) {
                delete newFood;

                break;
            } else if ( it == avaliableItems.end() ) {
                avaliableItems.push_back(newFood);
                newFood->addItemList(&avaliableItems);
            }
        }
    }
}

void ItemForm::loadDish(const QJsonArray &jsonArray) {
    for ( int i = 0; i < jsonArray.size(); i++ ) {
        Dish * newDish = readDish(jsonArray[i].toObject());
        std::list<Dish*>::iterator it = std::find(avaliableDish.begin(), avaliableDish.end(), newDish);

        if ( it == avaliableDish.end() ) {
           avaliableDish.push_back(newDish);
           newDish->addDishList(&avaliableDish);
        }
    }
}

bool ItemForm::loadData(QString &fileName) {
    QFile loadFile(fileName);

    if ( !loadFile.open(QIODevice::ReadOnly) ) {
        PRINT_ERR("Couldn't open save file.");

        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc((!fileName.right(5).compare(".json")) ?
                           QJsonDocument::fromJson(saveData) :
                           QJsonDocument::fromBinaryData(saveData));

    loadDish(loadDoc.object()["dishList"].toArray());
    loadFood(loadDoc.object()["foodList"].toArray());
    loadItems(loadDoc.object()["itemList"].toArray());

    return true;
}
