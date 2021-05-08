#include "third.hpp"

void Dashboard::update(data_t data)
{
	this->history.push_back(data);

	std::cout << "Computer notified: " << std::endl;
	std::cout << "-speed: " << data.speed << std::endl;
	std::cout << "-fuel: \t" << data.fuel << std::endl;
	std::cout << "-oil: \t" << data.oil << std::endl;
}

void Central_computer::run()
{
	for (size_t i = 0; i < 10; i++)
	{
		this->speed = rand() % 250;
		this->oil   = rand() % 100;
		this->fuel  = rand() % 100;

		if (this->subsriber)
		{
			this->subsriber->update({ this->speed,this->oil,this->fuel });
		}
	}
}

void Central_computer::add_subsriber(Subscriber* subsriber)
{
	this->subsriber = subsriber;
}
