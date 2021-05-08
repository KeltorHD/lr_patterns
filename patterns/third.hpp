#pragma once

#include <iostream>
#include <vector>

class Subscriber
{
public:
	struct data_t
	{
		double speed;
		double fuel;
		double oil;
	};
	Subscriber() = default;
	~Subscriber() = default;

	virtual void update(data_t data) = 0;
};

class Dashboard final
	: public Subscriber
{
public:
	Dashboard() = default;
	~Dashboard() = default;

	void update(data_t data) override;

private:
	std::vector<data_t> history;
};

class Central_computer
{
public:
	Central_computer() = default;
	~Central_computer() = default;

	void run();

	void add_subsriber(Subscriber* subsriber);

private:
	double speed;
	double fuel;
	double oil;
	Subscriber* subsriber;
};