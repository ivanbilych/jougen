#include <journey.hpp>
#include <engineLimits.hpp>
#include <debug.hpp>
#include <errors.hpp>

Journey::Journey(std::string name, const Day& day) :
        PeopleStats<Day>(name, JOURNEY_MIN_MASS, JOURNEY_MAX_MASS, JOURNEY_MIN_PRICE, JOURNEY_MAX_PRICE, JOURNEY_MIN_FATS, JOURNEY_MAX_FATS, JOURNEY_MIN_PROTEINS, JOURNEY_MAX_PROTEINS, JOURNEY_MIN_CARBOHYDRATES, JOURNEY_MAX_CARBOHYDRATES, JOURNEY_MIN_CALORIES, JOURNEY_MAX_CALORIES, JOURNEY_MIN_AMOUNT_OF_DAYS, JOURNEY_MAX_AMOUNT_OF_DAYS, JOURNEY_MIN_AMOUNT_OF_PEOPLE, JOURNEY_MAX_AMOUNT_OF_PEOPLE) {
    setAmountOfPeople(day.getAmountOfPeople());

    addItem(day);

    PRINT_OBJ("Journey " << NAME_ID << " created for " << getAmountOfPeople() << " people");
}

Journey::~Journey(void) {
    PRINT_OBJ("Journey " << NAME_ID << " destroyed");
}

std::ostream& operator<<(std::ostream& out, const Journey& journey) {
#ifdef DEBUG
    std::list<Day> days = journey.getList();

    out << dynamic_cast<const PeopleStats<Day>&>(journey) << std::endl;
    out << "        DAYS (" << days.size() << "):" << std::endl;
    out << "        >>> >>> >>>" << std::endl;

    for ( std::list<Day>::iterator it = days.begin(); it != days.end(); it++ ) {
        out << "        day " << *it << std::endl;
    }
    out << "        <<< <<< <<<";
#else
    out << journey.getName();
#endif

    return out;
}
