#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

class ToDoList {
private:
    std::vector<std::string> tasks;

public:
    // Load tasks from file on program start
    ToDoList() {
        loadTasksFromFile("tasks.txt");
    }

    void addTask(const std::string& task) {
        tasks.push_back(task);
        std::cout << "Task added: " << task << std::endl;
        saveTasksToFile("tasks.txt"); // Save tasks to file after adding
        std::cout << "---------------------------------" << std::endl;
    }

    void displayTasks() {
        std::cout << "---------------------------------" << std::endl;

        if (tasks.empty()) {
            std::cout << "No tasks in the list." << std::endl;
        } else {
            std::cout << "Tasks:" << std::endl;
            for (size_t i = 0; i < tasks.size(); ++i) {
                std::cout << i + 1 << ". " << tasks[i] << std::endl;
            }
        }
        std::cout << "---------------------------------" << std::endl;
    }

    void removeTask(size_t index) {
        if (index > 0 && index <= tasks.size()) {
            std::cout << "Task removed: " << tasks[index - 1] << std::endl;
            tasks.erase(tasks.begin() + index - 1);
            saveTasksToFile("tasks.txt"); // Save tasks to file after removing
        } else {
            std::cout << "Invalid task number." << std::endl;
        }
    }

    // Save tasks to file
    void saveTasksToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const std::string& task : tasks) {
                file << task << std::endl;
            }
            file.close();
        } else {
            std::cerr << "Unable to open file for writing." << std::endl;
        }
    }

    // Load tasks from file
    void loadTasksFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string task;
            while (std::getline(file, task)) {
                tasks.push_back(task);
            }
            file.close();
        } else {
            std::cerr << "No existing tasks file found. Starting with an empty list." << std::endl;
        }
    }
};

int main() {
    ToDoList myList;
    int choice;
    std::string task;
    size_t index;

    do {
        system(CLEAR_SCREEN);
        std::cout << "\nMy To-Do List" << std::endl;
        std::cout << "1. Add Task" << std::endl;
        std::cout << "2. Display Tasks" << std::endl;
        std::cout << "3. Remove Task" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid option." << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.get();
            continue;
        }

        switch (choice) {
            case 1:
                std::cout << "Enter task to add: ";
                std::cin.ignore(); // Clear the buffer
                std::getline(std::cin, task);
                myList.addTask(task);
                break;
            case 2:
                myList.displayTasks();
                break;
            case 3:
                std::cout << "Enter task number to remove: ";
                myList.displayTasks();
                std::cin >> index;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a valid number." << std::endl;
                    std::cout << "Press Enter to continue...";
                    std::cin.get();
                    break;
                }
                myList.removeTask(index);
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
                break;
        }

        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get(); // Wait for user input before clearing the screen
    } while (choice != 4);

    return 0;
}
