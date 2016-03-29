#include <debug.hpp>
#include <itemsForm.hpp>

#include <string>

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
    for ( auto& entry: avaliableItems ) {
        delete entry;
    }

    PRINT_OBJ("ItemForm destroyed");
}
