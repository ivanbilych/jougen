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

    ui->tableWidget_1->setColumnCount(2);

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
    avaliableItemsList = itemsList;

    for ( auto& entry: *itemsList ) {
        foodStringList->append(QString::fromStdString(entry->getName()));
    }

    itemListModel->setStringList(*foodStringList);
}

Dish* NewDishWindow::createNewDish(void) {
    return newDish;
}

void NewDishWindow::on_pushButton_1_clicked() {
    QModelIndexList selected = ui->listView_1->selectionModel()->selectedIndexes();

    if ( !selected.isEmpty() ) {
        std::list<Item *>::iterator item = avaliableItemsList->begin();

        std::advance(item, selected.first().row());

        if ( std::find(dishItemsList.begin(), dishItemsList.end(), *item) == dishItemsList.end() ) {
            QTableWidgetItem *newItem;
            dishItemsList.push_back(*item);

            newItem = new QTableWidgetItem(tr("%1").arg(QString::fromStdString((*item)->getName())));
            ui->tableWidget_1->setRowCount(ui->tableWidget_1->rowCount()+1);
            ui->tableWidget_1->setItem(ui->tableWidget_1->rowCount()-1, 0, newItem);
        }
   }
}

void NewDishWindow::on_pushButton_2_clicked() {

}
