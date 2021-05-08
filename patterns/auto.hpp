#pragma once

#include <string>

class Passenger_car
{
public:
	Passenger_car(const std::string& info = "Passenger_car") : info(info) {};
	~Passenger_car() = default;

	const std::string& get_info() { return this->info; }

protected:
	const std::string info;
};

class Truck
{
public:
	Truck(const std::string& info = "Truck") : info(info) {};
	~Truck() = default;

	const std::string& get_info() { return this->info; }

protected:
	const std::string info;
};

class Racing_car
{
public:
	Racing_car(const std::string& info = "Racing_car") : info(info) {};
	~Racing_car() = default;

	const std::string& get_info() { return this->info; }

protected:
	const std::string info;
};