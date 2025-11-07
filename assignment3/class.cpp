#include "individual.h"

// default constructor
Individual::Individual() {
    age = 0;
    gender = 0;
    race = 0;
    status = 0;
}

Individual::Individual(int age, int gender, int race, int status) {
    this->age = age;
    this->gender = gender;
    this->race = race;
    this->status = status;
}

int Individual::getAge() {
    return this->age;
}

int Individual::getGender() {
    return this->gender;
}

int Individual::getRace() {
    return this->race;
}

int Individual::getStatus() {
    return this->status;
}