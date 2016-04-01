#ifndef CONVERT_H
#define CONVERT_H

#include <common.hpp>

#include <QString>

QString priceToQString(uint64_t price);
QString massToQString(uint64_t mass);
QString fatsToQString(uint64_t fats);
QString proteinsToQString(uint64_t proteins);
QString carbohydratesToQString(uint64_t carbohydrates);
QString caloriesToQString(uint64_t calories);

#endif // CONVERT_H
