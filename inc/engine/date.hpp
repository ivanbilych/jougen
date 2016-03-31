#ifndef DATE_H
#define DATE_H

#include <common.hpp>

#include <iostream>

#define FEBRUARY               2
#define NOT_LEAP_DAYS         28
#define LEAP_DAYS             29
#define HIGH_MOUNTHS_DAYS     31
#define LOW_MOUNTHS_DAYS      30
#define HIGH_MOUNTHS_QUANTITY  7
#define LOW_MOUNTHS_QUANTITY   4

class Date {
    private:
        static const uint32_t highDays[];
        static const uint32_t lowDays[];
        uint32_t day;
        uint32_t mounth;
        int32_t year;

        uint32_t februaryDays(int32_t year) const;
        bool dayCorrect(uint32_t day) const;
        bool mounthCorrect(uint32_t mounth) const;
        bool yearCorrect(int32_t year) const;

    public:
        Date(uint32_t day, uint32_t mounth, int32_t year);
        ~Date(void);

        void setDay(uint32_t day);
        void setMounth(uint32_t mounth);
        void setYear(int32_t year);
        uint32_t getDay(void) const;
        uint32_t getMounth(void) const;
        int32_t getYear(void) const;
};

std::ostream& operator<<(std::ostream& out, const Date& date);

#endif // DATE_H
