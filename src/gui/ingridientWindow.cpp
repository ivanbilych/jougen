#include <convert.hpp>
#include <errors.hpp>
#include <debug.hpp>

#include <QMessageBox>
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
    bool result = false;

    if ( editMode ) {
        result = buttonBoxAcceptedEditMode();
    } else {
        result = buttonBoxAcceptedNewMode();
    }

    if ( !result ) {
        return;
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

    QString name = ui->lineEdit_1->text();
    QString mass = ui->lineEdit_2->text();
    QString price = ui->lineEdit_4->text();

    if ( name.isEmpty() ) {
        PRINT_ERR("Ingridient name could not be empty");

        throw EmptyIngridientNameException();
    }

    if ( mass.isEmpty() ) {
        PRINT_ERR("Ingridient mass could not be empty");

        throw EmptyIngridientMassException();
    }

    if ( price.isEmpty() ) {
        PRINT_ERR("Ingridient price could not be empty");

        throw EmptyIngridientPriceException();
    }

    return new Item(name.toStdString(), (!ui->comboBox_1->currentText().toStdString().compare("kg") ? 1 : QStringToMass(mass)),
                    QStringToPrice(price), static_cast<Item::MeasureType>(ui->comboBox_1->currentIndex()));
}

Food* IngridientWindow::createNewFood(void) {
    bool isKg = !ui->comboBox_1->currentText().toStdString().compare("kg");

    PRINT_DEBUG("Creating new food");

    QString name = ui->lineEdit_1->text();
    QString mass = ui->lineEdit_2->text();
    QString price = ui->lineEdit_4->text();
    QString fats = ui->lineEdit_3->text();
    QString proteins = ui->lineEdit_5->text();
    QString carbohydrates = ui->lineEdit_6->text();
    QString calories = ui->lineEdit_7->text();

    if ( name.isEmpty() ) {
        PRINT_ERR("Food name could not be empty");

        throw EmptyIngridientNameException();
    }

    if ( mass.isEmpty() && !isKg ) {
        PRINT_ERR("Food mass could not be empty");

        throw EmptyIngridientMassException();
    }

    if ( price.isEmpty() ) {
        PRINT_ERR("Food price could not be empty");

        throw EmptyIngridientPriceException();
    }

    if ( fats.isEmpty() ) {
        PRINT_ERR("Food fats could not be empty");

        throw EmptyIngridientFatsException();
    }

    if ( proteins.isEmpty() ) {
        PRINT_ERR("Food proteins could not be empty");

        throw EmptyIngridientProteinsException();
    }

    if ( carbohydrates.isEmpty() ) {
        PRINT_ERR("Food carbohydrates could not be empty");

        throw EmptyIngridientCarbohydratesException();
    }

    if ( calories.isEmpty() ) {
        PRINT_ERR("Food calories could not be empty");

        throw EmptyIngridientCaloriesException();
    }

    return new Food(name.toStdString(), isKg ? 1 : QStringToMass(mass),
                    QStringToPrice(price), static_cast<Item::MeasureType>(ui->comboBox_1->currentIndex()),
                    QStringToFats(fats),
                    QStringToProteins(proteins),
                    QStringToCarbohydrates(carbohydrates),
                    QStringToCalories(calories));
}

void IngridientWindow::editItem(Item* item) {
    PRINT_DEBUG("Editing item");

    if ( !ui->comboBox_1->currentText().toStdString().compare("kg") ) {
        item->setItemMass(1);
    } else {
        item->setItemMass(QStringToMass(ui->lineEdit_2->text()));
    }
    item->setItemPrice(QStringToPrice(ui->lineEdit_4->text()));
    item->setItemUnitType(static_cast<Item::MeasureType>(ui->comboBox_1->currentIndex()));
}

void IngridientWindow::editFood(Food* food) {
    PRINT_DEBUG("Editing food");

    editItem(food);
    food->setItemFats(QStringToFats(ui->lineEdit_3->text()));
    food->setItemProteins(QStringToProteins(ui->lineEdit_5->text()));
    food->setItemCarbohydrates(QStringToCarbohydrates(ui->lineEdit_6->text()));
    food->setItemCalories(QStringToCalories(ui->lineEdit_7->text()));
}

bool IngridientWindow::buttonBoxAcceptedEditMode(void) {
    bool isFood = ui->radioButton_1->isChecked();

    try {
        if ( isFood ) {
            editFood(dynamic_cast<Food*>(editedItem));
        } else {
            editItem(editedItem);
        }
    } catch ( IngridientWindowException e ) {
        QMessageBox msgBox;

        PRINT_ERR("Wrong value provided");

        msgBox.setText("Wrong value provided");
        msgBox.exec();

        return false;
    } catch ( EngineException e ) {
        QMessageBox msgBox;

        PRINT_ERR("Engine calculation error");

        msgBox.setText("Engine calculation error");
        msgBox.exec();

        return false;
    }

    return true;
}

bool IngridientWindow::buttonBoxAcceptedNewMode(void) {
    bool isFood = ui->radioButton_1->isChecked();
    Food* newFood = nullptr;
    Item* newItem = nullptr;

    try {
        if ( isFood ) {
            newFood = createNewFood();
        } else {
            newItem = createNewItem();
        }
    } catch ( IngridientWindowException e ) {
        QMessageBox msgBox;

        PRINT_ERR("Wrong value provided");

        msgBox.setText("Wrong value provided");
        msgBox.exec();

        return false;
    } catch ( EngineException e ) {
        QMessageBox msgBox;

        PRINT_ERR("Engine calculation error");

        msgBox.setText("Engine calculation error");
        msgBox.exec();

        return false;
    }

    if ( isFood ) {
        emit foodObjectReady(newFood);
    } else {
        emit itemObjectReady(newItem);
    }

    return true;
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
    if ( !arg1.toStdString().compare("kg") ) {
        ui->lineEdit_2->setDisabled(true);
    } else {
        ui->lineEdit_2->setDisabled(false);
    }

    PRINT_DEBUG(arg1.toStdString() << " selected");
}
