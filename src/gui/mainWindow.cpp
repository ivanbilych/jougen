#include <debug.hpp>
#include <dish.hpp>
#include <food.hpp>
#include <item.hpp>

#include <mainWindow.hpp>
#include "ui_mainWindow.h"

#include <QString>
#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow {parent},
    ui {new Ui::MainWindow},
    itemStringList {new QStringList},
    dishStringList {new QStringList},
    itemListModel {new QStringListModel {*itemStringList, NULL}},
    dishListModel {new QStringListModel {*dishStringList, NULL}},
    ingridients {new Ingridients} {

    ui->setupUi(this);

    ui->listView_1->setModel(itemListModel);
    ui->listView_2->setModel(dishListModel);

    redrawItemList();

    PRINT_OBJ("MainWindow created");
}

MainWindow::~MainWindow() {
    delete ui;
    delete itemStringList;
    delete dishStringList;
    delete itemListModel;
    delete dishListModel;
    delete ingridients;

    PRINT_OBJ("MainWindow destroyed");
}

void MainWindow::on_pushButton_1_clicked() {
    IngridientWindow ingridientWindow;

    QObject::connect(&ingridientWindow, SIGNAL(itemObjectReady(Item*)), this, SLOT(addNewItemObject(Item*)));
    QObject::connect(&ingridientWindow, SIGNAL(foodObjectReady(Food*)), this, SLOT(addNewFoodObject(Food*)));

    ingridientWindow.exec();
}

void MainWindow::on_pushButton_2_clicked() {
    QModelIndexList selected = ui->listView_1->selectionModel()->selectedIndexes();

    if ( !selected.isEmpty() ) {
        int row = selected.first().row();

        const QModelIndex index = itemListModel->index(row?row-1:0);
        std::list<Item*>::iterator item = ingridients->avaliableItems.begin();

        std::advance(item, row);

        delete *item;

        redrawItemList();

        if ( itemStringList->size() ) {
            ui->listView_1->setCurrentIndex(index);
            displayListViewInfoItem(index);
        } else {
            ui->textEdit_1->clear();
        }
   }
}

void MainWindow::on_pushButton_3_clicked() {
    DishWindow dishWindow;

    QObject::connect(&dishWindow, SIGNAL(itemObjectReady(Dish*)), this, SLOT(addNewDishObject(Dish*)));
    QObject::connect(this, SIGNAL(newDishRequest(std::list<Item*>*)), &dishWindow, SLOT(fillItemList(std::list<Item*>*)));

    emit newDishRequest(&ingridients->avaliableItems);

    dishWindow.exec();
}

void MainWindow::on_pushButton_4_clicked() {
    QModelIndexList selected = ui->listView_2->selectionModel()->selectedIndexes();

    if ( !selected.isEmpty() ) {
        int row = selected.first().row();

        const QModelIndex index = dishListModel->index(row?row-1:0);
        std::list<Dish*>::iterator dish = ingridients->avaliableDish.begin();

        std::advance(dish, row);

        delete *dish;

        redrawDishList();

        if ( dishStringList->size() ) {
            ui->listView_2->setCurrentIndex(index);
            displayListViewInfoDish(index);
        } else {
            ui->textEdit_1->clear();
        }
   }
}

void MainWindow::on_pushButton_5_clicked() {
    if ( infoWindowType == ITEM || infoWindowType == FOOD ) {
        QModelIndexList selected = ui->listView_1->selectionModel()->selectedIndexes();

        if ( !selected.isEmpty() ) {
            editItem(selected);
        }
    } else if ( infoWindowType == DISH ) {
        QModelIndexList selected = ui->listView_2->selectionModel()->selectedIndexes();

        if ( !selected.isEmpty() ) {
            editDish(selected);
        }
    }
}

void MainWindow::on_listView_1_clicked(const QModelIndex& index) {
    displayListViewInfoItem(index);

    PRINT_DEBUG("Clicked item/food: " << index.data().toString().toStdString());
}

void MainWindow::on_listView_2_clicked(const QModelIndex& index) {
    displayListViewInfoDish(index);

    PRINT_DEBUG("Clicked dish: " << index.data().toString().toStdString());
}

void MainWindow::on_listView_1_entered(const QModelIndex& index) {
    displayListViewInfoItem(index);

    PRINT_DEBUG("Entered item/food: " << index.data().toString().toStdString());
}

void MainWindow::on_listView_2_entered(const QModelIndex& index) {
    displayListViewInfoDish(index);

    PRINT_DEBUG("Entered dish: " << index.data().toString().toStdString());
}

void MainWindow::addNewItemObject(Item* item) {
    QModelIndex index;

    itemStringList->append(QString::fromStdString(item->getName()));
    itemListModel->setStringList(*itemStringList);

    ingridients->avaliableItems.push_back(item);

    index = itemListModel->index(ingridients->avaliableItems.size()-1);
    ui->listView_1->setCurrentIndex(index);
    displayListViewInfoItem(index);

    PRINT_DEBUG("New item added");
}

void MainWindow::addNewFoodObject(Food* food) {
    QModelIndex index;

    itemStringList->append(QString::fromStdString(food->getName()));
    itemListModel->setStringList(*itemStringList);

    ingridients->avaliableItems.push_back(food);

    index = itemListModel->index(ingridients->avaliableItems.size()-1);
    ui->listView_1->setCurrentIndex(index);
    displayListViewInfoItem(index);

    PRINT_DEBUG("New food added");
}

void MainWindow::addNewDishObject(Dish* dish) {
    dishStringList->append(QString::fromStdString(dish->getName()));
    dishListModel->setStringList(*dishStringList);

    ingridients->avaliableDish.push_back(dish);

    PRINT_DEBUG("New dish added");
}

void MainWindow::editItem(QModelIndexList& selected) {
    IngridientWindow* ingridientWindow;
    int row = selected.first().row();
    const QModelIndex index = itemListModel->index(row);

    std::list<Item*>::iterator item = ingridients->avaliableItems.begin();
    std::advance(item, row);

    ingridientWindow = (infoWindowType == ITEM) ? new IngridientWindow(*item) : new IngridientWindow(dynamic_cast<Food*>(*item));

    ingridientWindow->exec();

    delete ingridientWindow;

    displayListViewInfoItem(index);
}

void MainWindow::editDish(QModelIndexList& selected) {
    DishWindow* dishWindow;
    int row = selected.first().row();
    const QModelIndex index = dishListModel->index(row);

    std::list<Dish*>::iterator dish = ingridients->avaliableDish.begin();
    std::advance(dish, row);

    dishWindow = new DishWindow(*dish);

    QObject::connect(this, SIGNAL(newDishRequest(std::list<Item*>*)), dishWindow, SLOT(fillItemList(std::list<Item*>*)));

    emit newDishRequest(&ingridients->avaliableItems);
    dishWindow->exec();

    delete dishWindow;

    displayListViewInfoDish(index);
}

void MainWindow::displayListViewInfoItem(const QModelIndex& index) {
    std::list<Item*>::iterator item = ingridients->avaliableItems.begin();
    QString itemInfo;

    std::advance(item, index.row());

    if ( dynamic_cast<Food*>(*item) ) {
        infoWindowType = FOOD;
    } else {
        infoWindowType = ITEM;
    }

    itemInfo += "Name: " + QString::fromStdString((*item)->getName()) + "\n";
    itemInfo += "Price: " + QString::number((*item)->getPrice()) + "\n";
    itemInfo += "Mass: " + QString::number((*item)->getMass()) + "\n";
    itemInfo += "Unit: " + QString::fromStdString((*item)->getUnitTypeName()) + "\n";

    if ( infoWindowType == FOOD ) {
       itemInfo += "Fats: " + QString::number((*item)->getFats()) + " (in 100 g)\n";
       itemInfo += "Proteins: "+ QString::number((*item)->getProteins()) + " (in 100 g)\n";
       itemInfo += "Carbohydrates: " + QString::number((*item)->getCarbohydrates()) + " (in 100 g)\n";
       itemInfo += "Calories: " + QString::number((*item)->getCalories()) + " (in 100 g)\n";
    }

    ui->textEdit_1->setText(itemInfo);
}

void MainWindow::displayListViewInfoDish(const QModelIndex& index) {
    std::list<Dish*>::iterator item = ingridients->avaliableDish.begin();
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
        itemInfo += QString::fromStdString(entry.first->getName()) + " (";
        itemInfo += QString::number(entry.second) + " g)\n";
    }

    ui->textEdit_1->setText(itemInfo);
}

void MainWindow::redrawItemList(void) {
    PRINT_DEBUG("Redrawing items list");

    itemStringList->clear();

    for ( auto& entry: ingridients->avaliableItems ) {
        itemStringList->append(QString::fromStdString(entry->getName()));
    }
    itemListModel->setStringList(*itemStringList);

    redrawDishList();
}

void MainWindow::redrawDishList(void) {
    PRINT_DEBUG("Redrawing dish list");

    dishStringList->clear();

    for ( auto& entry: ingridients->avaliableDish ) {
        dishStringList->append(QString::fromStdString(entry->getName()));
    }
    dishListModel->setStringList(*dishStringList);
}

void MainWindow::on_actionAbout_triggered() {
    AboutWindow aboutWindow;

    aboutWindow.exec();
}

void MainWindow::on_actionOpen_triggered() {
    QString loadFile(QFileDialog::getOpenFileName(0, "Open File", "", "json (*.json);; binary (*)"));

    if ( !loadFile.isEmpty() ) {
        for ( std::list<Item*>::iterator it = ingridients->avaliableItems.begin(); it != ingridients->avaliableItems.end(); ) {
            std::list<Item*>::iterator oldit = it++;

            delete *oldit;
        }
        ingridients->avaliableItems.clear();
        ingridients->avaliableDish.clear();

        ingridients->loadData(loadFile);

        redrawItemList();
        ui->textEdit_1->clear();
    }
}

void MainWindow::on_actionSave_triggered() {
    QString saveFile(QFileDialog::getSaveFileName(0, "Save File", "", "json (*.json);; binary (*)"));

    if ( !saveFile.isEmpty() ) {
        ingridients->saveData(saveFile);
    }
}
