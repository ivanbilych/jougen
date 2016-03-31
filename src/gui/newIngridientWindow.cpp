#include <debug.hpp>

#include <newIngridientWindow.hpp>
#include "ui_newIngridientWindow.h"

NewIngridientWindow::NewIngridientWindow(QWidget* parent) :
    QDialog {parent},
    ui {new Ui::NewIngridientWindow},
    measureList {QStringList()} {

    setupMeasureList();
    ui->lineEdit_2->setDisabled(true);

    PRINT_OBJ("NewIngridientWindow created");
}

NewIngridientWindow::NewIngridientWindow(Item* item, QWidget* parent) :
    QDialog {parent},
    ui {new Ui::NewIngridientWindow},
    measureList {QStringList()},
    editMode {true},
    editedItem {item} {

    setupMeasureList();
    applyItemStats(item);
    this->setWindowTitle("Edit item");

    PRINT_OBJ("Existed item edit window created");
}

NewIngridientWindow::NewIngridientWindow(Food* food, QWidget* parent) :
    QDialog {parent},
    ui {new Ui::NewIngridientWindow},
    measureList {QStringList()},
    editMode {true},
    editedItem {food} {

    setupMeasureList();
    applyFoodStats(food);
    this->setWindowTitle("Edit food");

    PRINT_OBJ("Existed food edit window created");
}

NewIngridientWindow::~NewIngridientWindow() {
    delete ui;

    PRINT_OBJ("NewIngridientWindow destroyed");
}

void NewIngridientWindow::on_buttonBox_1_accepted() {
    if ( editMode ) {
        if ( ui->radioButton_1->isChecked() ) {
            editFood(dynamic_cast<Food*>(editedItem));
        } else if ( ui->radioButton_2->isChecked() ) {
            editItem(editedItem);
        }
    } else {
        if ( ui->radioButton_1->isChecked() ) {
            emit foodObjectReady(createNewFood());
        } else if ( ui->radioButton_2->isChecked() ) {
            emit itemObjectReady(createNewItem());
        }
    }

    this->hide();

    PRINT_DEBUG("New item/food accepted");
}

void NewIngridientWindow::on_buttonBox_1_rejected() {
    this->hide();

    PRINT_DEBUG("New item/food rejected");
}

void NewIngridientWindow::setupMeasureList(void) {
    const std::string* names = Item::getItemMeasureTypeNamesList();

    ui->setupUi(this);

    for ( int i = 0; !names[i].empty(); i++ ) {
        measureList.append(QString::fromStdString(names[i]));
    }

    ui->comboBox_1->addItems(measureList);
}

void NewIngridientWindow::applyItemStats(Item* item) {
    ui->lineEdit_1->setText(QString::fromStdString(item->getName()));
    ui->lineEdit_1->setDisabled(true);
    ui->comboBox_1->setCurrentIndex(static_cast<int>(item->getUnitType()));
    if ( item->getUnitType() != Item::GRAM ) {
        ui->lineEdit_2->setText(QString::number(item->getMass()));
    } else {
        ui->lineEdit_2->setDisabled(true);
    }
    ui->lineEdit_4->setText(QString::number(item->getPrice()));

    on_radioButton_2_clicked();
    ui->radioButton_2->setChecked(true);
    ui->radioButton_1->setDisabled(true);
}

void NewIngridientWindow::applyFoodStats(Food* food) {
    ui->lineEdit_1->setText(QString::fromStdString(food->getName()));
    ui->lineEdit_1->setDisabled(true);
    ui->comboBox_1->setCurrentIndex(static_cast<int>(food->getUnitType()));
    if ( food->getUnitType() != Item::GRAM ) {
        ui->lineEdit_2->setText(QString::number(food->getMass()));
    } else {
        ui->lineEdit_2->setDisabled(true);
    }
    ui->lineEdit_4->setText(QString::number(food->getPrice()));
    ui->lineEdit_3->setText(QString::number(food->getFats()));
    ui->lineEdit_5->setText(QString::number(food->getProteins()));
    ui->lineEdit_6->setText(QString::number(food->getCarbohydrates()));
    ui->lineEdit_7->setText(QString::number(food->getCalories()));

    ui->radioButton_1->setChecked(true);
    ui->radioButton_2->setDisabled(true);
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

void NewIngridientWindow::editItem(Item* item) {
    if ( !ui->comboBox_1->currentText().toStdString().compare("gram") ) {
        item->setItemMass(1);
    } else {
        item->setItemMass(ui->lineEdit_2->text().toLong());
    }
    item->setItemPrice(ui->lineEdit_4->text().toLong());
    item->setItemUnitType(static_cast<Item::MeasureType>(ui->comboBox_1->currentIndex()));
}

void NewIngridientWindow::editFood(Food* food) {
    editItem(food);
    food->setItemFats(ui->lineEdit_3->text().toLong());
    food->setItemProteins(ui->lineEdit_5->text().toLong());
    food->setItemCarbohydrates(ui->lineEdit_6->text().toLong());
    food->setItemCalories(ui->lineEdit_7->text().toLong());
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

void NewIngridientWindow::on_comboBox_1_currentIndexChanged(const QString& arg1) {
    if ( !arg1.toStdString().compare("gram") ) {
        ui->lineEdit_2->setDisabled(true);
    } else {
        ui->lineEdit_2->setDisabled(false);
    }

    PRINT_DEBUG(arg1.toStdString() << " selected");
}
