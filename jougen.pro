QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jougen
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -Wall

INCLUDEPATH += \
    inc \
    inc/engine \
    inc/gui

HEADERS += \
    inc/common.hpp \
    inc/debug.hpp \
    inc/errors.hpp \
    inc/engine/date.hpp \
    inc/engine/day.hpp \
    inc/engine/dish.hpp \
    inc/engine/engineLimits.hpp \
    inc/engine/food.hpp \
    inc/engine/item.hpp \
    inc/engine/journey.hpp \
    inc/engine/meal.hpp \
    inc/engine/peopleStats.hpp \
    inc/engine/stats.hpp \
    inc/gui/mainWindow.hpp \
    inc/gui/newIngridientWindow.hpp \
    inc/gui/newDishWindow.hpp

FORMS += \
    src/gui/mainWindow.ui \
    src/gui/newIngridientWindow.ui \
    src/gui/newDishWindow.ui

SOURCES += \
    src/jougen.cpp \
    src/engine/date.cpp \
    src/engine/day.cpp \
    src/engine/dish.cpp \
    src/engine/food.cpp \
    src/engine/item.cpp \
    src/engine/journey.cpp \
    src/engine/meal.cpp \
    src/engine/stats.cpp \
    src/gui/mainWindow.cpp \
    src/gui/newIngridientWindow.cpp \
    src/gui/newDishWindow.cpp
