#include <debug.hpp>
#include <itemsForm.hpp>

#include <string>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>
#include <QFile>

ItemForm::ItemForm(void) {
    // TODO: Load this list from some default settings or leave empty
    Item* item1 = new Item("Item #1", 1, 1, Item::GRAM);
    Item* item25 = new Item("Item #25", 25, 25, Item::PIECE);
    Item* item125 = new Item("Item #125", 125, 125, Item::PIECE);

    Food* food1 = new Food("Food #1", 1, 1, Item::GRAM, 1, 1, 1, 1);
    Food* food25 = new Food("Food #25", 25, 25, Item::PIECE, 25, 25, 25, 25);
    Food* food125 = new Food("Food #125", 125, 125, Item::PIECE, 125, 125, 125, 125);

    Dish* dish1 = new Dish("Dish #1", food1, food1->getMass(), 1);
    Dish* dish25 = new Dish("Dish #25", food25, food25->getMass(), 1);
    Dish* dish125 = new Dish("Dish #125", food125, food125->getMass(), 1);

    avaliableItems.push_back(item1);
    item1->addItemList(&avaliableItems);
    avaliableItems.push_back(item25);
    item25->addItemList(&avaliableItems);
    avaliableItems.push_back(item125);
    item125->addItemList(&avaliableItems);

    avaliableItems.push_back(food1);
    food1->addItemList(&avaliableItems);
    avaliableItems.push_back(food25);
    food25->addItemList(&avaliableItems);
    avaliableItems.push_back(food125);
    food125->addItemList(&avaliableItems);

    avaliableDish.push_back(dish1);
    dish1->addDishList(&avaliableDish);
    avaliableDish.push_back(dish25);
    dish25->addDishList(&avaliableDish);
    avaliableDish.push_back(dish125);
    dish125->addDishList(&avaliableDish);

    PRINT_OBJ("ItemForm created");
}

ItemForm::~ItemForm(void) {
    for ( std::list<Item*>::iterator it = avaliableItems.begin(); it != avaliableItems.end(); ) {
        std::list<Item*>::iterator oldit = it++;

        delete *oldit;
    }

    PRINT_OBJ("ItemForm destroyed");
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
        QJsonObject itemObj;

        if ( dynamic_cast<Food *>(entry) ) {
            writeItem(itemObj, *entry);

            foodList.append(itemObj);
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

bool ItemForm::saveData() {
    QJsonObject saveObj;
    QFile saveFile(QStringLiteral("save.json"));

    if ( !saveFile.open(QIODevice::WriteOnly) ) {
        PRINT_ERR("Couldn't open save file.");

        return false;
    }

    saveItems(saveObj);
    saveFood(saveObj);
    saveDish(saveObj);

    QJsonDocument saveDoc(saveObj);
    saveFile.write(saveDoc.toJson());

    return true;
}
