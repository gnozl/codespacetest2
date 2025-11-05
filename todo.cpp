#include <iostream>
#include <string>
using namespace std;

class Task {
private:
    string name;
    bool completed;
public:
    Task(const string &n) : name(n), completed(false) {}
    const string &getName() const { return name; }
    bool isCompleted() const { return completed; }
    void markComplete() { completed = true; }
};

class TaskList {
private:
    vector<Task> tasks;
public:
    // Add a task by name
    void addTask(const string &name) {
        tasks.emplace_back(name);
        cout << "Added task: '" << name << "'\n";
    }

    // Mark a task complete by name; returns true if found
    bool markComplete(const string &name) {
        for (auto &t : tasks) {
            if (t.getName() == name) {
                if (!t.isCompleted()) {
                    // need non-const reference; tasks holds Task objects
                    // but t is a Task&, so we can call markComplete through a little trick
                    const_cast<Task&>(t).markComplete();
                }
                cout << "Marked complete: '" << name << "'\n";
                return true;
            }
        }
        cout << "Task not found: '" << name << "'\n";
        return false;
    }

    // Remove a task by name; returns true if removed
    bool removeTask(const string &name) {
        auto it = remove_if(tasks.begin(), tasks.end(), [&](const Task &t){ return t.getName() == name; });
        if (it != tasks.end()) {
            tasks.erase(it, tasks.end());
            cout << "Removed task: '" << name << "'\n";
            return true;
        }
        cout << "Task not found: '" << name << "'\n";
        return false;
    }

    // List tasks
    void listTasks() const {
        if (tasks.empty()) {
            cout << "No tasks in the list.\n";
            return;
        }
        cout << "Tasks:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            const Task &t = tasks[i];
            cout << " " << (i+1) << ") " << t.getName() << " [" << (t.isCompleted() ? "x" : " ") << "]\n";
        }
    }
};

// Helper to read a full line (trim leading newline after reading an integer choice)
static string readLineTrimmed() {
    string line;
    // Use getline to allow spaces in task names
    if (!std::getline(cin, line)) return string();
    // Trim trailing and leading spaces
    auto l = line.find_first_not_of(" \t\r\n");
    if (l == string::npos) return string();
    auto r = line.find_last_not_of(" \t\r\n");
    return line.substr(l, r - l + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    TaskList list;
    while (true) {
        cout << "\nSimple ToDo List - choose an option:\n";
        cout << " 1) Add task\n 2) Mark complete\n 3) Remove task\n 4) List tasks\n 5) Quit\n";
        cout << "Enter choice: ";
        string choiceStr;
        if (!getline(cin, choiceStr)) break;
        int choice = 0;
        try { choice = stoi(choiceStr); } catch(...) { choice = 0; }

        if (choice == 1) {
            cout << "Enter task name: ";
            string name = readLineTrimmed();
            if (name.empty()) { cout << "Empty name, cancelled.\n"; continue; }
            list.addTask(name);
        } else if (choice == 2) {
            cout << "Enter task name to mark complete: ";
            string name = readLineTrimmed();
            if (name.empty()) { cout << "Empty name, cancelled.\n"; continue; }
            list.markComplete(name);
        } else if (choice == 3) {
            cout << "Enter task name to remove: ";
            string name = readLineTrimmed();
            if (name.empty()) { cout << "Empty name, cancelled.\n"; continue; }
            list.removeTask(name);
        } else if (choice == 4) {
            list.listTasks();
        } else if (choice == 5) {
            cout << "Goodbye.\n";
            break;
        } else {
            cout << "Invalid choice. Enter a number 1-5.\n";
        }
    }

    return 0;
}
