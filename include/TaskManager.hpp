#include <iostream>
#include <fstream>
#include <vector>
#include "Task.hpp"
#include "Project.hpp"
#pragma once

class TaskManager
{
private:
    bool is_tasks_file;
    std::string tasks_file_path;
    bool is_projects_file;
    std::string projects_file_path;
    std::vector<Task> tasks;
    std::vector<Project> projects;

    std::vector<std::string> Split(std::string string, char splitter);
public:
    TaskManager(std::string tasks_filepath, std::string projects_filepath);
    void run();
    void TaskRun();
    void ProjectRun();
    void AddTask();
    void EditTask();
    void DeleteTask();
    void ViewAllTasks();
    void SearchTasks();
    void MarkTaskStatus();
    void AddProject();
    void EditProject();
    void DeleteProject();
    void ViewAllProjects();
    void SearchProjects();
    void MarkProjectStatus();
    void SaveToFile();
    void LoadFromFile();
};
