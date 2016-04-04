#include <day.hpp>
#include <debug.hpp>
#include <engineLimits.hpp>
#include <errors.hpp>

Day::Day(std::string name, const Date& date, const Meal& meal) :
    PeopleStats<Meal> {name, DAY_MIN_MASS, DAY_MAX_MASS, DAY_MIN_PRICE,
                       DAY_MAX_PRICE, DAY_MIN_FATS, DAY_MAX_FATS,
                       DAY_MIN_PROTEINS, DAY_MAX_PROTEINS,
                       DAY_MIN_CARBOHYDRATES, DAY_MAX_CARBOHYDRATES,
                       DAY_MIN_CALORIES, DAY_MAX_CALORIES,
                       DAY_MIN_AMOUNT_OF_MEAL, DAY_MAX_AMOUNT_OF_MEAL,
                       DAY_MIN_AMOUNT_OF_PEOPLE, DAY_MAX_AMOUNT_OF_PEOPLE},
    date {date} {

    setAmountOfPeople(meal.getAmountOfPeople());

    addItem(meal);

    PRINT_OBJ("Day " << NAME_ID << " created for " << getAmountOfPeople() << " people");
}

Day::~Day(void) {
    PRINT_OBJ("Day " << NAME_ID << " destroyed");
}

Day& Day::operator=(const Day& right) {
    if ( this == &right ) {
        return *this;
    }

    PeopleStats::operator=(right);

    date = right.getDate();

    return *this;
}

Date Day::getDate(void) const {
    return date;
}

std::ostream& operator<<(std::ostream& out, const Day& day) {
#ifdef DEBUG
    std::list<Meal> meals = day.getList();

    out << dynamic_cast<const PeopleStats<Meal>&>(day) << std::endl;
    out << "        - date: " << day.getDate() << std::endl;
    out << "        MEALS (" << meals.size() << "):" << std::endl;
    out << "        >>> >>> >>>" << std::endl;

    for ( std::list<Meal>::iterator it = meals.begin(); it != meals.end(); it++ ) {
        out << "        meal " << *it << std::endl;
    }
    out << "        <<< <<< <<<";
#else
    out << day.getName();
#endif

    return out;
}
