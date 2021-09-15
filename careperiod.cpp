#include "careperiod.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}

void CarePeriod::setEnd(const Date &end) { end_ = end; }

std::string CarePeriod::get_id() const { return patient_->get_id(); }

void CarePeriod::assign_staff_careperiod(Person *person) {
  assign_staff_.push_back(person);
}
