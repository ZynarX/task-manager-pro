#include <iostream>
#include "../include/TaskManager.hpp"

TaskManager::TaskManager(std::string tasks_filepath, std::string projects_filepath)
{
    std::ifstream tasksFileOutput;
    tasksFileOutput.open(tasks_filepath);

    if(tasksFileOutput.is_open())
    {
        this->tasks_file_path = tasks_filepath;
        this->is_tasks_file = true;
        tasksFileOutput.close();
    }
    else
    {
        std::ofstream tasksFile;
        tasksFile.open(tasks_filepath, std::ios::out | std::ios::trunc);

        if(tasksFile.is_open())
        {
            this->tasks_file_path = tasks_filepath;
            this->is_tasks_file = true;
            tasksFile.close();
        }
    }

    std::ifstream projectsFileOutput;
    projectsFileOutput.open(projects_filepath);

    if(projectsFileOutput.is_open())
    {
        this->projects_file_path = projects_filepath;
        this->is_projects_file = true;
        projectsFileOutput.close();
    }
    else
    {
        std::ofstream projectsFile;
        projectsFile.open(projects_filepath, std::ios::out | std::ios::trunc);

        if(projectsFile.is_open())
        {
            this->projects_file_path = projects_filepath;
            this->is_projects_file = true;
            projectsFile.close();
        }
    }
    
            
    this->LoadFromFile();
}

std::vector<std::string> TaskManager::Split(std::string string, char splitter)
{
    std::vector<std::string> output = {};
    std::string curString = "";

    for(int i = 0; i < string.length(); i++)
    {
        if(string[i] == splitter)
        {
            output.push_back(curString);
            curString = "";
        }
        else
        {
            curString += string[i];
        }
    }

    output.push_back(curString);

    return output;
}

void TaskManager::run()
{
    int TorP;

    do
    {
        try
        {
            std::cout << "============ Task Manager Pro ============\n";
            std::cout << "1. Adjust Tasks\n2. Adjust Projects\n3. Quit\n\nChoose an option: ";
            std::cin >> TorP;
            
            switch (TorP)
            {
                case 1:
                    TaskRun();
                    break;
                case 2:
                    ProjectRun();
                    break;
                case 3:
                    std::cout << "Quitting program...\n\n";
                    break;
                default:
                    std::cout << "Invalid option!\n";
                    break;
            }
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
    } while (TorP != 3);

    this->SaveToFile();
    
}


void TaskManager::TaskRun()
{
    int option;

    do
    {
        try
        {
            std::cout << "====== Task Management ======\n";
            std::cout << "1. Add Task\n2. Edit Task\n3. Delete Task\n4. View All Tasks\n5. Search Tasks\n6. Toggle Task Status\n7. Return\n\nChoose an option: ";
            std::cin >> option;

            switch(option)
            {
                case 1:
                    this->AddTask();
                    break;
                case 2:
                    this->EditTask();
                    break;
                case 3:
                    this->DeleteTask();
                    break;
                case 4:
                    this->ViewAllTasks();
                    break;
                case 5:
                    this->SearchTasks();
                    break;
                case 6:
                    this->MarkTaskStatus();
                    break;
                case 7:
                    std::cout << "Returning to main menu...\n\n";
                    break;
                default:
                    std::cout << "Invalid option!\n";
                    break;
            }
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
    } while(option != 7);
}
void TaskManager::ProjectRun()
{
    int option;

    do
    {
        try
        {
            std::cout << "====== Project Management ======\n";
            std::cout << "1. Add Project\n2. Edit Project\n3. Delete Project\n4. View All Projects\n5. Search Projects\n6. Toggle Project Status\n7. Return\n\nChoose an option: ";
            std::cin >> option;

            switch(option)
            {
                case 1:
                    this->AddProject();
                    break;
                case 2:
                    this->EditProject();
                    break;
                case 3:
                    this->DeleteProject();
                    break;
                case 4:
                    this->ViewAllProjects();
                    break;
                case 5:
                    this->SearchProjects();
                    break;
                case 6:
                    this->MarkProjectStatus();
                    break;
                case 7:
                    std::cout << "Returning to main menu...\n\n";
                    break;
                default:
                    std::cout << "Invalid option!\n";
                    break;
            }
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
    } while(option != 7);
}


void TaskManager::AddTask()
{
    int id;
    std::string name = "";
    std::string description = "";

    std::cout << "=== Add Task ===\n";

    try
    {
        bool is_taken;

        do
        {
            std::cin.ignore();
            std::cout << "- Task Id: ";
            std::cin >> id;

            is_taken = false;

            for(Task& task : this->tasks)
            {
                if(task.get_id() == id)
                {
                    is_taken = true;
                }
            }
        } while (is_taken);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cin.ignore();

    do
    {
        std::cout << "- Task Name: ";
        std::getline(std::cin, name);
    } while (name == "");

    do
    {
        std::cout << "- Task Description: ";
        std::getline(std::cin, description);
    } while (description == "");

    Task newTask(id, false, name, description);
    this->tasks.push_back(newTask);
}
void TaskManager::EditTask()
{
    int targetId;
    bool is_valid = false;
    Task* targetTask = nullptr;

    std::cout << "=== Edit Task ===\n";

    try
    {
        do
        {
            std::cin.ignore();
            std::cout << "- Target Id: ";
            std::cin >> targetId;

            for(Task& task : this->tasks)
            {
                if(task.get_id() == targetId)
                {
                    is_valid = true;
                    targetTask = &task;
                }
            }
        } while (!is_valid);
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    if(is_valid)
    {
        std::cin.ignore();
     
        std::string name;
        std::string description;
        do
        {
            std::cout << "- Task New Name (write 'KC' to keep current): ";
            std::getline(std::cin, name);

            if(name == "KC")
            {
                name = targetTask->get_name();
            }
        } while (name == "");

        do
        {
            std::cout << "- Task New Description (write 'KC' to keep current): ";
            std::getline(std::cin, description);

            if(description == "KC")
            {
                description = targetTask->get_description();
            }
        } while (description == "");

        targetTask->set_new(name, description);
    }
}
void TaskManager::DeleteTask()
{
    int targetId;
    bool is_valid = false;
    Task* targetTask = nullptr;

    std::cout << "=== Delete Task ===\n";

    try
    {
        do
        {
            std::cin.ignore();
            std::cout << "- Target Id: ";
            std::cin >> targetId;

            for(Task& task : this->tasks)
            {
                if(task.get_id() == targetId)
                {
                    is_valid = true;
                    targetTask = &task;
                }
            }
        } while (!is_valid);
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for(size_t i = 0; i < this->tasks.size(); i++)
    {
        if(&this->tasks[i] == targetTask)
        {
            this->tasks.erase(this->tasks.begin() + i);
            break;
        }
    }
    
}
void TaskManager::ViewAllTasks()
{
    std::cout << "=== All Tasks ===\n";

    for(Task& task : this->tasks)
    {
        task.print_data();
    }

    std::cout << "-------------------\n";
}
void TaskManager::SearchTasks()
{
    int option;

    std::cout << "=== Search Tasks ===\n";

    do
    {
        try
        {
            std::cout << "1. Search by Id\n2. Search by Name\n\nChoose an option: ";
            std::cin >> option;

            if(option == 1 || option == 2)
            {

            }
            else
            {
                std::cout << "Invalid option!\n";
                option = -1;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    } while (option == -1);
    
    if(option == 1)
    {
        int targetId;

        std::cout << "== Search by Id ==\n";

        std::cin.ignore();
        std::cout << "- Target Id: ";
        std::cin >> targetId;

        for (Task& task : this->tasks)
        {
            if(task.get_id() == targetId)
            {
                task.print_data();
            }
        }
        
    }
    else if(option == 2)
    {
        std::string targetName = "";

        std::cout << "== Search by Name ==\n";

        std::cin.ignore();

        do
        {
            std::cout << "- Target Name: ";
            std::getline(std::cin, targetName);
        } while(targetName == "");

        for (Task& task : this->tasks)
        {
            if(task.get_name() == targetName)
            {
                task.print_data();
            }
        }
    }
}
void TaskManager::MarkTaskStatus()
{
    int targetId;
    bool is_done;
    bool is_valid = false;
    Task* targetTask = nullptr;

    std::cout << "=== Toggle Task Status ===\n";

    try
    {
        do
        {
            std::cin.ignore();
            std::cout << "- Target Id: ";
            std::cin >> targetId;

            for(Task& task : this->tasks)
            {
                if(task.get_id() == targetId)
                {
                    is_valid = true;
                    targetTask = &task;
                }
            }
        } while (!is_valid);
        
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    if(is_valid)
    {
        char option = '\0';

        std::cin.ignore();
        std::cout << "Is the task done or not (Y/N)?: ";
        std::cin >> option;

        if(option == 'Y' || option == 'y')
        {
            is_done = true;
        }
        else
        {
            is_done = false;
        }
    }
    
    targetTask->set_done(is_done);
}


void TaskManager::AddProject()
{
    int id;
    std::string name = "";
    std::string description = "";

    std::cout << "=== Add Project ===\n";

    try
    {
        bool is_taken;

        do
        {
            std::cin.ignore();
            std::cout << "- Project Id: ";
            std::cin >> id;

            is_taken = false;

            for(Project& project : this->projects)
            {
                if(project.get_id() == id)
                {
                    is_taken = true;
                }
            }
        } while (is_taken);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cin.ignore();

    do
    {
        std::cout << "- Project Name: ";
        std::getline(std::cin, name);
    } while (name == "");

    do
    {
        std::cout << "- Project Description: ";
        std::getline(std::cin, description);
    } while (description == "");

    Project newTask(id, false, name, description);
    this->projects.push_back(newTask);
}
void TaskManager::EditProject()
{
    int targetId;
    bool is_valid = false;
    Project* targetProject = nullptr;

    std::cout << "=== Edit Project ===\n";

    try
    {
        do
        {
            std::cin.ignore();
            std::cout << "- Target Id: ";
            std::cin >> targetId;

            for(Project& project : this->projects)
            {
                if(project.get_id() == targetId)
                {
                    is_valid = true;
                    targetProject = &project;
                }
            }
        } while (!is_valid);
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    if(is_valid)
    {
        
        std::cin.ignore();

        std::string name;
        std::string description;
        do
        {
            std::cout << "- Project New Name (write 'CN' to keep current): ";
            std::getline(std::cin, name);

            if(name == "CN")
            {
                name = targetProject->get_name();
            }
        } while (name == "");

        do
        {
            std::cout << "- Project New Description (write 'CN' to keep current): ";
            std::getline(std::cin, description);

            if(description == "CN")
            {
                description = targetProject->get_description();
            }
        } while (description == "");

        targetProject->set_new(name, description);
    }
}
void TaskManager::DeleteProject()
{
    int targetId;
    bool is_valid = false;
    Project* targetProject = nullptr;

    std::cout << "=== Delete Project ===\n";

    try
    {
        do
        {
            std::cin.ignore();
            std::cout << "- Target Id: ";
            std::cin >> targetId;

            for(Project& project : this->projects)
            {
                if(project.get_id() == targetId)
                {
                    is_valid = true;
                    targetProject = &project;
                }
            }
        } while (!is_valid);
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for(size_t i = 0; i < this->projects.size(); i++)
    {
        if(&this->projects[i] == targetProject)
        {
            this->projects.erase(this->projects.begin() + i);
            break;
        }
    }
}
void TaskManager::ViewAllProjects()
{
    std::cout << "=== All Projects ===\n";

    for(Project& project : this->projects)
    {
        project.print_data();
    }

    std::cout << "-------------------\n";
}
void TaskManager::SearchProjects()
{
    int option;

    std::cout << "=== Search Projects ===\n";

    do
    {
        try
        {
            std::cout << "1. Search by Id\n2. Search by Name\n\nChoose an option: ";
            std::cin >> option;

            if(option == 1 || option == 2)
            {

            }
            else
            {
                std::cout << "Invalid option!\n";
                option = -1;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    } while (option == -1);
    
    if(option == 1)
    {
        int targetId;

        std::cout << "== Search by Id ==\n";

        std::cin.ignore();
        std::cout << "- Target Id: ";
        std::cin >> targetId;

        for (Project& project : this->projects)
        {
            if(project.get_id() == targetId)
            {
                project.print_data();
            }
        }
        
    }
    else if(option == 2)
    {
        std::string targetName = "";

        std::cout << "== Search by Name ==\n";

        std::cin.ignore();

        do
        {
            std::cout << "- Target Name: ";
            std::getline(std::cin, targetName);
        } while(targetName == "");

        for (Project& project : this->projects)
        {
            if(project.get_name() == targetName)
            {
                project.print_data();
            }
        }
    }
}
void TaskManager::MarkProjectStatus()
{
    int targetId;
    bool is_done;
    bool is_valid = false;
    Project* targetProject = nullptr;

    std::cout << "=== Toggle Project Status ===\n";

    try
    {
        do
        {
            std::cin.ignore();
            std::cout << "- Target Id: ";
            std::cin >> targetId;

            for(Project& project : this->projects)
            {
                if(project.get_id() == targetId)
                {
                    is_valid = true;
                    targetProject = &project;
                }
            }
        } while (!is_valid);
        
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    if(is_valid)
    {
        char option = '\0';

        std::cin.ignore();
        std::cout << "Is the project done or not (Y/N)?: ";
        std::cin >> option;

        if(option == 'Y' || option == 'y')
        {
            is_done = true;
        }
        else
        {
            is_done = false;
        }
    }
    
    targetProject->set_done(is_done);
}


void TaskManager::SaveToFile()
{
    if(this->is_tasks_file)
    {
        std::ofstream fileOutput;
        fileOutput.open(this->tasks_file_path, std::ios::out | std::ios::trunc);

        if(fileOutput.is_open())
        {
            for(Task task : this->tasks)
            {
                std::string id = std::to_string(task.get_id());
                std::string name = task.get_name();
                std::string description = task.get_description();
                std::string is_done = task.get_is_done() ? "1" : "0";

                fileOutput << id << ',' << is_done << ',' << name << ',' << description << '\n';
            }

            fileOutput.close();
        }
        else
        {
            std::cerr << "Couldn't open tasks file to save!\n";
        }
    }

    if(this->is_projects_file)
    {
        std::ofstream fileOutput;
        fileOutput.open(this->projects_file_path, std::ios::out | std::ios::trunc);

        if(fileOutput.is_open())
        {
            for(Project project : this->projects)
            {
                std::string id = std::to_string(project.get_id());
                std::string name = project.get_name();
                std::string description = project.get_description();
                std::string is_done = project.get_is_done() ? "1" : "0";

                fileOutput << id << ',' << is_done << ',' << name << ',' << description << '\n';
            }

            fileOutput.close();
        }
        else
        {
            std::cerr << "Couldn't open projects file to save!\n";
        }
    }
}
void TaskManager::LoadFromFile()
{
    if(this->is_tasks_file)
    {
        std::vector<std::string> lines;

        std::ifstream fileContent;
        fileContent.open(this->tasks_file_path);

        if(fileContent.is_open())
        {
            std::string curLine;

            while(std::getline(fileContent, curLine))
            {
                lines.push_back(curLine);
            }

            fileContent.close();
        }
        else
        {
            std::cerr << "Couldn't open tasks file to load!\n";
        }

        for(std::string data : lines)
        {
            std::vector<std::string> line_data = this->Split(data, ',');

            int data_id;
            bool data_is_done;
            std::string data_name;
            std::string data_description;

            try
            {
                data_id = std::stoi(line_data[0]);

                if(line_data[1] == "1")
                {
                    data_is_done = true;
                }
                else
                {
                    data_is_done = false;
                }

                data_name = line_data[2];
                data_description = line_data[3];

                Task newTask(data_id, data_is_done, data_name, data_description);
                this->tasks.push_back(newTask);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }

    if(this->is_projects_file)
    {
        std::vector<std::string> lines;

        std::ifstream fileContent;
        fileContent.open(this->projects_file_path);

        if(fileContent.is_open())
        {
            std::string line;

            while(std::getline(fileContent, line))
            {
                lines.push_back(line);
            }

            fileContent.close();
        }
        else
        {
            std::cerr << "Couldn't open projects file to load!\n";
        }

        for(std::string line : lines)
        {
            std::vector<std::string> line_data = this->Split(line, ',');

            int data_id;
            bool data_is_done;
            std::string data_name;
            std::string data_description;

            try
            {
                data_id = std::stoi(line_data[0]);

                if(line_data[1] == "1")
                {
                    data_is_done = true;
                }
                else
                {
                    data_is_done = false;
                }

                data_name = line_data[2];
                data_description = line_data[3];

                Project newProject(data_id, data_is_done, data_name, data_description);
                this->projects.push_back(newProject);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        }
    }
}
