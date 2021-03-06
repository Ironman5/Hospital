/* Class Person
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a person that can be a patient or a staff member
 * in hospital.
 *
 * Note: Students can change this class, but most probably they need not.
 * */
#ifndef PERSON_HH
#define PERSON_HH

#include "date.hh"
#include <string>
#include <map>
#include <vector>

class Person
{
public:
    // Default constructor.
    Person();

    // Constructor with an id.
    Person(const std::string& id);

    // Constructor with an id and a date of birth (actually useless)
    Person(const std::string& id, const std::string& date_of_birth);

    // Destructor.
    ~Person();

    // Set the patient in / out of the hospital
    void set_in_out_hospital(bool state);

    // Get the patient's location
    bool get_in_out__hospital() const;

    // Get patient's name
    std::string get_id() const;

    // Get the patient's medication
    std::vector<std::string> get_medicines() const;

    // Adds a medicine for the person.
    void add_medicine(const std::string& name,
                      unsigned int strength,
                      unsigned int dosage);

    // Removes medicine from the person.
    void remove_medicine(const std::string& name);

    // Prints person's id.
    void print_id() const;

    // Prints person's medicines.
    void print_medicines(const std::string& pre_text) const;

    // Comparison operator, enables forming a set of Person objects.
    bool operator<(const Person& rhs) const;

private:
    std::string id_;     // Can be a name or any other identifier
    Date date_of_birth_; // Not actually needed
    bool in_hospital;

    struct Prescription
    {
        unsigned int strength_;
        unsigned int dosage_;
    };
    // Medicine names and their prescriptions
    std::map<std::string, Prescription> medicines_;
};

#endif // PERSON_HH
