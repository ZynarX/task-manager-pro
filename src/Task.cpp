#include <iostream>
#include "../include/Task.hpp"

Task::Task(int Id, bool Is_done, std::string Name, std::string Description)
{
    this->id = Id;
    this->is_done = Is_done;
    this->name = name;
    this->description = Description;
}

int Task::get_id()
{
    return this->id;
}
bool Task::get_is_done()
{
    return this->is_done;
}
std::string Task::get_name()
{
    return this->name;
}
std::string Task::get_description()
{
    return this->description;
}

void Task::set_new(std::string Name, std::string Description)
{
    this->name = Name;
    this->description = Description;
}
void Task::set_done(bool Is_done)
{
    this->is_done = Is_done;
}

void Task::print_data()
{
    std::cout << "Task Id: " << this->id << '\n';
    std::cout << "Task Name: " << this->name << '\n';
    std::cout << "Task Description: " << this->description << '\n';
    std::cout << "Is Done? " << this->is_done << '\n';
    std::cout << "--------\n";
}
