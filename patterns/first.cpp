#include "first.hpp"

Temperature_celsius::Temperature_celsius(const temp_mas_t& mas)
	: temp_mas(mas)
{
}

double Temperature_celsius::calc_avg() const
{
	double res{};
	for (auto& i : this->temp_mas)
	{
		res += i.second;
	}
	return res / this->temp_mas.size();
}

Temperature_celsius::day_temp_t Temperature_celsius::calc_min() const
{
	day_temp_t res{ "", std::numeric_limits<double>::max() };
	for (auto& i : this->temp_mas)
	{
		if (i.second < res.second)
		{
			res.second = i.second;
			res.first = i.first;
		}
	}
	return res;
}

Temperature_celsius::day_temp_t Temperature_celsius::calc_max() const
{
	day_temp_t res{ "", std::numeric_limits<double>::min() };
	for (auto& i : this->temp_mas)
	{
		if (i.second > res.second)
		{
			res.second = i.second;
			res.first = i.first;
		}
	}
	return res;
}

std::ostream& operator<<(std::ostream& os, const Temperature_celsius& t)
{
	for (auto& i : t.temp_mas)
	{
		os << "Date: " << i.first << ", temperature: " << i.second << " C" << std::endl;
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const Temperature_celsius::day_temp_t& t)
{
	os << "Date: " << t.first << ", temperature: " << t.second << " C" << std::endl;
	return os;
}

Temperature_celsius::temp_mas_t Adapter::fahrenheit2celsius(const Temperature_celsius::temp_mas_t& mas)
{
	Temperature_celsius::temp_mas_t res{};
	for (auto& i : mas)
	{
		res.push_back({ i.first, (i.second - 32) * (5. / 9.) });
	}
	return res;
}
