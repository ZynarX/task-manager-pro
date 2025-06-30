#include <iostream>
#include "../include/TaskManager.hpp"

int main()
{
    TaskManager task_manager("tasks.txt", "projects.txt");
    task_manager.run();

    return 0;
}
