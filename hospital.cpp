#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{
    // Deallocating staff
    for( std::map<std::string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Deallocating patients
    for (std::map<std::string, Person *>::iterator iter = patients_.begin();
         iter != patients_.end(); ++iter) {
      delete iter->second;
    }

    // Deallocating careperiods
    for (unsigned int i = 0; i < care_periods_.size(); ++i) {
      delete care_periods_.at(i);
    }
}

void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::enter(Params params)
{
  std::string patient_id = params.at(0);
  std::map<std::string, Person *>::const_iterator patient_iter =
      patients_.find(patient_id);

  // Check patient exist in current patients_
  if (patient_iter != patients_.end() and
      patient_iter->second->get_in_out__hospital() == true) {
    std::cout << ALREADY_EXISTS << patient_id << std::endl;
    return;
  }

  // Create a new patient and save it to _patients_
  Person *new_patient = new Person(patient_id);
  patients_.insert({patient_id, new_patient});

  // Make a new careperiod and save it to care periods_
  CarePeriod *new_careperiod = new CarePeriod(utils::today, new_patient);
  care_periods_.push_back(new_careperiod);
  std::cout << PATIENT_ENTERED << std::endl;
}

void Hospital::leave(Params params)
{
  std::string patient_id = params.at(0);
  auto patient_iter = patients_.find(patient_id);

  // Check the patient exist and in the hospital
  if (patient_iter == patients_.end() or
      not patient_iter->second->get_in_out__hospital()) {
    std::cout << CANT_FIND << patient_id << std::endl;
    return;
  }

  // Record the patient out of the hospital
  patient_iter->second->set_in_out_hospital(false);

  // Set the end date of the patient's care periodd
  for (auto period : care_periods_) {
    if (period->get_id() == patient_id) {
      period->setEnd(utils::today);
    }
  }

  std::cout << PATIENT_LEFT << std::endl;
}

void Hospital::assign_staff(Params params)
{
  std::string staff_id = params.at(0);
  std::string patient_id = params.at(1);

  // Check staff exist
  std::map<std::string, Person *>::const_iterator staff_iter =
      staff_.find(staff_id);
  if (staff_iter == staff_.end()) {
    std::cout << CANT_FIND << staff_id << std::endl;
    return;
  }

  // Check the patient's presence in the hospital
  std::map<std::string, Person *>::const_iterator patient_iter =
      patients_.find(patient_id);
  if (patient_iter == patients_.end() or
      not patient_iter->second->get_in_out__hospital()) {
    std::cout << CANT_FIND << patient_id << std::endl;
    return;
  }

  // Find the patient's last careperiod
  CarePeriod *last = get_last_period(patient_iter->second);

  // Assign staff to the patient latest careperiod
  last->assign_staff_careperiod(staff_iter->second);

  std::cout << STAFF_ASSIGNED << patient_id << std::endl;
}

void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person *>::const_iterator patient_iter =
        patients_.find(patient);
    if (patient_iter == patients_.end()) {
      std::cout << CANT_FIND << patient << std::endl;
      return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person *>::const_iterator patient_iter =
        patients_.find(patient);
    if (patient_iter == patients_.end()) {
      std::cout << CANT_FIND << patient << std::endl;
      return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

void Hospital::print_patient_info(Params params)
{
  std::string patient_id = params.at(0);
  std::string pre_care = "* Care period: ";
  std::string pre_staff = "  - Staff: ";
  std::string pre_med = "* Medicines: ";

  // Check patient exist
  std::map<std::string, Person *>::const_iterator patient_iter =
      patients_.find(patient_id);

  if (patient_iter == patients_.end()) {
    std::cout << CANT_FIND << patient_id << std::endl;
    return;
  }

  // Print the patient's care periods and assigned staff
  for (std::size_t i = 0; i < care_periods_.size(); ++i) {

    if (care_periods_.at(i)->get_id() == patient_id) {
      care_periods_.at(i)->print_careperiod(pre_care);
      care_periods_.at(i)->print_assign_staff(pre_staff);
    }
  }
  // Print the patient's medicines
  patient_iter->second->print_medicines(pre_med);
}

void Hospital::print_care_periods_per_staff(Params params)
{

}

void Hospital::print_all_medicines(Params)
{

}

void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::print_all_patients(Params)
{

}

void Hospital::print_current_patients(Params)
{

}

void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

CarePeriod *Hospital::get_last_period(Person *patient) const {
  for (std::size_t i = care_periods_.size() - 1;; --i) {

    if (care_periods_.at(i)->get_id() == patient->get_id()) {
      return care_periods_.at(i);
    }
  }
  return nullptr;
}
