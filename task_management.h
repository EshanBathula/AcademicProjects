#ifndef TASK_MANAGEMENT_H
#define TASK_MANAGEMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Forward declarations
class BaseTask;
enum class CategoryType;
enum class Priority;
enum class TaskStatus;
string PriorityToString(Priority priority);
string TaskStatusToString(TaskStatus status);

// Enumeration for task priority levels
enum class Priority
{
    Low = 1,
    Medium,
    High,
    Completed // Additional priority level for completed tasks
};

// Enumeration for task category types
enum class CategoryType
{
    Work = 1,
    Personal,
    Shopping,
    Health,
    Education,
    General
};

// Enumeration for task status (pending or completed)
enum class TaskStatus
{
    Pending,
    Completed
};

// Abstract base class for tasks
class BaseTask
{
protected:
    int taskID;
    string description;
    Priority priority;
    TaskStatus status;

public:
    // Constructor for BaseTask
    BaseTask(int id, const string &desc, Priority pri = Priority::Medium)
        : taskID(id), description(desc), priority(pri), status(TaskStatus::Pending) {}

    // Virtual destructor for BaseTask
    virtual ~BaseTask() {}

    // Abstract methods to be implemented by derived classes
    virtual void SetPriority(Priority pri) = 0;
    virtual void MarkAsComplete() = 0;

    // Getter methods for task properties
    int GetTaskID() const { return taskID; }
    string GetDescription() const { return description; }
    Priority GetPriority() const { return priority; }
    TaskStatus GetStatus() const { return status; }
};

// Derived class representing a specific task
class Task : public BaseTask
{
private:
    string deadline;
    CategoryType category;

public:
    // Constructor for Task
    Task(int id, const string &desc, Priority pri = Priority::Medium, const string &dl = "", CategoryType cat = CategoryType::General)
        : BaseTask(id, desc, pri), category(cat) {}

    // Implementation of virtual method to set task priority
    void SetPriority(Priority pri) override
    {
        priority = pri;
        cout << "Priority set to " << PriorityToString(pri) << endl;
    }

    // Method to set task deadline
    void SetDeadline(const string &dl)
    {
        deadline = dl;
        cout << "Deadline set to " << dl << endl;
    }

    // Implementation of virtual method to mark task as completed
    void MarkAsComplete() override
    {
        status = TaskStatus::Completed;
        priority = Priority::Completed; // Update priority to "TASK COMPLETED"
        cout << "Task marked as completed." << endl;
    }

    // Getter methods for task properties
    string GetDeadline() const { return deadline; }
    CategoryType GetCategory() const { return category; }
};

// Class representing a category of tasks
class Category
{
private:
    int categoryID;
    string name;
    string description;
    vector<Task *> tasks;

public:
    // Constructor for Category
    Category(int id, const string &name, const string &desc)
        : categoryID(id), name(name), description(desc) {}

    // Method to add a task to the category
    void AddTask(Task *task)
    {
        tasks.push_back(task);
        cout << "Task added to category: " << name << endl;
    }

    // Method to remove a task from the category
    void RemoveTask(int taskID)
    {
        auto it = find_if(tasks.begin(), tasks.end(), [taskID](const Task *task)
                           { return task->GetTaskID() == taskID; });

        if (it != tasks.end())
        {
            tasks.erase(it);
            cout << "Task removed from category: " << name << endl;
        }
        else
        {
            cout << "Task not found in category: " << name << endl;
        }
    }

    // Method to view tasks in the category
    void ViewTasks() const
    {
        cout << "Tasks in category: " << name << endl;
        for (const auto &task : tasks)
        {
            cout << "Task ID: " << task->GetTaskID() << ", Description: " << task->GetDescription() << ", Category: " << static_cast<int>(task->GetCategory()) << endl;
        }
    }

    // Getter methods for category properties
    int GetCategoryID() const { return categoryID; }
    string GetName() const { return name; }
    string GetDescription() const { return description; }
};

// Class representing a deadline for tasks
class Deadline
{
private:
    int deadlineID;
    string date;
    string time;
    vector<Task *> tasks;

public:
    // Constructor for Deadline
    Deadline(int id, const string &date, const string &time)
        : deadlineID(id), date(date), time(time) {}

    // Method to set the date of the deadline
    void SetDate(const string &newDate)
    {
        date = newDate;
        cout << "Deadline date set to: " << newDate << endl;
    }

    // Method to set the time of the deadline
    void SetTime(const string &newTime)
    {
        time = newTime;
        cout << "Deadline time set to: " << newTime << endl;
    }

    // Method to add a task to the deadline
    void AddTask(Task *task)
    {
        if (task != nullptr)
        {
            tasks.push_back(task);
            cout << "Task added to deadline." << endl;
        }
    }

    // Method to view tasks with the deadline
    void ViewTasks() const
    {
        cout << "Tasks with deadline " << deadlineID << " (" << date << " " << time << "):" << endl;
        for (const auto &task : tasks)
        {
            cout << "Task ID: " << task->GetTaskID() << "\nDescription: " << task->GetDescription() << "\nPriority: " << PriorityToString(task->GetPriority()) << endl;
        }
    }

    // Getter methods for deadline properties
    int GetDeadlineID() const { return deadlineID; }
    string GetDate() const { return date; }
    string GetTime() const { return time; }
};

// Class representing a user
class User
{

private:
    int userID;
    string name;
    vector<string> preferences;
    vector<Task> tasks; // Store Task objects directly

public:
    // Constructor for User
    User(int id, const string &name) : userID(id), name(name) {}

    // Method to add a preference for the user
    void AddPreference(const string &preference)
    {
        preferences.push_back(preference);
    }

    // Method to get mutable reference to user tasks
    vector<Task>& GetTasks()
    {
        return tasks;
    }

    // Method to get immutable reference to user tasks
    const vector<Task>& GetTasks() const
    {
        return tasks;
    }

    // Method to remove a preference for the user
    void RemovePreference(const string &preference)
    {
        auto it = remove(preferences.begin(), preferences.end(), preference);
        if (it != preferences.end())
        {
            preferences.erase(it, preferences.end());
        }
    }

    // Method to view user preferences
    void ViewPreferences() const
    {
        cout << "Preferences for user " << name << ":" << endl;
        for (const auto &pref : preferences)
        {
            cout << pref << endl;
        }
    }

    // Method to add a task for the user
    void AddTask(const Task &task)
    {
        tasks.push_back(task);
        cout << "Task added for user: " << name << endl;
    }

    // Method to remove a task for the user
    void RemoveTask(int taskID)
    {
        auto it = find_if(tasks.begin(), tasks.end(), [taskID](const Task &task)
                           { return task.GetTaskID() == taskID; });

        if (it != tasks.end())
        {
            tasks.erase(it);
            cout << "Task removed for user: " << name << endl;
        }
        else
        {
            cout << "Task not found for user: " << name << endl;
        }
    }

    // Method to view tasks for the user
    void ViewTasks() const
    {
        cout << "Tasks for user: " << name << endl;
        for (const auto &task : tasks)
        {
            cout << "Task ID: " << task.GetTaskID() << "\nDescription: " << task.GetDescription() << "\nPriority: " << PriorityToString(task.GetPriority()) << endl;
        }
    }

    // Method to set priority for a task of the user
    void SetPriority(int taskID, Priority priority)
    {
        auto it = find_if(tasks.begin(), tasks.end(), [taskID](const Task &task)
                           { return task.GetTaskID() == taskID; });

        if (it != tasks.end())
        {
            it->SetPriority(priority);
            cout << "Priority updated for task: " << taskID << " for user: " << name << endl;
        }
        else
        {
            cout << "Task not found for user: " << name << endl;
        }
    }

    // Method to check if the user has a specific task
    bool HasTask(int taskID) const
    {
        auto it = find_if(tasks.begin(), tasks.end(), [taskID](const Task &task)
                           { return task.GetTaskID() == taskID; });

        return it != tasks.end();
    }

    // Getter methods for user properties
    int GetUserID() const { return userID; }
    string GetName() const { return name; }
};

// Function to add a user to the vector of users
void AddUser(vector<User> &users, int id, const string &name);

// Function to view users in the vector of users
void ViewUsers(const vector<User> &users);

// Function to remove a user from the vector of users
void RemoveUser(vector<User> &users, int userID);

// Function to display the menu for the task management system
void displayMenu();

#endif // TASK_MANAGEMENT_H
