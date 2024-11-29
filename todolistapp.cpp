#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>  // For std::numeric_limits

// Task structure to store task details
struct Task {
    std::string description;
    bool isCompleted;

    // Constructor to initialize task
    Task(const std::string& desc) : description(desc), isCompleted(false) {}
};

// Class to represent the To-Do List
class TodoList {
private:
    std::vector<Task> tasks;  // Vector to store tasks

public:
    // Add a task to the list
    void addTask(const std::string& description) {
        tasks.push_back(Task(description));
    }

    // Display all tasks
    void viewTasks() {
        if (tasks.empty()) {
            std::cout << "No tasks available!" << std::endl;
        } else {
            std::cout << "Todo List:" << std::endl;
            for (size_t i = 0; i < tasks.size(); ++i) {
                std::cout << (i + 1) << ". " 
                          << tasks[i].description 
                          << (tasks[i].isCompleted ? " [Completed]" : " [Pending]") 
                          << std::endl;
            }
        }
    }

    // Mark a task as completed
    void markTaskComplete(int taskIndex) {
        if (taskIndex >= 0 && taskIndex < tasks.size()) {
            tasks[taskIndex].isCompleted = true;
            std::cout << "Task marked as completed!" << std::endl;
        } else {
            std::cout << "Invalid task index!" << std::endl;
        }
    }

    // Delete a task from the list
    void deleteTask(int taskIndex) {
        if (taskIndex >= 0 && taskIndex < tasks.size()) {
            tasks.erase(tasks.begin() + taskIndex);
            std::cout << "Task deleted!" << std::endl;
        } else {
            std::cout << "Invalid task index!" << std::endl;
        }
    }

    // Save the tasks to a file
    void saveToFile() {
        std::ofstream outFile("todo_list.txt");
        if (outFile.is_open()) {
            for (const auto& task : tasks) {
                outFile << task.description << "|" << task.isCompleted << std::endl;
            }
            outFile.close();
            std::cout << "Tasks saved to 'todo_list.txt'!" << std::endl;
        } else {
            std::cout << "Failed to save tasks!" << std::endl;
        }
    }

    // Load tasks from a file (clear previous tasks)
    void loadFromFile() {
        std::ifstream inFile("todo_list.txt");
        std::string line;
        tasks.clear(); // Clear previous tasks

        while (getline(inFile, line)) {
            size_t delimiterPos = line.find('|');
            if (delimiterPos != std::string::npos) {
                std::string description = line.substr(0, delimiterPos);
                bool isCompleted = (line.substr(delimiterPos + 1) == "1");
                tasks.push_back(Task(description));
                tasks.back().isCompleted = isCompleted;
            }
        }
        inFile.close();
    }
};

// Function to display the menu
void displayMenu() {
    std::cout << "\n==== To-Do List Menu ====" << std::endl;
    std::cout << "1. Add Task" << std::endl;
    std::cout << "2. View Tasks" << std::endl;
    std::cout << "3. Mark Task as Completed" << std::endl;
    std::cout << "4. Delete Task" << std::endl;
    std::cout << "5. Save Tasks to File" << std::endl;
    std::cout << "6. Load Tasks from File" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "=========================" << std::endl;
}

int main() {
    TodoList todoList;
    todoList.loadFromFile(); // Load tasks from file when starting the application

    int choice;
    std::string description;
    int taskIndex;

    while (true) {
        displayMenu();
        std::cout << "Enter your choice: ";
        
        // Ensure the user inputs a valid choice
        if (!(std::cin >> choice)) {
            std::cin.clear();  // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
            std::cout << "Invalid input. Please enter a valid option." << std::endl;
            continue;  // Skip the rest of the loop and ask for input again
        }

        std::cin.ignore(); // To clear the newline character from the input buffer

        switch (choice) {
            case 1:  // Add Task
                std::cout << "Enter task description: ";
                std::getline(std::cin, description);  // Use getline for string input
                todoList.addTask(description);
                break;

            case 2:  // View Tasks
                todoList.viewTasks();
                break;

            case 3:  // Mark Task as Completed
                std::cout << "Enter task number to mark as completed: ";
                std::cin >> taskIndex;
                std::cin.ignore(); // Clear input buffer
                todoList.markTaskComplete(taskIndex - 1); // 0-based index
                break;

            case 4:  // Delete Task
                std::cout << "Enter task number to delete: ";
                std::cin >> taskIndex;
                std::cin.ignore(); // Clear input buffer
                todoList.deleteTask(taskIndex - 1); // 0-based index
                break;

            case 5:  // Save Tasks to File
                todoList.saveToFile();
                break;

            case 6:  // Load Tasks from File
                todoList.loadFromFile();
                break;

            case 7:  // Exit
                std::cout << "Exiting... Goodbye!" << std::endl;
                return 0;  // Exit the program cleanly

            default:
                std::cout << "Invalid choice, please try again." << std::endl;
        }
    }

    return 0;
}
