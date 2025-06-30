#include <iostream>
#include "../include/Project.hpp"

Project::Project(int Id, bool Is_done, std::string Name, std::string Description)
{
    this->id = Id;
    this->is_done = Is_done;
    this->name = name;
    this->description = Description;
}

int Project::get_id()
{
    return this->id;
}
bool Project::get_is_done()
{
    return this->is_done;
}
std::string Project::get_name()
{
    return this->name;
}
std::string Project::get_description()
{
    return this->description;
}

void Project::set_new(std::string Name, std::string Description)
{
    this->name = Name;
    this->description = Description;
}
void Project::set_done(bool Is_done)
{
    this->is_done = Is_done;
}

void Project::print_data()
{
    std::cout << "Project Id: " << this->id << '\n';
    std::cout << "Project Name: " << this->name << '\n';
    std::cout << "Poject Description: " << this->description << '\n';
    std::cout << "Is Done? " << this->is_done << '\n';
    std::cout << "--------\n";
}
