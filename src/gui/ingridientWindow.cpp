#include <convert.hpp>
#include <debug.hpp>

#include <ingridientWindow.hpp>
#include "ui_ingridientWindow.h"

IngridientWindow::IngridientWindow(QWidget* parent) :
    QDialog {parent},
    ui {new Ui::IngridientWindow},
    measureList {QStringList()} {

    setupMeasureList();
    ui->lineEdit_2->setDisabled(true);

    PRINT_OBJ("IngridientWindow created");
}

IngridientWindow::IngridientWindow(Item* item, QWidget* parent) :
    QDialog {parent},
    ui {new Ui::IngridientWindow},
    measureList {QStringList()},
    editMode {true},
    editedItem {item} {

    setupMeasureList();
    applyItemStats(item);
    this->setWindowTitle("Edit item");

    PRINT_OBJ("Existed item edit window created");
}

IngridientWindow::IngridientWindow(Food* food, QWidget* parent) :
    QDialog {parent},
    ui {new Ui::IngridientWindow},
    measureList {QStringList()},
    editMode {true},
    editedItem {food} {

    setupMeasureList();
    applyFoodStats(food);
    this->setWindowTitle("Edit food");

    PRINT_OBJ("Existed food edit window created");
}

IngridientWindow::~IngridientWindow() {
    delete ui;

    PRINT_OBJ("IngridientWindow destroyed");
}

void IngridientWindow::on_buttonBox_1_accepted() {
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

void IngridientWindow::on_buttonBox_1_rejected() {
    this->hide();

    PRINT_DEBUG("New item/food rejected");
}

void IngridientWindow::setupMeasureList(void) {
    const std::string* names = Item::getItemMeasureTypeNamesList();

    ui->setupUi(this);

    for ( int i = 0; !names[i].empty(); i++ ) {
        measureList.append(QString::fromStdString(names[i]));
    }

    ui->comboBox_1->addItems(measureList);
}

void IngridientWindow::applyItemStats(Item* item) {
    ui->lineEdit_1->setText(QString::fromStdString(item->getName()));
    ui->lineEdit_1->setDisabled(true);
    ui->comboBox_1->setCurrentIndex(static_cast<int>(item->getUnitType()));
    if ( item->getUnitType() != Item::KGRAM ) {
        ui->lineEdit_2->setText(massToQString(item->getMass()));
    } else {
        ui->lineEdit_2->setDisabled(true);
    }
    ui->lineEdit_4->setText(priceToQString(item->getPrice()));

    on_radioButton_2_clicked();
    ui->radioButton_2->setChecked(true);
    ui->radioButton_1->setDisabled(true);

    PRINT_DEBUG("All items stats are applied");
}

void IngridientWindow::applyFoodStats(Food* food) {
    ui->lineEdit_1->setText(QString::fromStdString(food->getName()));
    ui->lineEdit_1->setDisabled(true);
    ui->comboBox_1->setCurrentIndex(static_cast<int>(food->getUnitType()));
    if ( food->getUnitType() != Item::KGRAM ) {
        ui->lineEdit_2->setText(massToQString(food->getMass()));
    } else {
        ui->lineEdit_2->setDisabled(true);
    }
    ui->lineEdit_4->setText(priceToQString(food->getPrice()));
    ui->lineEdit_3->setText(fatsToQString(food->getFats()));
    ui->lineEdit_5->setText(proteinsToQString(food->getProteins()));
    ui->lineEdit_6->setText(carbohydratesToQString(food->getCarbohydrates()));
    ui->lineEdit_7->setText(caloriesToQString(food->getCalories()));

    ui->radioButton_1->setChecked(true);
    ui->radioButton_2->setDisabled(true);

    PRINT_DEBUG("All food stats are applied");
}

Item* IngridientWindow::createNewItem(void) {
    PRINT_DEBUG("Creating new item");

    return new Item(ui->lineEdit_1->text().toStdString(),
                    (!ui->comboBox_1->currentText().toStdString().compare("gram") ? 1 : ui->lineEdit_2->text().toLong()),
                    ui->lineEdit_4->text().toLong(),
                    static_cast<Item::MeasureType>(ui->comboBox_1->currentIndex()));
}

Food* IngridientWindow::createNewFood(void) {
    PRINT_DEBUG("Creating new food");

    return new Food(ui->lineEdit_1->text().toStdString(),
                    (!ui->comboBox_1->currentText().toStdString().compare("gram") ? 1 : ui->lineEdit_2->text().toLong()),
                    ui->lineEdit_4->text().toLong(),
                    static_cast<Item::MeasureType>(ui->comboBox_1->currentIndex()),
                    ui->lineEdit_3->text().toLong(),
                    ui->lineEdit_5->text().toLong(),
                    ui->lineEdit_6->text().toLong(),
                    ui->lineEdit_7->text().toLong());
}

void IngridientWindow::editItem(Item* item) {
    PRINT_DEBUG("Editing item");

    if ( !ui->comboBox_1->currentText().toStdString().compare("gram") ) {
        item->setItemMass(1);
    } else {
        item->setItemMass(ui->lineEdit_2->text().toLong());
    }
    item->setItemPrice(ui->lineEdit_4->text().toLong());
    item->setItemUnitType(static_cast<Item::MeasureType>(ui->comboBox_1->currentIndex()));
}

void IngridientWindow::editFood(Food* food) {
    PRINT_DEBUG("Editing food");

    editItem(food);
    food->setItemFats(ui->lineEdit_3->text().toLong());
    food->setItemProteins(ui->lineEdit_5->text().toLong());
    food->setItemCarbohydrates(ui->lineEdit_6->text().toLong());
    food->setItemCalories(ui->lineEdit_7->text().toLong());
}

void IngridientWindow::on_radioButton_1_clicked() {
    ui->lineEdit_3->setDisabled(false);
    ui->lineEdit_5->setDisabled(false);
    ui->lineEdit_6->setDisabled(false);
    ui->lineEdit_7->setDisabled(false);
}

void IngridientWindow::on_radioButton_2_clicked() {
    ui->lineEdit_3->setDisabled(true);
    ui->lineEdit_5->setDisabled(true);
    ui->lineEdit_6->setDisabled(true);
    ui->lineEdit_7->setDisabled(true);
}

void IngridientWindow::on_comboBox_1_currentIndexChanged(const QString& arg1) {
    if ( !arg1.toStdString().compare("gram") ) {
        ui->lineEdit_2->setDisabled(true);
    } else {
        ui->lineEdit_2->setDisabled(false);
    }

    PRINT_DEBUG(arg1.toStdString() << " selected");
}
