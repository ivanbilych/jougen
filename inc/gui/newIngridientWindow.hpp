#ifndef NEWINGRIDIENTWINDOW_H
#define NEWINGRIDIENTWINDOW_H

#include <item.hpp>
#include <food.hpp>

#include <QDialog>

namespace Ui {
    class NewIngridientWindow;
}

class NewIngridientWindow : public QDialog {
    Q_OBJECT

public:
    explicit NewIngridientWindow(QWidget* parent = 0);
    explicit NewIngridientWindow(Item* item, QWidget* parent = 0);
    explicit NewIngridientWindow(Food* food, QWidget* parent = 0);
    ~NewIngridientWindow();

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
    Ui::NewIngridientWindow* ui;
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
};

#endif // NEWINGRIDIENTWINDOW_H
