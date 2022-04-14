#include <iostream>
#include <vector>
#include <algorithm>
#include <system_error>
#include <map>
#include <string>
#include <sstream>

class InitiativeTracker {
    using Pair = std::pair<std::string, unsigned int>;
public:
    void add(const std::string& name, unsigned int roll) noexcept {
        mNameRollPair.emplace_back(name, roll);
        std::ranges::sort(mNameRollPair, [](const Pair& a, const Pair& b) { return a.second > b.second; });
    }

    void remove(const std::string& name) {
        for (auto it = mNameRollPair.begin(); it != mNameRollPair.end(); ++it) {
            if (it->first == name) {
                mNameRollPair.erase(it);
                return;
            }
        }
        throw std::runtime_error("Name not found! Use help command for usage.");
    }
    void clear() noexcept {
        while (not mNameRollPair.empty()) mNameRollPair.erase(mNameRollPair.begin());
    }
    void print() const noexcept {
        for (const auto& pair : mNameRollPair) std::cout << pair.first << " " << pair.second << std::endl;
    }
private:
    std::vector<Pair> mNameRollPair{};
};

inline void printHelp() {
    std::cout << R"(add     - adds an entry into the tracker        - add "name" "roll"
print   - lists the rolls in descending order   - {no special flags}
remove  - removes an entry from the tracker     - remove "name"
clear   - removes all entries                   - {no special flags}
)";
}

inline void printBanner() {
    std::cout << R"(               ____      _ __  _       __  _               ______                __
              /  _/___  (_) /_(_)___ _/ /_(_)   _____     /_  __/________ ______/ /_____  _____
 ____________ / // __ \/ / __/ / __ `/ __/ / | / / _ \     / / / ___/ __ `/ ___/ //_/ _ \/ ___/___________
/_____/_____// // / / / / /_/ / /_/ / /_/ /| |/ /  __/    / / / /  / /_/ / /__/ ,< /  __/ /  /_____/_____/
           /___/_/ /_/_/\__/_/\__,_/\__/_/_|___/\___/ __ /_/_/_/_  \__,_/\___/_/|_|\___/_/
                                      / __ )__  __   /  |/  (_) /__  _____
 ____________________________________/ __  / / / /  / /|_/ / / / _ \/ ___/_____________________________
/_____/_____/_____/_____/_____/_____/ /_/ / /_/ /  / /  / / / /  __(__  )_____/_____/_____/_____/_____/
                                   /_____/\__, /  /_/  /_/_/_/\___/____/
                                         /____/
)" << std::flush;
}

inline std::string getline() {
    std::string ret;
    std::getline(std::cin, ret);
    return ret;
}



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    printBanner();
    InitiativeTracker initiativeTracker;
    std::string command;
    while (true) {
        std::istringstream iss(getline());
        iss >> command;
        if (command == "help") {
            printHelp();
            continue;
        }
        else if (command == "exit") return 0;
        else if (command == "add") {
            std::string name;
            unsigned int roll;
            iss >> name >> roll;
            if (iss.fail() or not iss.eof()) {
                printHelp();
                continue;
            }
            initiativeTracker.add(name, roll);
            continue;
        }
        else if (command == "print") {
            initiativeTracker.print();
            continue;
        }
        else if (command == "remove") {
            std::string name;
            iss >> name;
            if (iss.fail() or not iss.eof()) {
                printHelp();
                continue;
            }
            try {
                initiativeTracker.remove(name);
            }
            catch (std::runtime_error& e) {
                std::cout << e.what() << std::endl;
            }
            continue;
        }
        else if (command == "clear") initiativeTracker.clear();
        else printHelp();
    }
}