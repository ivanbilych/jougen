#ifndef ITEMSFORM_H
#define ITEMSFORM_H

#include <list>

#include <common.hpp>
#include <item.hpp>
#include <food.hpp>
#include <dish.hpp>

class ItemForm {
    public:
        std::list<Item *> avaliableItems {};
        std::list<Dish *> avaliableDish {};

        ItemForm(void);
        ~ItemForm(void);
};

#endif // ITEMSFORM_H
