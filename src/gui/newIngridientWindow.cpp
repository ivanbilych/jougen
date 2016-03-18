#include <debug.hpp>

#include <newIngridientWindow.hpp>
#include "ui_newIngridientWindow.h"

NewIngridientWindow::NewIngridientWindow(QWidget *parent) :
    QDialog {parent},
    ui {new Ui::NewIngridientWindow},
    measureList {QStringList()} {

    const std::string* names = Item::getItemMeasureTypeNamesList();

    ui->setupUi(this);

    for ( int i = 0; !names[i].empty(); i++ ) {
        measureList.append(QString::fromStdString(names[i]));
    }

    ui->comboBox_1->addItems(measureList);

    PRINT_OBJ("NewIngridientWindow created");
}

NewIngridientWindow::~NewIngridientWindow() {
    delete ui;

    PRINT_OBJ("NewIngridientWindow destroyed");
}

void NewIngridientWindow::on_buttonBox_1_accepted() {
    this->hide();
}

void NewIngridientWindow::on_buttonBox_1_rejected() {
    this->hide();
}
