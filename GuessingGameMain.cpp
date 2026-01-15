#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

struct Stats {
    int gamesPlayed = 0;
    int wins = 0;
    int bestScore = 999;
};

void loadStats(Stats& stats) {
    std::ifstream file("stats.txt");
    if (file.is_open()) {
        file >> stats.gamesPlayed >> stats.wins >> stats.bestScore;
        file.close();
    }
}

void saveStats(const Stats& stats) {
    std::ofstream file("stats.txt");
    if (file.is_open()) {
        file << stats.gamesPlayed << " " << stats.wins << " " << stats.bestScore;
        file.close();
    }
}

int main() {
    srand(time(0));
    Stats stats;
    loadStats(stats);

    while (true) {
        std::cout << "\n=== Number Guessing Game ===\n";
        std::cout << "Games played: " << stats.gamesPlayed << " | Wins: " << stats.wins;
        if (stats.wins > 0) std::cout << " | Best: " << stats.bestScore << " tries";
        std::cout << "\n1. Play (1-100)\n2. Quit\nChoose: ";

        int choice;
        std::cin >> choice;
        if (choice != 1) break;

        int secret = rand() % 100 + 1;
        int guess, tries = 0;

        std::cout << "Guess the number (1-100): ";
        while (true) {
            std::cin >> guess;
            tries++;
            if (guess == secret) {
                std::cout << "You win in " << tries << " tries!\n";
                stats.wins++;
                if (tries < stats.bestScore) stats.bestScore = tries;
                break;
            } else if (guess < secret) {
                std::cout << "Too low! Try again: ";
            } else {
                std::cout << "Too high! Try again: ";
            }
        }
        stats.gamesPlayed++;
    }

    saveStats(stats);
    std::cout << "Thanks for playing!\n";
    return 0;
}