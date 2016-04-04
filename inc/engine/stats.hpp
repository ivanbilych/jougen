#ifndef STATS_H
#define STATS_H

#include <common.hpp>
#include <engineLimits.hpp>

#include <iostream>
#include <string>

class Stats {
    private:
        static uint64_t lastId;
        std::string name;
        uint64_t id {lastId};
        uint64_t mass {};
        uint64_t price {};
        uint64_t fats {};
        uint64_t proteins {};
        uint64_t carbohydrates {};
        uint64_t calories {};

        void updateId(void);

    protected:
        void setMass(uint64_t mass);
        void setPrice(uint64_t price);
        void setFats(uint64_t fats);
        void setProteins(uint64_t proteins);
        void setCarbohydrates(uint64_t carbohydrates);
        void setCalories(uint64_t calories);

    public:
        class Compare {
            public:
                const bool operator()(const Stats&, const Stats&) const;
                const bool operator()(const Stats*, const Stats*) const;
        };

        const uint64_t minMass;
        const uint64_t maxMass;
        const uint64_t minPrice;
        const uint64_t maxPrice;
        const uint64_t priceRatio {STATS_PRICE_RATIO};
        const uint64_t minFats {};
        const uint64_t maxFats {};
        const uint64_t fatsRatio {STATS_FATS_RATIO};
        const uint64_t minProteins {};
        const uint64_t maxProteins {};
        const uint64_t proteinsRatio {STATS_PROTEINS_RATIO};
        const uint64_t minCarbohydrates {};
        const uint64_t maxCarbohydrates {};
        const uint64_t carbohydratesRatio {STATS_CARBOHYDRATES_RATIO};
        const uint64_t minCalories {};
        const uint64_t maxCalories {};
        const uint64_t caloriesRatio {STATS_CALORIES_RATIO};

        Stats(std::string name, uint64_t minMass, uint64_t maxMass, uint64_t minPrice, uint64_t maxPrice);
        Stats(std::string name, uint64_t minMass, uint64_t maxMass, uint64_t minPrice, uint64_t maxPrice, uint64_t minFats, uint64_t maxFats, uint64_t minProteins, uint64_t maxProteins, uint64_t minCarbohydrates, uint64_t maxCarbohydrates, uint64_t minCalories, uint64_t maxCalories);
        ~Stats(void);

        Stats& operator=(const Stats& right);

        const std::string& getName(void) const;
        uint64_t getId(void) const;
        uint64_t getMass(void) const;
        uint64_t getPrice(void) const;
        uint64_t getFats(void) const;
        uint64_t getProteins(void) const;
        uint64_t getCarbohydrates(void) const;
        uint64_t getCalories(void) const;
};

std::ostream& operator<<(std::ostream& out, const Stats& stats);

#endif // STATS_H
