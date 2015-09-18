#ifndef ERRORS_H
#define ERRORS_H

// Global Engine Exception

class EngineException {};

// Date class exceptions

class DateException : public EngineException {};

class WrongDay : public DateException {};
class WrongMounth : public DateException {};
class WrongYear : public DateException {};

// Stats class exceptions

class StatsException : public EngineException {};

class NoMoreId : public StatsException {};
class WrongStatsMass : public StatsException {};
class WrongStatsPrice : public StatsException {};
class WrongStatsFats : public StatsException {};
class WrongStatsProteins : public StatsException {};
class WrongStatsCarbohydrates : public StatsException {};
class WrongStatsCalories : public StatsException {};

// Item class exceptions

class ItemException : public EngineException {};

class WrongItemMass : public ItemException {};

// Food class exceptions

class FoodException : public EngineException {};

class WrongFoodMass : public FoodException {};

// People Stats class exceptions

class PeopleStatsException : public EngineException {};

class WrongPeopleStatsAmountOfPeople : public PeopleStatsException {};

// Dish class exceptions

class DishException : public EngineException {};

class WrongDishMass : public DishException {};
class WrongDishAmountOfPeople : public DishException {};
class AlreadySuchFoodInList : public DishException {};
class TooMuchFoodInMap : public DishException {};
class TooBigDishMass : public DishException {};
class TooBigDishPrice : public DishException {};
class TooBigDishFats : public DishException {};
class TooBigDishProteins : public DishException {};
class TooBigDishCarbohydrates : public DishException {};
class TooBigDishCalories : public DishException {};
class NoSuchFoodInMap : public DishException {};
class LastFoodInMap : public DishException {};

// Meal class exceptions

class MealException : public EngineException {};

class TooMuchDishInList : public MealException {};
class TooBigMealMass : public MealException {};
class TooBigMealPrice : public MealException {};
class TooBigMealFats : public MealException {};
class TooBigMealProteins : public MealException {};
class TooBigMealCarbohydrates : public MealException {};
class TooBigMealCalories : public MealException {};
class LastDishInList : public MealException {};
class NoSuchDishInList : public MealException {};
class SetMealPeopleAmountError : public MealException {};

// Day class exceptions

class DayException : public EngineException {};

class TooMuchMealsInList : public DayException {};
class TooBigDayMass : public DayException {};
class TooBigDayPrice : public DayException {};
class TooBigDayFats : public DayException {};
class TooBigDayProteins : public DayException {};
class TooBigDayCarbohydrates : public DayException {};
class TooBigDayCalories : public DayException {};
class LastMealInList : public DayException {};
class NoSuchMealInList : public DayException {};
class SetDayPeopleAmountError : public DayException {};

// Journey class exceptions

class JourneyException : public EngineException {};

class TooMuchDaysInList : public JourneyException {};
class TooBigJourneyMass : public JourneyException {};
class TooBigJourneyPrice : public JourneyException {};
class TooBigJourneyFats : public JourneyException {};
class TooBigJourneyProteins : public JourneyException {};
class TooBigJourneyCarbohydrates : public JourneyException {};
class TooBigJourneyCalories : public JourneyException {};
class LastDayInList : public JourneyException {};
class NoSuchDayInList : public JourneyException {};
class SetJourneyPeopleAmountError : public JourneyException {};

#endif // ERRORS_H
