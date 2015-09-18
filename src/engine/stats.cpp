#include <stats.h>
#include <engineLimits.h>
#include <debug.h>
#include <errors.h>

uint64_t Stats::lastId = 0;

Stats::Stats(std::string name, uint64_t minMass, uint64_t maxMass, uint64_t minPrice, uint64_t maxPrice) :
        name(name), id(lastId), mass(0), price(0), fats(0), proteins(0), carbohydrates(0), calories(0), minMass(minMass), maxMass(maxMass), minPrice(minPrice), maxPrice(maxPrice), priceRatio(STATS_PRICE_RATIO), minFats(0), maxFats(0), fatsRatio(STATS_FATS_RATIO), minProteins(0), maxProteins(0), proteinsRatio(STATS_PROTEINS_RATIO), minCarbohydrates(0), maxCarbohydrates(0), carbohydratesRatio(STATS_CARBOHYDRATES_RATIO), minCalories(0), maxCalories(0), caloriesRatio(STATS_CALORIES_RATIO) {
    updateId();

    PRINT_OBJ("Created stats class " << NAME_ID);
}

Stats::Stats(std::string name, uint64_t minMass, uint64_t maxMass, uint64_t minPrice, uint64_t maxPrice, uint64_t minFats, uint64_t maxFats, uint64_t minProteins, uint64_t maxProteins, uint64_t minCarbohydrates, uint64_t maxCarbohydrates, uint64_t minCalories, uint64_t maxCalories) :
        name(name), id(lastId), mass(0), price(0), fats(0), proteins(0), carbohydrates(0), calories(0), minMass(minMass), maxMass(maxMass), minPrice(minPrice), maxPrice(maxPrice), priceRatio(STATS_PRICE_RATIO), minFats(minFats), maxFats(maxFats), fatsRatio(STATS_FATS_RATIO), minProteins(minProteins), maxProteins(maxProteins), proteinsRatio(STATS_PROTEINS_RATIO), minCarbohydrates(minCarbohydrates), maxCarbohydrates(maxCarbohydrates), carbohydratesRatio(STATS_CARBOHYDRATES_RATIO), minCalories(minCalories), maxCalories(maxCalories), caloriesRatio(STATS_CALORIES_RATIO) {
    updateId();

    PRINT_OBJ("Created stats class " << NAME_ID);
}

Stats::~Stats(void) {
    PRINT_OBJ("Destroyed stats class " << NAME_ID);
}

Stats& Stats::operator=(const Stats& right) {
    if ( this == &right ) {
        return *this;
    }

    name = right.getName();
    id = right.getId();
    mass = right.getMass();
    price = right.getPrice();
    fats = right.getFats();
    proteins = right.getProteins();
    carbohydrates = right.getCarbohydrates();
    calories = right.getCalories();

    return *this;
}

void Stats::setMass(uint64_t mass) {
    if ( mass < minMass || mass > maxMass ) {
        PRINT_ERR("Wrong mass value provided [" << mass << "]");

        throw WrongStatsMass();
    }

    this->mass = mass;

    PRINT_INFO("Stats class " << NAME_ID << " mass set to " << mass);
}

void Stats::setPrice(uint64_t price) {
    if ( price < minPrice || price > maxPrice ) {
        PRINT_ERR("Wrong price value provided [" << price << "]");

        throw WrongStatsPrice();
    }

    this->price = price;

    PRINT_INFO("Stats class " << NAME_ID << " price set to " << price);
}

void Stats::setFats(uint64_t fats) {
    if ( fats < minFats || fats > maxFats ) {
        PRINT_ERR("Wrong food fats value provided [" << fats << "]");

        throw WrongStatsFats();
    }

    this->fats = fats;

    PRINT_INFO("Stats class " << NAME_ID << " fats set to " << fats);
}

void Stats::setProteins(uint64_t proteins) {
    if ( proteins < minProteins || proteins > maxProteins ) {
        PRINT_ERR("Wrong food proteins value provided [" << proteins << "]");

        throw WrongStatsProteins();
    }

    this->proteins = proteins;

    PRINT_INFO("Stats class " << NAME_ID << " proteins set to " << proteins);
}

void Stats::setCarbohydrates(uint64_t carbohydrates) {
    if ( carbohydrates < minCarbohydrates || carbohydrates > maxCarbohydrates ) {
        PRINT_ERR("Wrong food carbohydrates value provided [" << carbohydrates << "]");

        throw WrongStatsCarbohydrates();
    }

    this->carbohydrates = carbohydrates;

    PRINT_INFO("Stats class " << NAME_ID << " carbohydrates set to " << carbohydrates);
}

void Stats::setCalories(uint64_t calories) {
    if ( calories < minCalories || calories > maxCalories ) {
        PRINT_ERR("Wrong food calories value provided [" << calories << "]");

        throw WrongStatsCalories();
    }

    this->calories = calories;

    PRINT_INFO("Stats class " << NAME_ID << " calories set to " << calories);
}

const std::string& Stats::getName(void) const {
    return name;
}

uint64_t Stats::getId(void) const {
    return id;
}

uint64_t Stats::getMass(void) const {
    return mass;
}

uint64_t Stats::getPrice(void) const {
    return price;
}

uint64_t Stats::getFats(void) const {
    return fats;
}

uint64_t Stats::getProteins(void) const {
    return proteins;
}

uint64_t Stats::getCarbohydrates(void) const {
    return carbohydrates;
}

uint64_t Stats::getCalories(void) const {
    return calories;
}

void Stats::updateId(void) {
    if ( lastId == UINT_MAX ) {
        throw NoMoreId();
    }

    lastId += 1;
}

const bool Stats::Compare::operator()(const Stats& left, const Stats& right) const {
    return left.getId() < right.getId();
}

std::ostream& operator<<(std::ostream& out, const Stats& stats) {
#ifdef DEBUG
    char prevFill;
    uint32_t prevWide;
    uint64_t price = stats.getPrice();
    uint64_t fats = stats.getFats();
    uint64_t proteins = stats.getProteins();
    uint64_t carbohydrates = stats.getCarbohydrates();
    uint64_t calories = stats.getCalories();

    out << "\"" << stats.getName() << "\" (";

    prevFill = out.fill('0');
    prevWide = out.width(10);

    out << stats.getId();

    out.fill(prevFill);
    out.width(prevWide);

    out << ")" << std::endl;
    out << "        - mass: " << stats.getMass() << " gram" << std::endl;
    out << "        - price: " << price / stats.priceRatio << "." << price % stats.priceRatio << std::endl;
    out << "        - fats: " << fats / stats.fatsRatio << "." << fats % stats.fatsRatio << std::endl;
    out << "        - proteins: " << proteins / stats.proteinsRatio << "." << proteins % stats.proteinsRatio << std::endl;
    out << "        - carbohydrates: " << carbohydrates / stats.carbohydratesRatio << "." << carbohydrates % stats.carbohydratesRatio << std::endl;
    out << "        - calories: " << calories / stats.caloriesRatio << "." << calories % stats.caloriesRatio;
#else
    out << "\"" << stats.getName() << "\"";
#endif

    return out;
}
