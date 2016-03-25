#include <debug.hpp>
#include <itemsForm.hpp>

#include <string>

ItemForm::ItemForm(void) {
    // TODO: Load this list from some default settings or leave empty

    avaliableItems.push_back(new Item("Backpack", 10, 20020, Item::PIECE));
    avaliableItems.push_back(new Item("Rope", 100, 2020, Item::PIECE));
    avaliableItems.push_back(new Item("Nails", 1000, 200, Item::PIECE));
    avaliableItems.push_back(new Item("Pen", 10010, 20, Item::PIECE));
    avaliableItems.push_back(new Item("Pencil", 10100, 2, Item::PIECE));

    avaliableItems.push_back(new Food("Apple", 1, 1, Item::GRAM, 1, 2, 3, 4));
    avaliableItems.push_back(new Food("Bear", 10, 10, Item::PIECE, 5, 6, 7, 8));
    avaliableItems.push_back(new Food("Rice", 10, 10, Item::PACK, 90, 100, 110, 120));
    avaliableItems.push_back(new Food("Orange", 10, 10, Item::STICK, 130, 140, 150, 160));
    avaliableItems.push_back(new Food("Pepper", 10, 10, Item::JAR, 1700, 1800, 1900, 2000));
    avaliableItems.push_back(new Food("Tomato", 10, 10, Item::CAN, 2100, 2200, 2300, 2400));
    avaliableItems.push_back(new Food("Beaf", 10, 10, Item::LOAF, 25001, 26001, 27001, 28001));

    avaliableDish.push_back(new Dish("Apple pie", dynamic_cast<Food &>(*avaliableItems.back()), avaliableItems.back()->getMass(), 1));
    avaliableDish.push_back(new Dish("Beaf pie", dynamic_cast<Food &>(*avaliableItems.back()), avaliableItems.back()->getMass()*10, 2));

    PRINT_OBJ("ItemForm created");
}

ItemForm::~ItemForm(void) {
    for ( auto& entry: avaliableItems ) {
        delete entry;
    }
    for ( auto& entry: avaliableDish ) {
        delete entry;
    }

    PRINT_OBJ("ItemForm destroyed");
}
