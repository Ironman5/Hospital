/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "date.hh"
#include "person.hh"
#include <set>
#include <string>

class CarePeriod
{
public:
    // Constructor, start date given as a string (ddmmyyyy).
    CarePeriod(const std::string& start, Person* patient);

    // Constructor, start date given as a Date object.
    CarePeriod(const Date& start, Person* patient);

    // Destructor.
    ~CarePeriod();

    // More public methods

    // set careperiod end
    void setEnd(const Date &end);

    // Get patient_id (name)
    std::string get_id() const;

    // Assign staff to careperiod
    void assign_staff_careperiod(Person *person);

    // Prints person's care period.
    void print_careperiod(const std::string &pre_text) const;

    // Prints person's care staff.
    void print_assign_staff(const std::string &pre_text) const;

  private:
    Person* patient_;
    Date start_;
    Date end_;

    // More attributes and methods
    std::set<Person *> assign_staff_;
};

#endif // CAREPERIOD_HH
