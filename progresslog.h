#pragma once

#include <iostream>


class ProgressLog
{
public:
    ProgressLog(std::string name, int start, int finish, int reportStep)
            : _name(name)
            , _start(start)
            , _finish(finish)
            , _reportStep(std::max(1, reportStep))
            , _current(start)
    {
    }

    void progress()
    {

        if((++_current % _reportStep) == 0)
        {
            double num = _current - _start;
            double den = _finish - _start;
            if(den == 0)
                den = 1;
            std::cout << _name << " : " << 100 * num / den << "%" << std::endl;

        }
    }

private:
    std::string _name;
    int _start;
    int _finish;
    int _reportStep;
    int _current;
};
