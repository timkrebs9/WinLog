#include <cstddef>
#include <ucontext.h>

int main()
{
    ucontext_t context;
    getcontext(&context);

    return 0;
}
