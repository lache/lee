#ifndef __CargoModel_H__
#define __CargoModel_H__

enum class CargoType
{
    Empty,
    Passenger,
};

class CargoModel
{
public:
    float _capacity;
    CargoType _cargoType;

    long long int _price;

    static CargoModel s_emptyCargo;
};

#endif
