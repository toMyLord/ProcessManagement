#include "findway.h"

findByPid::findByPid(char * pid)
{
    int lenth = strlen(pid);
    int number = 0;
    for(int i = 0; i < lenth; i++)
    {
        number = number * 10 + pid[i] - '0'; 
    }
    this->pid = number;
}


bool findByPid::operator()(vector<proc_node>::value_type &value)
{
    return value.pid == this->pid;
}  