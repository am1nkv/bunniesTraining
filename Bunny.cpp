#include "Bunny.h"

// Bunny constructor, we create a bunny and assign him a random sex and color and a name based on his sex
Bunny::Bunny() {

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(1, 100);
    static const Color colors[] = { Color::Black, Color::Brown, Color::White, Color::Spotted };

    // The bunny has 2% of chance to be radioactive mutant vampire
    radioactive_mutant_vampire_bunny = (dist(gen) <= 2);

    sex = (std::rand() % 2 == 0) ? Sex::Male : Sex::Female;

    age = 0;

    color = colors[std::rand() % 4];

    // Assign random name based on sex
    if (sex == Sex::Male) {
        name = maleNames[std::rand() % maleNames.size()];
    }
    else {
        name = femaleNames[std::rand() % femaleNames.size()];
    }

    next = nullptr;
}

void Bunny::appendBunny2() {

    Bunny* head = this;
    Bunny* newBunny = new Bunny();

    if (!head) {
        head = newBunny;
    }
    else {
        Bunny* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newBunny;
    }
}

// Add a bunny in the list of bunnies
void appendBunny(Bunny*& head) { // *& pour pouvoir modifier le head, la fonction doit changer le pointeur d’origine

    Bunny* newBunny = new Bunny;

    if (!head) {
        head = newBunny;
    }
    else {
        Bunny* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newBunny;
    }
}

int Bunny::lengthBunnyList2() {
    Bunny* current = this;
    int count = 0;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}



int lengthBunnyList(Bunny* bunny) {
    int count = 0;
    Bunny* current = bunny;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// Show all the bunnies in the list
void showBunnies(const Bunny* head) {
    const Bunny* temp = head;
    int index = 1;
    while (temp) {
        std::cout << "Bunny " << index++ << ": "
            << temp->getNameBunny() << " (" << temp->getSexString() << ") \n" << "My color : " << temp->getColorString() << "\n" << "My age : " << temp->getAgeBunny() << "\n";
        if (temp->isRadioactive_Mutant_Vampire_Bunny())
            std::cout << "I am radioactive mutant vampire bunny... >_<" << std::endl;
        else
            std::cout << "I am a normal bunny !" << std::endl;
        temp = temp->next;
    }
}

void Bunny::freeBunnies2() {
    Bunny* head = this;
    while (head) {
        Bunny* temp = head;
        head = head->next;
        delete temp;
    }
}

// Free all bunnies from memory
void freeBunnies(Bunny*& head) {
    while (head) {
        Bunny* temp = head;
        head = head->next;
        delete temp;
    }
}

// Remove bunnies that have reached their max age
void removeDeadBunnies(Bunny*& head) {
    // Remove from the beginning
    while (head && ((head->getAgeBunny() >= 10 && !head->isRadioactive_Mutant_Vampire_Bunny()) ||
                    (head->getAgeBunny() >= 50 && head->isRadioactive_Mutant_Vampire_Bunny()))) {
        Bunny* temp = head;
        std::cout << "RIP... " << head->getNameBunny() << " died at age " << head->getAgeBunny() << std::endl;
        head = head->next;
        delete temp;
    }

    // Remove from middle/end
    if (head) {
        Bunny* current = head;
        while (current->next) {
            if ((current->next->getAgeBunny() >= 10 && !current->next->isRadioactive_Mutant_Vampire_Bunny()) ||
                (current->next->getAgeBunny() >= 50 && current->next->isRadioactive_Mutant_Vampire_Bunny())) {
                Bunny* temp = current->next;
                std::cout << "RIP... " << temp->getNameBunny() << " died at age " << temp->getAgeBunny() << std::endl;
                current->next = temp->next;
                delete temp;
            } else {
                current = current->next;
            }
        }
    }
}

// Verifies if there is at least one non-mutant male
bool isAdultMalePresent(Bunny* head) {
    Bunny* current = head;
    while (current != nullptr) {
        // Conditions : Sex = Male, Age >= 2, Not Vampire
        if (current->getSexString() == "Male" &&
            current->getAgeBunny() >= 2 &&
            !current->isRadioactive_Mutant_Vampire_Bunny()) {
            return true;
            }
        current = current->next;
    }
    return false;
}

void breedBunnies(Bunny*& head) {
    // Verifying if there's a male, so a dad
    if (!isAdultMalePresent(head))
        return;

    // Temporary list for the babies
    Bunny* babiesHead = nullptr; // The beginning of the list
    Bunny* lastBaby = nullptr;   // The end of the list

    Bunny* current = head;

    // Go through the list to find a mother
    while (current != nullptr) {
        // If female, adult (>=2) & not a vampire
        if (current->getSexString() == "Female" &&
            current->getAgeBunny() >= 2 &&
            !current->isRadioactive_Mutant_Vampire_Bunny()) {

            // Birth
            // Baby gets his/her mother's color
            Bunny* newBaby = new Bunny(current->getColor());

            std::cout << "Bunny " << newBaby->getNameBunny() << " was born!" << std::endl;

            // Insert the baby in the temporary list
            if (babiesHead == nullptr) {
                // If it's the first babt of the list
                babiesHead = newBaby;
                lastBaby = newBaby;
            } else {
                // If there's already another babies, we add him/her to the list
                lastBaby->next = newBaby; // The precedent last points on the new baby
                lastBaby = newBaby;       // The new baby becomes the last
            }
        }
        current = current->next; // go to the next adult
    }

    // If there are babies who were born, we add them to the main list
    if (babiesHead != nullptr) {
        if (head == nullptr) {
            head = babiesHead; // if the main list was empty (impossible)
        } else {
            // Searching the end of the main list
            Bunny* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            // Adding the new babies to the end of the main list
            temp->next = babiesHead;
        }
    }
}

void foodShortage(Bunny*& head) {
    if (lengthBunnyList(head) <= 1000)
        return;
    while (head && (std::rand() % 2 == 0)) {
        Bunny* temp = head;
        head = head->next;
        delete temp;
    }

    if (head) {
        Bunny* current = head;
        while (current->next) {
            if (std::rand() % 2 == 0) { // 1/2 chances to die
                Bunny* temp = current->next;
                current->next = temp->next;
                delete temp;
            } else {
                current = current->next; // Saved !
            }
        }
    }
}

void infectBunnies(Bunny* head) {
    // Counting the vampires
    int vampireCount = 0;
    Bunny* temp = head; // temp to not lose head's address

    while (temp != nullptr) {
        if (temp->isRadioactive_Mutant_Vampire_Bunny()) {
            vampireCount++;
        }
        temp = temp->next;
    }

    // If there's no vampires
    if (vampireCount == 0) return;

    // Go through the list again to infect
    temp = head; // come back to the beginning

    // If there's still bunnies && vampireCount isn't 0
    while (temp != nullptr && vampireCount > 0) {
        // Looking for only normal bunnies
        if (!temp->isRadioactive_Mutant_Vampire_Bunny()) {

            // Transform the victim bunny
            temp->setRadioactive_Mutant_Vampire_Bunny(true);
            std::cout << "Bunny " << temp->getNameBunny() << " has turned into a Vampire!" << std::endl;

            // One infection done :)
            vampireCount--;
        }

        temp = temp->next; // Looking for the new victim -_-
    }
}

void sortBunnies(Bunny* head) {
    if (head == nullptr) return;

    bool sorted = true;

    while (sorted) {

        sorted = false;
        Bunny* current = head;

        while (current->next != nullptr) {

            if (current->getAgeBunny() > current->next->getAgeBunny()) {
                int tempAge = current->getAgeBunny();
                current->setAge(current->next->getAgeBunny());
                current->next->setAge(tempAge);
                Color tempColor = current->getColor();
                current->setColor(current->next->getColor());
                current->next->setColor(tempColor);
                std::string tempName = current->getNameBunny();
                current->setName(current->next->getNameBunny());
                current->next->setName(tempName);
                Sex tempSex = current->getSex();
                current->setSex(current->next->getSex());
                current->next->setSex(tempSex);
                bool tempVampire = current->isRadioactive_Mutant_Vampire_Bunny();
                current->setRadioactive_Mutant_Vampire_Bunny(current->next->isRadioactive_Mutant_Vampire_Bunny());
                current->next->setRadioactive_Mutant_Vampire_Bunny(tempVampire);
                sorted = true;
            }
            current = current->next;
        }
    }
}