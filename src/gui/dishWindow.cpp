#include <convert.hpp>
#include <debug.hpp>
#include <errors.hpp>

#include <dishWindow.hpp>
#include "ui_dishWindow.h"

DishWindow::DishWindow(QWidget* parent) :
    QDialog {parent},
    ui {new Ui::DishWindow},
    foodStringList {new QStringList},
    itemListModel {new QStringListModel {*foodStringList, NULL}} {

    ui->setupUi(this);
    ui->listView_1->setModel(itemListModel);
    ui->tableWidget_1->setColumnCount(2);

    PRINT_OBJ("DishWindow created");
}

DishWindow::DishWindow(Dish* dish, QWidget* parent) :
    QDialog {parent},
    ui {new Ui::DishWindow},
    foodStringList {new QStringList},
    itemListModel {new QStringListModel {*foodStringList, NULL}},
    dish {dish},
    editMode {true} {

    ui->setupUi(this);
    ui->listView_1->setModel(itemListModel);
    ui->tableWidget_1->setColumnCount(2);
    applyStats(dish);
    this->setWindowTitle("Edit dish");

    PRINT_OBJ("Existed dish edit window created");
}

DishWindow::~DishWindow() {
    delete ui;
    delete foodStringList;
    delete itemListModel;

    PRINT_OBJ("DishWindow destroyed");
}

void DishWindow::on_buttonBox_1_accepted() {
    if ( dishFoodList.size() && !editMode ) {
        emit itemObjectReady(createNewDish());
    } else {
        int pos_y = 0;
        QString newAmountOfPeople = ui->lineEdit_2->text();

        if ( newAmountOfPeople.isEmpty() ) {
            PRINT_ERR("Amount of people could not be empty");

            throw EmptyAmountOfPeopleException();
        }

        PRINT_DEBUG("Changing every food item to correct...");

        for ( auto& entry: dish->getIngridientMap() ) {
            QString foodAmount = ui->tableWidget_1->item(pos_y, 1)->text();

            if ( foodAmount.isEmpty() ) {
                PRINT_ERR("Dish ingridient could not be empty");

                throw EmptyDishIngridientException();
            }

            dish->changeFoodAmount(entry.first, QStringToMass(foodAmount));
            pos_y += 1;
        }

        if ( oldAmountOfPeople != newAmountOfPeople ) {
            PRINT_DEBUG("Changing amount of people to correct...");

            dish->changeAmountOfPeople(newAmountOfPeople.toLong());
        }
    }

    this->hide();

    PRINT_DEBUG("New dish accepted");
}

void DishWindow::on_buttonBox_1_rejected() {
    this->hide();

    PRINT_DEBUG("New dish rejected");
}

void DishWindow::fillItemList(std::list<Item*>* itemsList) {
    avaliableItemsList = itemsList;

    for ( auto& entry: *itemsList ) {
        if ( dynamic_cast<Food*>(entry) ) {
            foodStringList->append(QString::fromStdString(entry->getName()));
        } else {
            foodStringList->append(QString::fromStdString(entry->getName())+QString(" (item)"));
        }
    }

    itemListModel->setStringList(*foodStringList);

    PRINT_DEBUG("Item list filled");
}

Dish* DishWindow::createNewDish(void) {
    int pos_y = 0;
    std::list<Food*>::iterator item = dishFoodList.begin();
    QString name = ui->lineEdit_1->text();
    QString foodAmount = ui->tableWidget_1->item(pos_y, 1)->text();
    QString amountOfPeople = ui->lineEdit_2->text();

    if ( amountOfPeople.isEmpty() ) {
        amountOfPeople = QString("1");
    }

    if ( name.isEmpty() ) {
        PRINT_ERR("Food name could not be empty");

        throw EmptyDishNameException();
    }

    if ( !dishFoodList.size() ) {
        PRINT_ERR("There is no food in list for dish");

        throw EmptyDishListException();
    }

    if ( foodAmount.isEmpty() ) {
        PRINT_ERR("Dish ingridient could not be empty");

        throw EmptyDishIngridientException();
    }

    PRINT_DEBUG("foodAmount: " << QStringToMass(foodAmount));

    dish = new Dish(name.toStdString(), dynamic_cast<Food*>(*item),
                    QStringToMass(foodAmount),
                    static_cast<uint64_t>(amountOfPeople.toLong()));

    PRINT_DEBUG("New dish created");

    pos_y += 1;
    std::advance(item, 1);

    for ( ; item != dishFoodList.end(); item++ ) {
        foodAmount = ui->tableWidget_1->item(pos_y, 1)->text();

        if ( foodAmount.isEmpty() ) {
            PRINT_ERR("Dish ingridient could not be empty");

            throw EmptyDishIngridientException();
        }

        dish->addFood(dynamic_cast<Food*>(*item), QStringToMass(foodAmount));
        pos_y += 1;
    }

    return dish;
}

void DishWindow::applyStats(Dish* dish) {
    oldAmountOfPeople = QString::number(dish->getAmountOfPeople());

    ui->lineEdit_1->setText(QString::fromStdString(dish->getName()));
    ui->lineEdit_1->setDisabled(true);
    ui->lineEdit_2->setText(oldAmountOfPeople);

    for ( auto& entry: dish->getIngridientMap() ) {
        int rowCount = ui->tableWidget_1->rowCount();

        ui->tableWidget_1->setRowCount(rowCount+1);
        ui->tableWidget_1->setItem(rowCount, 0, new QTableWidgetItem(QString::fromStdString(entry.first->getName())));
        ui->tableWidget_1->setItem(rowCount, 1, new QTableWidgetItem(massToQString(entry.second)));

        dishFoodList.push_back(entry.first);
    }

    PRINT_DEBUG("Dish stats applied");
}

void DishWindow::on_pushButton_1_clicked() {
    QModelIndexList selected = ui->listView_1->selectionModel()->selectedIndexes();

    if ( !selected.isEmpty() ) {
        std::list<Item*>::iterator item = avaliableItemsList->begin();

        std::advance(item, selected.first().row());

        if ( dynamic_cast<Food*>(*item) && *std::find(dishFoodList.begin(), dishFoodList.end(), *item) == *dishFoodList.end() ) {
            int rowCount = ui->tableWidget_1->rowCount();

            if ( editMode ) {
                dish->addFood(dynamic_cast<Food*>(*item), 1);
            }
            dishFoodList.push_back(dynamic_cast<Food*>(*item));

            ui->tableWidget_1->setRowCount(rowCount+1);
            ui->tableWidget_1->setItem(rowCount, 0, new QTableWidgetItem(QString::fromStdString((*item)->getName())));
            ui->tableWidget_1->setItem(rowCount, 1, new QTableWidgetItem(QString("0.001")));

            PRINT_DEBUG("Item was added");
        }
    }
}

void DishWindow::on_pushButton_2_clicked() {
    if ( ui->tableWidget_1->currentRow() != -1 ) {
        std::list<Food*>::iterator item = dishFoodList.begin();
        int currentRow = ui->tableWidget_1->currentRow();

        std::advance(item, currentRow);

        if ( editMode && dish->getIngridientMap().size() > 1 ) {
            dish->removeFood(dynamic_cast<Food*>(*item));
            dishFoodList.remove(*item);

            ui->tableWidget_1->removeRow(currentRow);
        } else if ( !editMode ) {
            dishFoodList.remove(*item);

            ui->tableWidget_1->removeRow(currentRow);
        }

        PRINT_DEBUG("Item was removed");
    }
}
