#include "random.h"

#include <random>

int util::random::ascii()
{
        return ' ' + rand() % (' ' - '~' + 1);
}

