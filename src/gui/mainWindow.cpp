#include <debug.hpp>
#include <item.hpp>
#include <dish.hpp>
#include <food.hpp>

#include <QString>

#include <mainWindow.hpp>
#include "ui_mainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow {parent},
    ui {new Ui::MainWindow},
    itemStringList {new QStringList},
    dishStringList {new QStringList},
    itemListModel {new QStringListModel {*itemStringList, NULL}},
    dishListModel {new QStringListModel {*dishStringList, NULL}},
    itemForm {new ItemForm} {

    ui->setupUi(this);

    ui->listView_1->setModel(itemListModel);
    ui->listView_2->setModel(dishListModel);

    for ( auto& entry: itemForm->avaliableItems ) {
        itemStringList->append(QString::fromStdString(entry->getName()));
    }

    for ( auto& entry: itemForm->avaliableDish ) {
        dishStringList->append(QString::fromStdString(entry->getName()));
    }

    itemListModel->setStringList(*itemStringList);
    dishListModel->setStringList(*dishStringList);

    PRINT_OBJ("MainWindow created");
}

MainWindow::~MainWindow() {
    delete ui;
    delete itemStringList;
    delete dishStringList;
    delete itemListModel;
    delete dishListModel;

    PRINT_OBJ("MainWindow destroyed");
}

void MainWindow::on_pushButton_1_clicked() {
    NewIngridientWindow newIngridientWindow;

    QObject::connect(&newIngridientWindow, SIGNAL(itemObjectReady(Item *)), this, SLOT(addNewItemObject(Item *)));
    QObject::connect(&newIngridientWindow, SIGNAL(foodObjectReady(Food *)), this, SLOT(addNewFoodObject(Food *)));

    newIngridientWindow.exec();
}

void MainWindow::on_pushButton_2_clicked() {
    QModelIndexList selected = ui->listView_1->selectionModel()->selectedIndexes();

    if ( !selected.isEmpty() ) {
        const QModelIndex index = itemListModel->index(selected.first().row()?selected.first().row()-1:0);
        std::list<Item *>::iterator item = itemForm->avaliableItems.begin();

        std::advance(item, selected.first().row());
        itemForm->avaliableItems.erase(item);

        itemStringList->removeAt(selected.first().row());
        itemListModel->setStringList(*itemStringList);

        if ( itemStringList->size() ) {
            ui->listView_1->setCurrentIndex(index);
            displayListViewInfoItem(index);
        }

        ui->textEdit_1->clear();
   }
}

void MainWindow::on_pushButton_3_clicked() {
    NewDishWindow newDishWindow;

    newDishWindow.exec();
}

void MainWindow::on_pushButton_5_clicked() {
    if ( infoWindowType == ITEM || infoWindowType == FOOD ) {
        NewIngridientWindow newIngridientWindow;

        newIngridientWindow.exec();
    } else if ( infoWindowType == DISH ) {
        NewDishWindow newDishWindow;

        newDishWindow.exec();
    }
}

void MainWindow::on_listView_1_clicked(const QModelIndex &index) {
    displayListViewInfoItem(index);

    PRINT_DEBUG("Clicked item/food: " << index.data().toString().toStdString());
}

void MainWindow::on_listView_2_clicked(const QModelIndex &index) {
    displayListViewInfoDish(index);

    PRINT_DEBUG("Clicked dish: " << index.data().toString().toStdString());
}

void MainWindow::on_listView_1_entered(const QModelIndex &index) {
    displayListViewInfoItem(index);

    PRINT_DEBUG("Entered item/food: " << index.data().toString().toStdString());
}

void MainWindow::on_listView_2_entered(const QModelIndex &index) {
    displayListViewInfoDish(index);

    PRINT_DEBUG("Entered dish: " << index.data().toString().toStdString());
}

void MainWindow::addNewItemObject(Item *item) {
    QModelIndex index;

    itemStringList->append(QString::fromStdString(item->getName()));
    itemListModel->setStringList(*itemStringList);

    itemForm->avaliableItems.push_back(item);

    index = itemListModel->index(itemForm->avaliableItems.size()-1);
    ui->listView_1->setCurrentIndex(index);
    displayListViewInfoItem(index);

    PRINT_DEBUG("New item added");
}

void MainWindow::addNewFoodObject(Food *food) {
    QModelIndex index;

    itemStringList->append(QString::fromStdString(food->getName()));
    itemListModel->setStringList(*itemStringList);

    itemForm->avaliableItems.push_back(food);

    index = itemListModel->index(itemForm->avaliableItems.size()-1);
    ui->listView_1->setCurrentIndex(index);
    displayListViewInfoItem(index);

    PRINT_DEBUG("New food added");
}

void MainWindow::displayListViewInfoItem(const QModelIndex &index) {
    std::list<Item *>::iterator item = itemForm->avaliableItems.begin();
    QString itemInfo;

    std::advance(item, index.row());

    if ( dynamic_cast<Food *>(*item) ) {
        infoWindowType = FOOD;
    } else {
        infoWindowType = ITEM;
    }

    itemInfo += "Name: " + QString::fromStdString((*item)->getName()) + "\n";
    itemInfo += "Price: " + QString::number((*item)->getPrice()) + "\n";
    itemInfo += "Mass: " + QString::number((*item)->getMass()) + "\n";

    if ( infoWindowType == FOOD ) {
       itemInfo += "Fats: " + QString::number((*item)->getFats()) + "\n";
       itemInfo += "Proteins: "+ QString::number((*item)->getProteins()) + "\n";
       itemInfo += "Carbohydrates: " + QString::number((*item)->getCarbohydrates()) + "\n";
       itemInfo += "Calories: " + QString::number((*item)->getCalories()) + "\n";
    }

    ui->textEdit_1->setText(itemInfo);
}

void MainWindow::displayListViewInfoDish(const QModelIndex &index) {
    std::list<Dish *>::iterator item = itemForm->avaliableDish.begin();
    QString itemInfo;

    std::advance(item, index.row());

    infoWindowType = DISH;

    itemInfo += "Name: " + QString::fromStdString((*item)->getName()) + "\n";
    itemInfo += "Price: " + QString::number((*item)->getPrice()) + "\n";
    itemInfo += "Mass: " + QString::number((*item)->getMass()) + "\n";
    itemInfo += "Fats: " + QString::number((*item)->getFats()) + "\n";
    itemInfo += "Proteins: " + QString::number((*item)->getProteins()) + "\n";
    itemInfo += "Carbohydrates: " + QString::number((*item)->getCarbohydrates()) + "\n";
    itemInfo += "Calories: " + QString::number((*item)->getCalories()) + "\n\n";
    itemInfo += "Amount of people: " + QString::number((*item)->getAmountOfPeople()) + "\n\n";
    itemInfo += "Ingridients:\n";

    for ( auto& entry: (*item)->getIngridientMap() ) {
        itemInfo += QString::fromStdString(entry.first.getName()) + " (";
        itemInfo += QString::number(entry.second) + ")\n";
    }

    ui->textEdit_1->setText(itemInfo);
}
