#include "include/LogManager.hpp"

int main() {
    int selected;
    std::string jsonPath = "logs/your_log.json";
    hk::LogManager manager(jsonPath);
    manager.save();

    while (true) {
        manager.showMenu();
        selected = manager.checkInput<int>("Enter option: ");

        switch (selected) {
            case 1:
                manager.createNewLog();
                break;
            case 2:
                manager.editLog();
                break;
            case 3:
                manager.deleteLog();
                break;
            case 4:
                manager.recordsLog();
                break;
            case 5:
                manager.historyLog();
                break;
            default:
                std::cout << "Invalid option" << std::endl;

        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    return 0;

}