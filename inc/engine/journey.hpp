#ifndef JOURNEY_H
#define JOURNEY_H

#include <common.hpp>
#include <day.hpp>
#include <peopleStats.hpp>

#include <iostream>
#include <string>

class Journey : public PeopleStats<Day> {
    public:
        Journey(std::string name, const Day& day);
        ~Journey(void);

        Journey& operator=(const Journey& right);
};

std::ostream& operator<<(std::ostream& out, const Journey& journey);

#endif // JOURNEY_H
