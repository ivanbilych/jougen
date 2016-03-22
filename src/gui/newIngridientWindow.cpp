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

    ui->lineEdit_2->setDisabled(true);

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

    PRINT_DEBUG("New item/food accepted");
}

void NewIngridientWindow::on_buttonBox_1_rejected() {
    this->hide();

    PRINT_DEBUG("New item/food rejected");
}

Item* NewIngridientWindow::createNewItem(void) {
    return new Item(ui->lineEdit_1->text().toStdString(),
                    (!ui->comboBox_1->currentText().toStdString().compare("gram") ? 1 : ui->lineEdit_2->text().toLong()),
                    ui->lineEdit_4->text().toLong(),
                    static_cast<Item::MeasureType>(ui->comboBox_1->currentIndex()));
}

Food* NewIngridientWindow::createNewFood(void) {
    return new Food(ui->lineEdit_1->text().toStdString(),
                    (!ui->comboBox_1->currentText().toStdString().compare("gram") ? 1 : ui->lineEdit_2->text().toLong()),
                    ui->lineEdit_4->text().toLong(),
                    static_cast<Item::MeasureType>(ui->comboBox_1->currentIndex()),
                    ui->lineEdit_3->text().toLong(),
                    ui->lineEdit_5->text().toLong(),
                    ui->lineEdit_6->text().toLong(),
                    ui->lineEdit_7->text().toLong());
}

void NewIngridientWindow::on_radioButton_1_clicked() {
    ui->lineEdit_3->setDisabled(false);
    ui->lineEdit_5->setDisabled(false);
    ui->lineEdit_6->setDisabled(false);
    ui->lineEdit_7->setDisabled(false);
}

void NewIngridientWindow::on_radioButton_2_clicked() {
    ui->lineEdit_3->setDisabled(true);
    ui->lineEdit_5->setDisabled(true);
    ui->lineEdit_6->setDisabled(true);
    ui->lineEdit_7->setDisabled(true);
}

void NewIngridientWindow::on_comboBox_1_currentIndexChanged(const QString &arg1) {
    if ( !arg1.toStdString().compare("gram") ) {
        ui->lineEdit_2->setDisabled(true);
    } else {
        ui->lineEdit_2->setDisabled(false);
    }

    PRINT_DEBUG(arg1.toStdString() << " selected");
}
