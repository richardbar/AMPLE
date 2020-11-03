#include <stdbool.h>
#include <stdint.h>

#include "AMPLE.h"
#include "OPCODE HANDLERS/V1.h"

#if defined(__WINDOWS__)
    #include <Windows.h>
#elif (defined(__LINUX__) || defined(__APPLE__))
    #include <unistd.h>
#else
    #include <time.h>
#endif

/** Waits for one AMPLE cycle
 * @param Arg1 First OP Code Argument
 * @param Arg2 Second OP Code Argument
 * @param position Int pointer of position of program
 * @return Returns true if success and false if not.
 */
bool HALT_MIN(FUNCTION_ARGUMENTS)
{
    return true;
}

/** Waits for Args1 ms
 * @param Arg1 First OP Code Argument
 * @param Arg2 Second OP Code Argument
 * @param position Int pointer of position of program
 * @return Returns true if success and false if not.
 */
bool HALT_MS(FUNCTION_ARGUMENTS)
{
#if defined(__WINDOWS__)
    Sleep(Arg1);
#elif (defined(__LINUX__) || defined(__APPLE__))
    usleep(Arg1 * 1000);
#else
    clock_t EndTime = clock() + Arg1;
    while (clock() < EndTime) ;
#endif
    return true;
}

bool HALT_REGISTER(FUNCTION_ARGUMENTS)
{
    uint64_t* pos = GetElementFromList(Registers, Arg1);
    if (!pos)
        return false;
    Arg1 = *pos;
    return HALT_MS(PASS_ARGUMENTS);
}

bool HALT_MEMORY(FUNCTION_ARGUMENTS)
{
    uint64_t* pos = GetElementFromList(Memory, Arg1);
    if (!pos)
        return false;
    Arg1 = *pos;
    return HALT_MS(PASS_ARGUMENTS);
}

bool (*HALT_MODES[])(ARGUMENT_TYPES) = {
        HALT_MIN,
        HALT_MS,
        HALT_REGISTER,
        HALT_MEMORY
};

bool HALT_V1(MODE_FUNCTION_ARGUMENTS)
{
    return HALT_MODES[Mode](PASS_ARGUMENTS);
}