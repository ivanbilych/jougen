#include <debug.hpp>

#include <mainWindow.hpp>
#include "ui_mainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow {parent},
    ui {new Ui::MainWindow},
    newIngridientWindow {new NewIngridientWindow},
    newDishWindow {new NewDishWindow},
    itemStringList {new QStringList},
    dishStringList {new QStringList},
    itemListModel {new QStringListModel {*itemStringList, NULL}},
    dishListModel {new QStringListModel {*dishStringList, NULL}} {

    ui->setupUi(this);

    ui->listView_1->setModel(itemListModel);
    ui->listView_2->setModel(dishListModel);

    itemStringList->append("Apple");
    itemStringList->append("Potato");
    itemStringList->append("Rice");
    itemStringList->append("Nails");

    dishStringList->append("Apple pie");
    dishStringList->append("Fired Potato");
    dishStringList->append("Rice with spices");

    itemListModel->setStringList(*itemStringList);
    dishListModel->setStringList(*dishStringList);

    PRINT_OBJ("MainWindow created");
}

MainWindow::~MainWindow() {
    delete ui;
    delete newIngridientWindow;
    delete newDishWindow;
    delete itemStringList;
    delete dishStringList;
    delete itemListModel;
    delete dishListModel;

    PRINT_OBJ("MainWindow destroyed");
}

void MainWindow::closeEvent(QCloseEvent *event) {
    newIngridientWindow->close();
    newDishWindow->close();
}

void MainWindow::on_pushButton_1_clicked() {
    newIngridientWindow->show();
}

void MainWindow::on_pushButton_3_clicked() {
    newDishWindow->show();
}

void MainWindow::on_pushButton_5_clicked() {
    if ( infoWindowType == ITEM ) {
        newIngridientWindow->show();
    } else if ( infoWindowType == FOOD ) {
        newIngridientWindow->show();
    } else if ( infoWindowType == DISH ) {
        newDishWindow->show();
    }
}

void MainWindow::on_listView_1_clicked(const QModelIndex &index) {
    infoWindowType = ITEM;
}

void MainWindow::on_listView_2_clicked(const QModelIndex &index) {
    infoWindowType = DISH;
}
