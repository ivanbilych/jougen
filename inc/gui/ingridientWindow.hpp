#ifndef INGRIDIENTWINDOW_H
#define INGRIDIENTWINDOW_H

#include <item.hpp>
#include <food.hpp>

#include <QDialog>

namespace Ui {
    class IngridientWindow;
}

class IngridientWindow : public QDialog {
    Q_OBJECT

public:
    explicit IngridientWindow(QWidget* parent = 0);
    explicit IngridientWindow(Item* item, QWidget* parent = 0);
    explicit IngridientWindow(Food* food, QWidget* parent = 0);
    ~IngridientWindow();

signals:
    void itemObjectReady(Item* item);
    void foodObjectReady(Food* food);

private slots:
    void on_buttonBox_1_accepted();
    void on_buttonBox_1_rejected();
    void on_radioButton_1_clicked();
    void on_radioButton_2_clicked();
    void on_comboBox_1_currentIndexChanged(const QString& arg1);

private:
    Ui::IngridientWindow* ui;
    QStringList measureList {};
    bool editMode {false};
    Item* editedItem {};

    void setupMeasureList(void);
    void applyItemStats(Item* item);
    void applyFoodStats(Food* food);
    Item* createNewItem(void);
    Food* createNewFood(void);
    void editItem(Item* item);
    void editFood(Food* food);
    bool buttonBoxAcceptedEditMode(void);
    bool buttonBoxAcceptedNewMode(void);
};

#endif // INGRIDIENTWINDOW_H
