# TASK MANAGER PRO

A tasks/projects manager CLI based application built using pure `C++`
It tracks tasks/projects inputted by the user, their name, description, and whether they are done or not

-------------------------------------------------------------------------

## OVERVIEW

This is a *fully functional console-based tasks/projects tracker* that allows users to:

 - Add tasks/projects
 - View all saved tasks/projects
 - Edit/Delete presaved tasks/projects using their Id
 - Search through tasks/projects
 - Mark tasks/projects as done

All built entirely with C++ without using any external libraries.

-------------------------------------------------------------------------

## FEATURES

| Feature | Description |
| ------- | ----------- |
| **Add Tasks/Projects** | Add tasks or projects by assigning an Id, Name, and Description to each task/project |
| **View Tasks/Projects** | List all saved tasks or projects with formatted output |
| **Search Tasks/Projects** | Search through saved tasks or projects using Id |
| **Edit and Delete Tasks/Projects** | Edit or delete presaved tasks or projects using Id |
| **Save & Load** | Data presists across sessions using text file storage |

-------------------------------------------------------------------------

## TECHNOLOGIES USED

- **C++17+**
- **Standard Template Library (STL)**: `vector`, `string`, `fstream`, `iostream`
- **Object-Oriented Programming (OOP)**: Structured around a `TaskManager`, `Task`, and `Project` classes
- **File Storage**: Plain `.txt` file for presistent data

-------------------------------------------------------------------------

## GETTING STARTED

### PREREQUISITES

 - **C++ Compiler**: `g++`, `clang++`, `MSVC`
 - **Terminal** or command-line interface access

### BUILD INSTRUCTIONS

To compile and run the app from project root:

`g++ src/main.cpp src/TaskManager.cpp src/Task.cpp src/Project.cpp -o manager`
`./manager`
