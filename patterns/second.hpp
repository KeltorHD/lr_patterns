#pragma once

#include "lada.hpp"
#include "ford.hpp"

/*abstract fabric*/
class Car_factory
{
public:
	virtual std::unique_ptr<Passenger_car> create_passenger_car() { return std::make_unique<Passenger_car>(); }
	virtual std::unique_ptr<Truck> create_truck() { return std::make_unique<Truck>(); }
	virtual std::unique_ptr<Racing_car> create_racing_car() { return std::make_unique<Racing_car>(); }
};

class Lada_car_factory final
	: public Car_factory
{
public:
	std::unique_ptr<Passenger_car> create_passenger_car() final { return std::make_unique<Lada_Passenger_car>(); }
	std::unique_ptr<Truck> create_truck() final { return std::make_unique<Lada_Truck>(); }
	std::unique_ptr<Racing_car> create_racing_car() final { return std::make_unique<Lada_Racing_car>(); }
};

class Ford_car_factory final
	: public Car_factory
{
public:
	std::unique_ptr<Passenger_car> create_passenger_car() final { return std::make_unique<Ford_Passenger_car>(); }
	std::unique_ptr<Truck> create_truck() final { return std::make_unique<Ford_Truck>(); }
	std::unique_ptr<Racing_car> create_racing_car() final { return std::make_unique<Ford_Racing_car>(); }
};