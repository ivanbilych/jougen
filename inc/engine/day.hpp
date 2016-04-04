#ifndef DAY_H
#define DAY_H

#include <common.hpp>
#include <date.hpp>
#include <meal.hpp>
#include <peopleStats.hpp>

#include <iostream>
#include <string>

class Day : public PeopleStats<Meal> {
    private:
        Date date;

    public:
        Day(std::string name, const Date& date, const Meal& meal);
        ~Day(void);

        Day& operator=(const Day& right);

        Date getDate(void) const;
};

std::ostream& operator<<(std::ostream& out, const Day& day);

#endif // DAY_H
