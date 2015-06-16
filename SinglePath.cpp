#include "SinglePath.h"

SinglePath::SinglePath()
{    
    path.clear();
    killed = false;
}

void SinglePath::AddStep(const PawnPos step)
{
    path.push_back(step);
}
