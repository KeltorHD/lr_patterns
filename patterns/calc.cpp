#include "calc.hpp"

void first()
{
	std::fstream file("first.txt");

	Temperature_celsius::temp_mas_t mas;
	std::string tmp;
	double d_tmp;
	while (file >> tmp >> d_tmp)
	{
		mas.push_back({ tmp, d_tmp });
	}

	Temperature_celsius temp(Adapter::fahrenheit2celsius(mas));

	std::cout << "AVG: " << temp.calc_avg() << std::endl;
	std::cout << "MIN: " << temp.calc_min() << std::endl;
	std::cout << "MAX: " << temp.calc_max() << std::endl;
}

void second()
{
	Car_factory* factory{ new Lada_car_factory() };

	std::cout << "Lada:" << std::endl;
	std::cout << "Passenger car: \t" << factory->create_passenger_car()->get_info() << std::endl;
	std::cout << "Truck: \t\t" << factory->create_truck()->get_info() << std::endl;
	std::cout << "Racing car: \t" << factory->create_racing_car()->get_info() << std::endl;

	delete factory;
	factory = new Ford_car_factory();

	std::cout << std::endl << "Ford:" << std::endl;
	std::cout << "Passenger car: \t" << factory->create_passenger_car()->get_info() << std::endl;
	std::cout << "Truck: \t\t" << factory->create_truck()->get_info() << std::endl;
	std::cout << "Racing car: \t" << factory->create_racing_car()->get_info() << std::endl;

	delete factory;
}

void third()
{
	Subscriber* dashboard{ new Dashboard };
	Central_computer computer{};

	computer.add_subsriber(dashboard);

	computer.run();

	delete dashboard;
}
