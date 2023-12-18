// main.cpp

#include "task_management.h"
#include <algorithm>
#include <limits>

using namespace std;

int main()
{
    vector<User> users;
    vector<Category> categories;
    vector<Deadline> deadlines;
    vector<Task> tasks;

    int userIDCounter = 1;
    int taskIDCounter = 1;
    int categoryIDCounter = 1;
    int deadlineIDCounter = 1;

    while (true)
    {
        displayMenu();

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string description;

            cout << "Enter task description: ";
            cin.ignore(); // Ignore newline character from previous input
            getline(cin, description);

            Priority priority;
            CategoryType selectedCategory = CategoryType::General; // Default category
            while (true)
            {
                cout << "Select a category (1: Work, 2: Personal, 3: Shopping, 4: Health, 5: Education, 6: General): ";
                int categoryChoice;
                if (cin >> categoryChoice && categoryChoice >= 1 && categoryChoice <= 6)
                {
                    selectedCategory = static_cast<CategoryType>(categoryChoice);
                    break; // Exit the loop if input is valid
                }
                else
                {
                    cout << "Invalid category. Please enter a number between 1 and 6." << endl;
                    cin.clear();                                                   // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                }
            }

            // Allow the user to choose a priority with input validation
            while (true)
            {
                cout << "Enter task priority (1: Low, 2: Medium, 3: High): ";
                int priorityChoice;
                if (cin >> priorityChoice && priorityChoice >= 1 && priorityChoice <= 3)
                {
                    switch (priorityChoice)
                    {
                    case 1:
                        priority = Priority::Low;
                        break;
                    case 2:
                        priority = Priority::Medium;
                        break;
                    case 3:
                        priority = Priority::High;
                        break;
                    }

                    break; // Exit the loop if input is valid
                }
                else
                {
                    cout << "Invalid priority. Please enter a number between 1 and 3." << endl;
                    cin.clear();                                                   // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                }
            }

            // Set deadline using Deadline class
            string deadlineDate;
            string deadlineTime;
            while (true)
            {
                cout << "Enter deadline date (format: YYYY-MM-DD): ";
                if (cin >> deadlineDate)
                {
                    // Check if the entered date has the correct format (YYYY-MM-DD)
                    if (deadlineDate.size() == 10 &&
                        deadlineDate[4] == '-' &&
                        deadlineDate[7] == '-' &&
                        all_of(deadlineDate.begin(), deadlineDate.end(), [](char c)
                                    { return isdigit(c) || c == '-'; }))
                    {
                        break; // Exit the loop if input is valid
                    }
                    else
                    {
                        cout << "Invalid date format. Please enter the date in YYYY-MM-DD format." << endl;
                        cin.clear();                                                   // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    }
                }
                else
                {
                    cout << "Invalid input. Please enter the date in YYYY-MM-DD format." << endl;
                    cin.clear();                                                   // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                }
            }
            while (true)
            {
                cout << "Enter deadline time (format: HH:MM): ";
                if (cin >> deadlineTime)
                {
                    // Check if the entered time has the correct format (HH:MM)
                    if (deadlineTime.size() == 5 &&
                        deadlineTime[2] == ':' &&
                        all_of(deadlineTime.begin(), deadlineTime.end(), [](char c)
                                    { return isdigit(c) || c == ':'; }))
                    {
                        break; // Exit the loop if input is valid
                    }
                    else
                    {
                        cout << "Invalid time format. Please enter the time in HH:MM format." << endl;
                        cin.clear();                                                   // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    }
                }
                else
                {
                    cout << "Invalid input. Please enter the time in HH:MM format." << endl;
                    cin.clear();                                                   // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                }
            }

            // Create Deadline object
            Deadline deadline(deadlineIDCounter++, deadlineDate, deadlineTime);

            Task newTask(taskIDCounter++, description, priority, deadlineDate, selectedCategory);
            tasks.push_back(newTask);

            // Add the task to the Deadline
            deadline.AddTask(&tasks.back());

            int userID;

            // Allow the user to enter a valid user ID
            while (true)
            {
                cout << "Enter user ID to assign the task: ";
                if (cin >> userID)
                {
                    break; // Exit the loop if input is valid
                }
                else
                {
                    cout << "Invalid user ID. Please enter a valid integer." << endl;
                    cin.clear();                                                   // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                }
            }

            auto userIt = find_if(users.begin(), users.end(), [userID](const User &user)
                                       { return user.GetUserID() == userID; });

            if (userIt != users.end())
            {
                userIt->AddTask(newTask);
            }
            else
            {
                cout << "User not found with ID: " << userID << endl;
            }

            break;
        }

        case 2:
        {
            for (const auto &user : users)
            {
                user.ViewTasks(); 
                cout << "-----------------------------" << endl;
            }
            break;
        }

        case 3:
        {
            // View Tasks with Deadlines
            for (const auto &deadline : deadlines)
            {
                deadline.ViewTasks();
            }
            break;
        }

        case 4:
        {
            // Set Task Priority
            int taskID;
            int userPriorityChoice;
            Priority priority;

            cout << "Enter task ID: ";
            cin >> taskID;

            cout << "Enter priority (1: Low, 2: Medium, 3: High): ";
            cin >> userPriorityChoice;

            switch (userPriorityChoice)
            {
            case 1:
                priority = Priority::Low;
                break;
            case 2:
                priority = Priority::Medium;
                break;
            case 3:
                priority = Priority::High;
                break;
            default:
                priority = Priority::Medium;
                cout << "Invalid priority. Setting to Medium by default." << endl;
            }

            bool taskFound = false;
            for (auto &user : users)
            {
                if (user.HasTask(taskID))
                {
                    user.SetPriority(taskID, priority);
                    taskFound = true;
                }
            }

            if (!taskFound)
            {
                cout << "Task with ID " << taskID << " not found in any user." << endl;
            }

            break;
        }

        case 5:
        {
            // Remove Task
            int taskID;
            cout << "Enter task ID: ";
            cin >> taskID;

            for (auto &user : users)
            {
                user.RemoveTask(taskID);
            }

            break;
        }

        case 6:
        {
            cout << "Select a category (1: Work, 2: Personal, 3: Shopping, 4: Health, 5: Education, 6: General): ";
            int categoryChoice;

            while (true)
            {
                if (cin >> categoryChoice && categoryChoice >= 1 && categoryChoice <= 6)
                {
                    break; // Exit the loop if input is valid
                }
                else
                {
                    cout << "Invalid category choice. Please enter a number between 1 and 6." << endl;
                    cin.clear();                                                   // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                }
            }

            CategoryType selectedCategory = static_cast<CategoryType>(categoryChoice);
            if (selectedCategory < CategoryType::Work || selectedCategory > CategoryType::General)
            {
                cout << "Invalid category choice." << endl;
                break;
            }

            cout << "Tasks in category " << static_cast<int>(selectedCategory) << ":\n";
            for (const auto &task : tasks)
            {
                if (task.GetCategory() == selectedCategory)
                {
                    cout << "Task ID: " << task.GetTaskID() << ", Description: " << task.GetDescription() << ", Priority: " << PriorityToString(task.GetPriority()) << endl;
                }
            }

            break;
        }

        case 7:
        {
            // View Tasks with Deadline
            int deadlineID;
            cout << "Enter deadline ID: ";
            cin >> deadlineID;

            auto deadlineIt = find_if(deadlines.begin(), deadlines.end(), [deadlineID](const Deadline &deadline)
                                           { return deadline.GetDeadlineID() == deadlineID; });

            if (deadlineIt != deadlines.end())
            {
                deadlineIt->ViewTasks();
            }
            else
            {
                cout << "Deadline not found with ID: " << deadlineID << endl;
            }

            break;
        }

        case 8:
        {
            // Mark Task as Complete
            int taskID;
            cout << "Enter task ID to mark as complete: ";
            cin >> taskID;

            for (auto &user : users)
            {
                for (auto &task : user.GetTasks()) // Iterate over tasks directly
                {
                    if (task.GetTaskID() == taskID)
                    {
                        task.MarkAsComplete();
                        cout << "Task marked as complete for user: " << user.GetName() << endl;
                        break; // Stop searching after finding the task
                    }
                }
            }

            break;
        }

        case 9:
        {
            // Add User
            string name;
            cout << "Enter user name: ";
            cin.ignore();
            getline(cin, name);

            AddUser(users, userIDCounter++, name);
            break;
        }
        case 10:
        {
            // View Users
            ViewUsers(users);
            break;
        }
        case 11:
        {
            // Remove User
            int userID;
            cout << "Enter user ID: ";
            cin >> userID;

            RemoveUser(users, userID);
            break;
        }
        case 0:
            // Exit
        	cout << "Thank you for using the Task Management Service. Have a great day!";
            return 0;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
