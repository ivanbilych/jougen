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
    if ( ui->radioButton_1->isChecked() ) {
        emit foodObjectReady(createNewFood());
    } else if ( ui->radioButton_2->isChecked() ) {
        emit itemObjectReady(createNewItem());
    }

    this->hide();

    PRINT_DEBUG("New dish rejected");
}

void NewIngridientWindow::on_buttonBox_1_rejected() {
    this->hide();

    PRINT_DEBUG("New dish rejected");
}

Item* NewIngridientWindow::createNewItem(void) {
    return new Item(ui->lineEdit_1->text().toStdString(),
                    ui->lineEdit_2->text().toLong(),
                    ui->lineEdit_4->text().toLong(),
                    static_cast<Item::MeasureType>(ui->comboBox_1->currentIndex()));
}

Food* NewIngridientWindow::createNewFood(void) {
    return new Food(ui->lineEdit_1->text().toStdString(),
                    ui->lineEdit_2->text().toLong(),
                    ui->lineEdit_4->text().toLong(),
                    static_cast<Item::MeasureType>(ui->comboBox_1->currentIndex()),
                    ui->lineEdit_3->text().toLong(),
                    ui->lineEdit_5->text().toLong(),
                    ui->lineEdit_6->text().toLong(),
                    ui->lineEdit_7->text().toLong());
}
