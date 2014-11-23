#pragma once

#include <iostream>


class ProgressLog
{
public:
    ProgressLog(std::string name, int start, int finish, int reportStep)
            : _name(name)
            , _start(start)
            , _finish(finish)
            , _reportStep(reportStep)
            , _current(start)
    {
    }

    void progress()
    {
        if((++_current % _reportStep) == 0)
            std::cout << _name << " : " << 100 * (_current - _start)/((double)(_finish - _start)) << "%" << std::endl;
    }

private:
    std::string _name;
    int _start;
    int _finish;
    int _reportStep;
    int _current;
};