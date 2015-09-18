#ifndef DAY_H
#define DAY_H

#include <iostream>
#include <string>

#include <common.h>
#include <peopleStats.h>
#include <meal.h>
#include <date.h>

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
