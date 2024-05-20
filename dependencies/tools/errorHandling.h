#include <signal.h>
#include <iostream>
#include "../glad/glad.h"

// Error handling
#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define LOGCHECK(x) do { clearError(); x; ASSERT(noLogCall(#x, __FILE__, __LINE__)); } while (0)


void clearError();
bool noLogCall(const char *function, const char *file, int line );