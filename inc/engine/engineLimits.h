#ifndef ENGINE_LIMITS_H
#define ENGINE_LIMITS_H

// Stats class limits

#define STATS_PRICE_RATIO                                                   100U
#define STATS_FATS_RATIO                                                     10U
#define STATS_PROTEINS_RATIO                                                 10U
#define STATS_CARBOHYDRATES_RATIO                                            10U
#define STATS_CALORIES_RATIO                                                  1U

// Item class limits

#define ITEM_MIN_MASS                                                         1U
#define ITEM_MAX_MASS                                                    100000U
#define ITEM_MIN_PRICE                                                        1U
#define ITEM_MAX_PRICE                                                 10000000U

#define MIN_MASS_FOR_GRAM                                          ITEM_MIN_MASS

// Food class limits

#define FOOD_MIN_MASS                                                         1U
#define FOOD_MAX_MASS                                                    100000U
#define FOOD_MIN_PRICE                                                        1U
#define FOOD_MAX_PRICE                                                 10000000U
#define FOOD_MIN_FATS                                                         0U
#define FOOD_MAX_FATS                                                    100000U
#define FOOD_MIN_PROTEINS                                                     0U
#define FOOD_MAX_PROTEINS                                                100000U
#define FOOD_MIN_CARBOHYDRATES                                                0U
#define FOOD_MAX_CARBOHYDRATES                                           100000U
#define FOOD_MIN_CALORIES                                                     0U
#define FOOD_MAX_CALORIES                                                100000U

// Dish class limits

#define DISH_MIN_MASS                                              FOOD_MIN_MASS
#define DISH_MAX_MASS                                              FOOD_MAX_MASS
#define DISH_MIN_PRICE                                            FOOD_MIN_PRICE
#define DISH_MAX_PRICE                                            FOOD_MAX_PRICE
#define DISH_MIN_FATS                                              FOOD_MIN_FATS
#define DISH_MAX_FATS                                              FOOD_MAX_FATS
#define DISH_MIN_PROTEINS                                      FOOD_MIN_PROTEINS
#define DISH_MAX_PROTEINS                                      FOOD_MAX_PROTEINS
#define DISH_MIN_CARBOHYDRATES                            FOOD_MIN_CARBOHYDRATES
#define DISH_MAX_CARBOHYDRATES                            FOOD_MAX_CARBOHYDRATES
#define DISH_MIN_CALORIES                                      FOOD_MIN_CALORIES
#define DISH_MAX_CALORIES                                      FOOD_MAX_CALORIES
#define DISH_MIN_AMOUNT_OF_PEOPLE                                             1U
#define DISH_MAX_AMOUNT_OF_PEOPLE                                          1000U
#define DISH_MIN_AMOUNT_OF_FOOD                                               1U
#define DISH_MAX_AMOUNT_OF_FOOD                                             100U

// Meal class limits

#define MEAL_MIN_MASS                                              DISH_MIN_MASS
#define MEAL_MAX_MASS                                        DISH_MAX_MASS * 10U
#define MEAL_MIN_PRICE                                            DISH_MIN_PRICE
#define MEAL_MAX_PRICE                                      DISH_MAX_PRICE * 10U
#define MEAL_MIN_FATS                                              DISH_MIN_FATS
#define MEAL_MAX_FATS                                        DISH_MAX_FATS * 10U
#define MEAL_MIN_PROTEINS                                      DISH_MIN_PROTEINS
#define MEAL_MAX_PROTEINS                                DISH_MAX_PROTEINS * 10U
#define MEAL_MIN_CARBOHYDRATES                            DISH_MIN_CARBOHYDRATES
#define MEAL_MAX_CARBOHYDRATES                      DISH_MAX_CARBOHYDRATES * 10U
#define MEAL_MIN_CALORIES                                      DISH_MIN_CALORIES
#define MEAL_MAX_CALORIES                                DISH_MAX_CALORIES * 10U
#define MEAL_MIN_AMOUNT_OF_PEOPLE                      DISH_MIN_AMOUNT_OF_PEOPLE
#define MEAL_MAX_AMOUNT_OF_PEOPLE                      DISH_MAX_AMOUNT_OF_PEOPLE
#define MEAL_MIN_AMOUNT_OF_DISH                                               1U
#define MEAL_MAX_AMOUNT_OF_DISH                                             100U

// Day class limits

#define DAY_MIN_MASS                                               MEAL_MIN_MASS
#define DAY_MAX_MASS                                         MEAL_MAX_MASS * 10U
#define DAY_MIN_PRICE                                             MEAL_MIN_PRICE
#define DAY_MAX_PRICE                                       MEAL_MAX_PRICE * 10U
#define DAY_MIN_FATS                                               MEAL_MIN_FATS
#define DAY_MAX_FATS                                         MEAL_MAX_FATS * 10U
#define DAY_MIN_PROTEINS                                       MEAL_MIN_PROTEINS
#define DAY_MAX_PROTEINS                                 MEAL_MAX_PROTEINS * 10U
#define DAY_MIN_CARBOHYDRATES                             MEAL_MIN_CARBOHYDRATES
#define DAY_MAX_CARBOHYDRATES                       MEAL_MAX_CARBOHYDRATES * 10U
#define DAY_MIN_CALORIES                                       MEAL_MIN_CALORIES
#define DAY_MAX_CALORIES                                 MEAL_MAX_CALORIES * 10U
#define DAY_MIN_AMOUNT_OF_PEOPLE                       MEAL_MIN_AMOUNT_OF_PEOPLE
#define DAY_MAX_AMOUNT_OF_PEOPLE                       MEAL_MAX_AMOUNT_OF_PEOPLE
#define DAY_MIN_AMOUNT_OF_MEAL                                                1U
#define DAY_MAX_AMOUNT_OF_MEAL                                              100U

// Journey class limits

#define JOURNEY_MIN_MASS                                            DAY_MIN_MASS
#define JOURNEY_MAX_MASS                                      DAY_MAX_MASS * 10U
#define JOURNEY_MIN_PRICE                                          DAY_MIN_PRICE
#define JOURNEY_MAX_PRICE                                    DAY_MAX_PRICE * 10U
#define JOURNEY_MIN_FATS                                            DAY_MIN_FATS
#define JOURNEY_MAX_FATS                                      DAY_MAX_FATS * 10U
#define JOURNEY_MIN_PROTEINS                                    DAY_MIN_PROTEINS
#define JOURNEY_MAX_PROTEINS                              DAY_MAX_PROTEINS * 10U
#define JOURNEY_MIN_CARBOHYDRATES                          DAY_MIN_CARBOHYDRATES
#define JOURNEY_MAX_CARBOHYDRATES                    DAY_MAX_CARBOHYDRATES * 10U
#define JOURNEY_MIN_CALORIES                                    DAY_MIN_CALORIES
#define JOURNEY_MAX_CALORIES                              DAY_MAX_CALORIES * 10U
#define JOURNEY_MIN_AMOUNT_OF_PEOPLE                    DAY_MIN_AMOUNT_OF_PEOPLE
#define JOURNEY_MAX_AMOUNT_OF_PEOPLE                    DAY_MAX_AMOUNT_OF_PEOPLE
#define JOURNEY_MIN_AMOUNT_OF_DAYS                                            1U
#define JOURNEY_MAX_AMOUNT_OF_DAYS                                          100U

#endif // ENGINE_LIMITS_H
