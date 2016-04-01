#include <convert.hpp>
#include <engineLimits.hpp>

QString priceToQString(uint64_t price) {
    QString priceInt = QString::number(price/STATS_PRICE_RATIO);
    uint64_t fraction = price % STATS_PRICE_RATIO;
    QString priceFract = QString::number(fraction);

    if ( fraction == 0 ) {
        priceFract.prepend("00");
    } else if ( fraction < 10 ) {
        priceFract.prepend("0");
    }

    return priceInt + "." + priceFract;
}

QString massToQString(uint64_t mass) {
    QString massInt = QString::number(mass/STATS_MASS_RATIO);
    uint64_t fraction = mass % STATS_MASS_RATIO;
    QString massFract = QString::number(fraction);

    if ( fraction == 0 ) {
        massFract.prepend("000");
    } else if ( fraction < 10 ) {
        massFract.prepend("00");
    } else if ( fraction < 100 ) {
        massFract.prepend("0");
    }

    return massInt + "." + massFract;
}

QString fatsToQString(uint64_t fats) {
    QString fatsInt = QString::number(fats/STATS_FATS_RATIO);
    uint64_t fraction = fats % STATS_FATS_RATIO;
    QString fatsFract = QString::number(fraction);

    if ( fraction == 0 ) {
        fatsFract.prepend("0");
    }

    return fatsInt + "." + fatsFract;
}

QString proteinsToQString(uint64_t proteins) {
    QString proteinsInt = QString::number(proteins/STATS_PROTEINS_RATIO);
    uint64_t fraction = proteins % STATS_PROTEINS_RATIO;
    QString proteinsFract = QString::number(fraction);

    if ( fraction == 0 ) {
        proteinsFract.prepend("0");
    }

    return proteinsInt + "." + proteinsFract;
}

QString carbohydratesToQString(uint64_t carbohydrates) {
    QString carbohydratesInt = QString::number(carbohydrates/STATS_CARBOHYDRATES_RATIO);
    uint64_t fraction = carbohydrates % STATS_CARBOHYDRATES_RATIO;
    QString carbohydratesFract = QString::number(fraction);

    if ( fraction == 0 ) {
        carbohydratesFract.prepend("0");
    }

    return carbohydratesInt + "." + carbohydratesFract;
}

QString caloriesToQString(uint64_t calories) {
    return QString::number(calories);
}

uint64_t QStringToPrice(QString price) {
    return static_cast<uint64_t>(price.toDouble()*STATS_PRICE_RATIO);
}

uint64_t QStringToMass(QString mass) {
    return static_cast<uint64_t>(mass.toDouble()*STATS_MASS_RATIO);
}

uint64_t QStringToFats(QString fats) {
    return static_cast<uint64_t>(fats.toDouble()*STATS_FATS_RATIO);
}

uint64_t QStringToProteins(QString proteins) {
    return static_cast<uint64_t>(proteins.toDouble()*STATS_PROTEINS_RATIO);
}

uint64_t QStringToCarbohydrates(QString carbohydrates) {
    return static_cast<uint64_t>(carbohydrates.toDouble()*STATS_CARBOHYDRATES_RATIO);
}

uint64_t QStringToCalories(QString calories) {
    return static_cast<uint64_t>(calories.toDouble()*STATS_CALORIES_RATIO);
}
