#pragma once

#include "auto.hpp"

class Ford_Passenger_car
	: public Passenger_car
{
public:
	Ford_Passenger_car() : Passenger_car("Ford_Passenger_car") {};
	~Ford_Passenger_car() = default;
};

class Ford_Truck
	: public Truck
{
public:
	Ford_Truck() : Truck("Ford_Truck") {};
	~Ford_Truck() = default;
};

class Ford_Racing_car
	: public Racing_car
{
public:
	Ford_Racing_car() : Racing_car("Ford_Racing_car") {};
	~Ford_Racing_car() = default;
};