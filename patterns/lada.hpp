#pragma once

#include "auto.hpp"

class Lada_Passenger_car
	: public Passenger_car
{
public:
	Lada_Passenger_car() : Passenger_car("Lada_Passenger_car") {};
	~Lada_Passenger_car() = default;
};

class Lada_Truck
	: public Truck
{
public:
	Lada_Truck() : Truck("Lada_Truck") {};
	~Lada_Truck() = default;
};

class Lada_Racing_car
	: public Racing_car
{
public:
	Lada_Racing_car() : Racing_car("Lada_Racing_car") {};
	~Lada_Racing_car() = default;
};