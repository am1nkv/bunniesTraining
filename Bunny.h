#ifndef BUNNY_H
#define BUNNY_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>

// Enums
enum Sex { Male, Female };

enum Color { White, Brown, Black, Spotted };

// Names based on the gender
static const std::vector<std::string> maleNames = {
        "Eren", "Jean", "Levi", "Armin", "Falco"
};

static const std::vector<std::string> femaleNames = {
    "Mikasa", "Historia", "Ymir", "Annie", "Sasha"
};

class Bunny {

// Private variables
private:
    Sex sex;
    Color color;
    std::string name;
    int age;
    bool radioactive_mutant_vampire_bunny;

// Public variables and functions
public:
    Bunny();
    Bunny(Color momsColor) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<int> dist(1, 100);
        radioactive_mutant_vampire_bunny = (dist(gen) <= 2);
        sex = (std::rand() % 2 == 0) ? Sex::Male : Sex::Female;
        this->color = momsColor;
        this->age = 0;
        if (sex == Sex::Male) {
            name = maleNames[std::rand() % maleNames.size()];
        }
        else {
            name = femaleNames[std::rand() % femaleNames.size()];
        }
    };

    Bunny* next;   // Pointer to next bunny in the list

    // Get the sex of the bunny
    std::string getSexString() const {
        return (sex == Sex::Male) ? "Male" : "Female";
    }

    // Set the sex of the bunny
    void setSex(Sex newSex) {
        this->sex = newSex;
    }

    // Get the color of the bunny
    std::string getColorString() const {
        if (this->color == Color::Black)
            return "Black";
        else if (this->color == Color::Brown)
            return "Brown";
        else if (this->color == Color::White)
            return "White";
        else
            return "Spotted";
    }

    Color getColor() const {
        return this->color;
    }

    // Set the color of the bunny
    void setColor(Color newColor) {
        this->color = newColor;
    }

    void appendBunny2();

    int lengthBunnyList2();

    void freeBunnies2();

    // Increment the age of the bunny
    void anniversaryBunny() {

        Bunny* current = this;
        while (current != nullptr) {

            // Normal bunny, max age 10
            if (!this->isRadioactive_Mutant_Vampire_Bunny() &&
                current->getAgeBunny() < 10)
            {
                current->age ++;
            }

            // Mutant bunny, max age 50
            if (current->isRadioactive_Mutant_Vampire_Bunny() &&
                current->getAgeBunny() < 50)
            {
                current->age ++;
            }

            current = current->next;
        }
    }

    // Get the name of the bunny
    std::string getNameBunny() const {
        return this->name;
    }

    // Set the name of the bunny
    void setName(const std::string& newName) { // & evite de copier toute la chaîne de caracteres, ce qui rend la fonction plus rapide et plus efficace.
        this->name = newName;
    }

    // Get the age of the bunny
    int getAgeBunny() const {
        return this->age;
    }

    // Set the age of the bunny
    void setAge(int newAge) {
        this->age = newAge;
    }

    // Bool to know if the bunny is radioactive mutant vampire
    bool isRadioactive_Mutant_Vampire_Bunny() const {
        return this->radioactive_mutant_vampire_bunny;
    }

    // Setter to turn the normal bunny
    void setRadioactive_Mutant_Vampire_Bunny(bool isVampire) {
        this->radioactive_mutant_vampire_bunny = isVampire;
    }
};

void appendBunny(Bunny*& head);
int lengthBunnyList(Bunny* bunny);
void showBunnies(const Bunny* head);
void freeBunnies(Bunny*& head);
void removeDeadBunnies(Bunny*& head);
void breedBunnies(Bunny*& head);
void foodShortage(Bunny*& head);
void infectBunnies(Bunny* head);

#endif // BUNNY_H