// task_management.cpp

#include "task_management.h"

using namespace std;

// Function to convert Priority enum to string

string PriorityToString(Priority priority)
{
    switch (priority)
    {
    case Priority::Low:
        return "Low";
    case Priority::Medium:
        return "Medium";
    case Priority::High:
        return "High";
    case Priority::Completed: // Add a case for "TASK COMPLETED"
        return "TASK COMPLETED";
    default:
        return "Unknown";
    }
}
// Function to convert TaskStatus enum to string
string TaskStatusToString(TaskStatus status)
{
    switch (status)
    {
    case TaskStatus::Pending:
        return "Pending";
    case TaskStatus::Completed:
        return "Completed";
    default:
        return "Unknown";
    }
}

// Functions to manage users
void AddUser(vector<User> &users, int id, const string &name)
{
    users.push_back(User(id, name));
    cout << "User added: " << name << endl;
}

void ViewUsers(const vector<User> &users)
{
    for (const auto &user : users)
    {
        cout << "User ID: " << user.GetUserID() << " - Name: " << user.GetName() << endl;
    }
}

void RemoveUser(vector<User> &users, int userID)
{
    auto it = remove_if(users.begin(), users.end(), [userID](const User &user)
                             { return user.GetUserID() == userID; });

    if (it != users.end())
    {
        users.erase(it, users.end());
        cout << "User removed with ID: " << userID << endl;
    }
    else
    {
        cout << "User not found with ID: " << userID << endl;
    }
}

// Improved UI for Menu
void displayMenu()
{
    cout << "\n********** Task Management System Menu **********\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks for users\n";
    cout << "3. View Tasks with Deadlines\n";
    cout << "4. Set Task Priority\n";
    cout << "5. Remove Task\n";
    cout << "6. View Tasks in Category\n";
    cout << "7. View Tasks with Deadline\n";
    cout << "8. Mark Task as Complete\n";
    cout << "9. Add User\n";
    cout << "10. View Users\n";
    cout << "11. Remove User\n";
    cout << "0. Exit\n";
    cout << "************************************************\n";
}

