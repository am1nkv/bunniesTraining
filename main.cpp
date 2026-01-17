#include "Bunny.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    auto* bunnyList = new Bunny();

    // Create initial bunnies
    int nb = 5;
    for (int i = 1; i < nb; ++i) {
        bunnyList->appendBunny2();
    }

    std::cout << "INITIAL POPULATION" << std::endl;
    std::cout << "Total bunnies : " << lengthBunnyList(bunnyList) << std::endl;
    showBunnies(bunnyList);

    // Turn-based system
    int turn = 1;
    while (bunnyList != nullptr) {
        std::cout << "\n=TURN : " << turn << std::endl;

        // Age all bunnies
        bunnyList->anniversaryBunny();

        breedBunnies(bunnyList);

        infectBunnies(bunnyList);

        // Remove dead bunnies
        removeDeadBunnies(bunnyList);

        foodShortage(bunnyList);

        // Show remaining bunnies
        if (bunnyList != nullptr) {
            std::cout << "\nRemaining bunnies: " << lengthBunnyList(bunnyList) << std::endl;
            showBunnies(bunnyList);
        } else {
            std::cout << "\nAll bunnies have died... Game over!" << std::endl;
        }

        // std::cout << "Press Enter for next turn...";
        // std::cin.get();

        turn++;
    }

    freeBunnies(bunnyList);

    return 0;
}