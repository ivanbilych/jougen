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
    delete foodStringList;
    delete itemListModel;

    PRINT_OBJ("NewDishWindow destroyed");
}

void NewDishWindow::on_buttonBox_1_accepted() {
    if ( dishFoodList.size() ) {
        emit itemObjectReady(createNewDish());
    }
    this->hide();

    PRINT_DEBUG("New dish accepted");
}

void NewDishWindow::on_buttonBox_1_rejected() {
    this->hide();

    PRINT_DEBUG("New dish rejected");
}

void NewDishWindow::fillItemList(std::list<Item *> *itemsList) {
    avaliableItemsList = itemsList;

    for ( auto& entry: *itemsList ) {
        if ( dynamic_cast<Food *>(entry) ) {
            foodStringList->append(QString::fromStdString(entry->getName()));
        } else {
            foodStringList->append(QString::fromStdString(entry->getName())+QString(" (item)"));
        }
    }

    itemListModel->setStringList(*foodStringList);
}

Dish* NewDishWindow::createNewDish(void) {
    std::list<Item *>::iterator item = dishFoodList.begin();
    uint64_t amountOfPeople = static_cast<uint64_t>(ui->lineEdit_2->text().toLong());
    int pos_y = 0;

    if ( amountOfPeople < 1 ) {
        amountOfPeople = 1;
    }

    newDish = new Dish(ui->lineEdit_1->text().toStdString(),
                       *dynamic_cast<Food *>(*item),
                       static_cast<uint64_t>(ui->tableWidget_1->item(pos_y, 1)->text().toLong()),
                       amountOfPeople);
    pos_y += 1;
    std::advance(item, 1);

    for ( ; item != dishFoodList.end(); item++ ) {
        newDish->addFood(*dynamic_cast<Food *>(*item),
                         static_cast<uint64_t>(ui->tableWidget_1->item(pos_y, 1)->text().toLong()));
        pos_y += 1;
    }

    return newDish;
}

void NewDishWindow::on_pushButton_1_clicked() {
    QModelIndexList selected = ui->listView_1->selectionModel()->selectedIndexes();

    if ( !selected.isEmpty() ) {
        std::list<Item *>::iterator item = avaliableItemsList->begin();

        std::advance(item, selected.first().row());

        if ( std::find(dishFoodList.begin(), dishFoodList.end(), *item) == dishFoodList.end() && dynamic_cast<Food *>(*item) ) {
            int rowCount = ui->tableWidget_1->rowCount();

            dishFoodList.push_back(*item);

            ui->tableWidget_1->setRowCount(rowCount+1);
            ui->tableWidget_1->setItem(rowCount, 0, new QTableWidgetItem(QString::fromStdString((*item)->getName())));
            ui->tableWidget_1->setItem(rowCount, 1, new QTableWidgetItem(QString("1")));
        }
   }
}

void NewDishWindow::on_pushButton_2_clicked() {
    if ( ui->tableWidget_1->currentRow() != -1 ) {
        std::list<Item *>::iterator item = dishFoodList.begin();
        int currentRow = ui->tableWidget_1->currentRow();

        std::advance(item, currentRow);
        dishFoodList.remove(*item);

        ui->tableWidget_1->removeRow(currentRow);
    }
}
