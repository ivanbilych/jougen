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
    inc/engine/ingridients.hpp \
    inc/gui/mainWindow.hpp \
    inc/gui/ingridientWindow.hpp \
    inc/gui/dishWindow.hpp \
    inc/gui/aboutWindow.hpp

FORMS += \
    src/gui/mainWindow.ui \
    src/gui/ingridientWindow.ui \
    src/gui/dishWindow.ui \
    src/gui/aboutWindow.ui

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
    src/engine/ingridients.cpp \
    src/gui/mainWindow.cpp \
    src/gui/ingridientWindow.cpp \
    src/gui/dishWindow.cpp \
    src/gui/aboutWindow.cpp

copydata.commands = $(COPY_DIR) $$PWD/res/* $$OUT_PWD
first.depends = $(first) copydata

export(first.depends)
export(copydata.commands)

QMAKE_EXTRA_TARGETS += first copydata
