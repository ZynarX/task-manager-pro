#include <iostream>
#include <string>
#pragma once

class Task
{
private:
    int id;
    bool is_done;
    std::string name;
    std::string description;
public:
    Task(int Id, bool Is_done, std::string Name, std::string Description);

    int get_id();
    bool get_is_done();
    std::string get_name();
    std::string get_description();

    void set_new(std::string Name, std::string Description);
    void set_done(bool Is_done);

    void print_data();
};
