// Golden build of the OLD converters only: every malloc they make is zeroed,
// so bytes they leave unset come out as 0 (as the new converters write them).
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include <limits>
#include <stdexcept>
#include <array>
#define malloc(n) calloc(1, (n))
