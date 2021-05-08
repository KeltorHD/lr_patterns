#pragma once

#include <iostream>

#include <vector>
#include <string>
#include <limits>

class Temperature_celsius
{
public:
	using day_temp_t = std::pair<std::string, double>;
	using temp_mas_t = std::vector<day_temp_t>;

	/*������������ / ����������*/
	Temperature_celsius(const temp_mas_t& mas);
	~Temperature_celsius() = default;

	/*����������*/
	double calc_avg() const;
	day_temp_t calc_min() const;
	day_temp_t calc_max() const;

	/*�����*/
	friend std::ostream& operator<<(std::ostream& os, const Temperature_celsius& t);

private:
	/*������ ��������*/
	temp_mas_t temp_mas;
};

std::ostream& operator<<(std::ostream& os, const Temperature_celsius::day_temp_t& t);

class Adapter
{
public:
	static Temperature_celsius::temp_mas_t fahrenheit2celsius(const Temperature_celsius::temp_mas_t& mas);
};