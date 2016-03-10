#ifndef JOURNEY_H
#define JOURNEY_H

#include <iostream>
#include <string>

#include <common.hpp>
#include <peopleStats.hpp>
#include <day.hpp>

class Journey : public PeopleStats<Day> {
    public:
        Journey(std::string name, const Day& day);
        ~Journey(void);
        Journey& operator=(const Journey& right);
};

std::ostream& operator<<(std::ostream& out, const Journey& journey);

#endif // JOURNEY_H
