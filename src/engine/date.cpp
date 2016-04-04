#include <date.hpp>
#include <debug.hpp>
#include <errors.hpp>

const uint32_t Date::highDays[] = {1, 3, 5, 7, 8, 10, 12};

const uint32_t Date::lowDays[] = {4, 6, 9, 11};

uint32_t Date::februaryDays(int32_t year) const {
    if ( year % 4 != 0 ) {
        return NOT_LEAP_DAYS;
    }

    if ( year % 100 != 0 ) {
        return LEAP_DAYS;
    }

    if ( year % 400 != 0 ) {
        return NOT_LEAP_DAYS;
    }

    return LEAP_DAYS;
}

bool Date::dayCorrect(uint32_t day) const {
    if ( day < 1 ) {
        return false;
    }

    for ( int32_t i = 0; i < HIGH_MOUNTHS_QUANTITY; i++ ) {
        if ( mounth == highDays[i] && day > HIGH_MOUNTHS_DAYS ) {
            return false;
        }
    }
    for ( int32_t i = 0; i < LOW_MOUNTHS_QUANTITY; i++ ) {
        if ( mounth == lowDays[i] && day > LOW_MOUNTHS_DAYS ) {
            return false;
        }
    }
    if ( mounth == FEBRUARY && day > februaryDays(year) ) {
        return false;
    }

    return true;
}

bool Date::mounthCorrect(uint32_t mounth) const {
    if ( mounth < 1 || mounth > 12 ) {
        return false;
    }

    return true;
}

bool Date::yearCorrect(int32_t year) const {
    if ( year == 0 ) {
        return false;
    }

    return true;
}

Date::Date(uint32_t day, uint32_t mounth, int32_t year) {
    if ( !yearCorrect(year) ) {
        PRINT_ERR("Date wrong year [" << year << "]");

        throw WrongYear();
    }
    this->year = year;

    if ( !mounthCorrect(mounth) ) {
        PRINT_ERR("Date wrong mounth [" << mounth << "]");

        throw WrongMounth();
    }
    this->mounth = mounth;

    setDay(day);

    PRINT_OBJ("Date \"" << *this << "\" created");
}

Date::~Date(void) {
    PRINT_OBJ("Date \"" << *this << "\" destroyed");
}

void Date::setDay(uint32_t day) {
    if ( !dayCorrect(day) ) {
        PRINT_ERR("Date wrong day [" << day << "]");

        throw WrongDay();
    }
    this->day = day;

    PRINT_INFO("Date day changed to " << day);
}

void Date::setMounth(uint32_t mounth) {
    if ( !mounthCorrect(mounth) || (mounth == FEBRUARY && day > februaryDays(year)) ) {
        PRINT_ERR("Date wrong mounth [" << mounth << "]");

        throw WrongMounth();
    }
    this->mounth = mounth;

    PRINT_INFO("Date mounth changed to " << mounth);
}

void Date::setYear(int32_t year) {
    if ( !yearCorrect(year) || (mounth == FEBRUARY && day > februaryDays(year)) ) {
        PRINT_ERR("Date wrong year [" << year << "]");

        throw WrongYear();
    }
    this->year = year;

    PRINT_INFO("Date year changed to " << year);
}

uint32_t Date::getDay(void) const {
    return day;
}

uint32_t Date::getMounth(void) const {
    return mounth;
}

int32_t Date::getYear(void) const {
    return year;
}

std::ostream& operator<<(std::ostream& out, const Date& date) {
    out << date.getDay() << "." << date.getMounth() << "." << date.getYear();

    return out;
}
