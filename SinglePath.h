#ifndef SINGLEPATH_H
#define SINGLEPATH_H

#include <list>
#include "PawnPos.h"

class SinglePath
{
    public:
        SinglePath();
        void AddStep(const PawnPos step);

    private:
        std::list<PawnPos> path;
        bool killed;
};

#endif // SINGLEPATH_H
