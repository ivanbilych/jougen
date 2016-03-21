#include <debug.hpp>

#include <newDishWindow.hpp>
#include "ui_newDishWindow.h"

NewDishWindow::NewDishWindow(QWidget *parent) :
    QDialog {parent},
    ui {new Ui::NewDishWindow},
    foodStringList {new QStringList},
    itemListModel {new QStringListModel {*foodStringList, NULL}} {

    ui->setupUi(this);

    ui->listView_1->setModel(itemListModel);

    PRINT_OBJ("NewDishWindow created");
}

NewDishWindow::~NewDishWindow() {
    delete ui;

    PRINT_OBJ("NewDishWindow destroyed");
}

void NewDishWindow::on_buttonBox_1_accepted() {
    emit itemObjectReady(createNewDish());

    this->hide();
}

void NewDishWindow::on_buttonBox_1_rejected() {
    this->hide();
}

void NewDishWindow::fillItemList(std::list<Item *> *itemsList) {
    for ( auto& entry: *itemsList ) {
        foodStringList->append(QString::fromStdString(entry->getName()));
    }

    itemListModel->setStringList(*foodStringList);
}

Dish* NewDishWindow::createNewDish(void) {
    PRINT_DEBUG("NewDishWindow::createNewDish(void)");
    return NULL;
}
