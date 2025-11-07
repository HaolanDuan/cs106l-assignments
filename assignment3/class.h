class Individual {
    private:
        int age;
        int gender;
        int race;
        int status;
    public:
        // constructor for a new individual
        Individual(int age, int gender, int race, int status);
        // destructor
        ~Individual();
        // get the age of the individual
        int getAge();
        // get the gender of the individual
        int getGender();
        // get the race of the individual
        int getRace();
        // get the status of the individual
        int getStatus();
};

