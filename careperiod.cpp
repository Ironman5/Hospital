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
  assign_staff_.insert(person);
}

void CarePeriod::print_careperiod(const std::string &pre_text) const {
  std::cout << pre_text;
  start_.print();
  std::cout << " - ";
  if (!end_.is_default()) {
    end_.print();
  }
  std::cout << std::endl;
}

void CarePeriod::print_assign_staff(const std::string &pre_text) const {
  std::cout << pre_text;

  if (assign_staff_.empty()) {
    std::cout << "None" << std::endl;
    return;
  }

  for (auto &name : assign_staff_) {
    name->print_id();
  }
}
