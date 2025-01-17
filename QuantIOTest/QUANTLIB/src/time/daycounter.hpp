#pragma once
#include <ql/time/daycounter.hpp>
#include <ql/time/daycounters/all.hpp>
#include "luastate/luastate.hpp"
#include "calendar.hpp"

class CustomDayCounter : public QuantLib::DayCounter {
public:
	CustomCalendar m_customCalendar;
public:
	class CustomDayCounterImpl : public QuantLib::DayCounter::Impl {
	public:
		std::string m_dayCounterName;
		std::string m_dayCountFunction;
		std::string m_yearFractionFunction;
		std::string name() const override;


		//Extra variables
		bool m_code;
		bool m_inclusive;
		unsigned int m_dayCount;
		unsigned int m_denominator;

		//number of days between two dates
		QuantLib::Date::serial_type dayCount(const QuantLib::Date& d2, const QuantLib::Date& d1) const override;
		//the period between two dates as a fraction of year
		QuantLib::Time yearFraction(const QuantLib::Date& d2, const QuantLib::Date& d1, 
			const QuantLib::Date&, const QuantLib::Date&) const override;
		CustomDayCounterImpl(std::string& name, std::string& dayCountFunction, std::string& yearFractionFunction, 
			bool code, bool inclusive, unsigned int dayCount, unsigned int denominator)
			: m_dayCounterName(name), m_dayCountFunction(dayCountFunction), m_yearFractionFunction(yearFractionFunction), m_code(code), m_inclusive(inclusive), m_dayCount(dayCount), m_denominator(denominator) {};
	};
public:
	void setAnotherDayCounter(std::string& name, std::string& dayCountFunction, 
		std::string& yearFractionFunction, CustomCalendar& calendar, 
		bool code, bool inclusive, unsigned int dayCount, unsigned int denominator);

	CustomDayCounter() = default;
	CustomDayCounter(std::string& name, std::string& dayCountFunction, 
		std::string& yearFractionFunction, CustomCalendar& calendar, 
		bool code, bool inclusive, unsigned int dayCount, unsigned int denominator);
	CustomDayCounter(const CustomDayCounter& customDayCounter);

};

bool isLastOfFebruary(QuantLib::Day d, QuantLib::Month m, QuantLib::Year y);

//Lua functions
int isLastOfFebruaryLua(lua_State* L);
int businessDaysBetweenLua(lua_State* L);
int daysBetweenLua(lua_State* L);

//Year fraction
QuantLib::Time getYearFraction(const QuantLib::Date& date2, const QuantLib::Date& date1,
	const std::string& dayCountFunction, const std::string& yearFracFunction);

//Day count
QuantLib::Date::serial_type getDayCount(const QuantLib::Date& date2, const QuantLib::Date& date1,
	const std::string& dayCountFunction, const std::string& yearFracFunction);