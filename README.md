Task Management System
This repository contains a simple Task Management System implemented in C++. The system allows users to manage tasks, set priorities, assign deadlines, and organize tasks into categories. The implementation includes features such as user management, task assignment, viewing tasks, and more.

Files
main.cpp: The main program that interacts with the user through a console-based menu system. It handles the core functionality of adding tasks, viewing tasks, setting priorities, and managing users.

task_management.cpp: Contains various functions related to task management, including the conversion of enums to strings, user management functions (add, view, remove), and an improved user interface for displaying the menu.

task_management.h: Header file defining classes, enums, and function prototypes used in the Task Management System. It includes the declaration of classes like BaseTask, Task, Category, Deadline, and User, as well as functions for user management and menu display.

Compilation and Execution
To compile and run the Task Management System, you can use a C++ compiler. Here's an example using g++:

bash
Copy code
g++ main.cpp task_management.cpp -o task_management
./task_management
Follow the on-screen instructions to interact with the Task Management System.

Usage
Adding a Task: Choose option 1 from the menu, enter task details such as description, category, priority, and deadline.

Viewing Tasks: Option 2 allows you to view tasks for each user.

Setting Task Priority: Use option 4 to set the priority of a task.

Removing a Task: Option 5 allows you to remove a task by entering its ID.

Viewing Tasks by Category: Option 6 enables you to view tasks in a specific category.

Viewing Tasks with Deadline: Option 7 allows you to view tasks associated with a specific deadline.

Marking Task as Complete: Choose option 8 to mark a task as complete.

User Management: Options 9, 10, and 11 provide functionality for adding, viewing, and removing users.

Exiting the System: Choose option 0 to exit the Task Management System.

Dependencies
This program relies on the C++ standard library and does not have external dependencies.

Feel free to explore and enhance the Task Management System as needed for your use case. If you encounter any issues or have suggestions for improvement, please create an issue or submit a pull request.
