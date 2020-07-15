#include "opcodes/Mov.h"

#define FUNCTION_ARGUMENTS uint64_t arg1, uint64_t arg2, uint64_t arg3, Memory* memory, Memory* registers, uint32_t* programCounter

_Bool MovValueToRegister(FUNCTION_ARGUMENTS) {
    void* pos = GetMemoryPos(registers, arg1);
    if (!pos) return false;
    *(int64_t*)pos = (int64_t)arg2;
    return true;
}

_Bool MovRegisterToRegister(FUNCTION_ARGUMENTS) {
    void* pos1 = GetMemoryPos(registers, arg1);
    void* pos2 = GetMemoryPos(registers, arg2);
    if (!pos1 || !pos2) return false;
    *(int64_t*)pos1 = *(int64_t*)pos2;
    return true;
}

_Bool MovMemoryToRegister(FUNCTION_ARGUMENTS) {
    void* pos1 = GetMemoryPos(registers, arg1);
    void* pos2 = GetMemoryPos(memory, 2);
    if (!pos1 || !pos2) return false;
    *(int64_t*)pos1 = *(int64_t*)pos2;
    return true;
}

_Bool MovRegisterValuePointerToRegister(FUNCTION_ARGUMENTS) {
    void* pos1 = GetMemoryPos(registers, arg1);
    void* pos2 = GetMemoryPos(registers, *(uint64_t*)GetMemoryPos(registers, arg2));
    if (!pos1 || !pos2) return false;
    *(int64_t*)pos1 = *(int64_t*)pos2;
}

_Bool MovRegisterRegisterPointerToRegister(FUNCTION_ARGUMENTS) {

}

_Bool MovRegisterMemoryPointerToRegister(FUNCTION_ARGUMENTS) {

}

_Bool MovMemoryValuePointerToRegister(FUNCTION_ARGUMENTS) {

}

_Bool MovMemoryRegisterPointerToRegister(FUNCTION_ARGUMENTS) {

}

_Bool MovMemoryMemoryPointerToRegister(FUNCTION_ARGUMENTS) {

}

_Bool MovValueToMemory(FUNCTION_ARGUMENTS) {

}

_Bool MovRegisterToMemory(FUNCTION_ARGUMENTS) {

}

_Bool MovMemoryToMemory(FUNCTION_ARGUMENTS) {

}

_Bool MovRegisterValuePointerToMemory(FUNCTION_ARGUMENTS) {

}

_Bool MovRegisterRegisterPointerToMemory(FUNCTION_ARGUMENTS) {

}

_Bool MovRegisterMemoryPointerToMemory(FUNCTION_ARGUMENTS) {

}

_Bool MovMemoryValuePointerToMemory(FUNCTION_ARGUMENTS) {

}

_Bool MovMemoryRegisterPointerToMemory(FUNCTION_ARGUMENTS) {

}

_Bool MovMemoryMemoryPointerToMemory(FUNCTION_ARGUMENTS) {

}

_Bool (*FunctionMovArray[])(FUNCTION_ARGUMENTS) = {
        MovValueToRegister,
        MovRegisterToRegister,
        MovMemoryToRegister,
        MovRegisterValuePointerToRegister,
        MovRegisterRegisterPointerToRegister,
        MovRegisterMemoryPointerToRegister,
        MovMemoryValuePointerToRegister,
        MovMemoryRegisterPointerToRegister,
        MovMemoryMemoryPointerToRegister,
        MovValueToMemory,
        MovRegisterToMemory,
        MovMemoryToMemory,
        MovRegisterValuePointerToMemory,
        MovRegisterRegisterPointerToMemory,
        MovRegisterMemoryPointerToMemory,
        MovMemoryValuePointerToMemory,
        MovMemoryRegisterPointerToMemory,
        MovMemoryMemoryPointerToMemory
};

inline _Bool MovOP(uint32_t mode, FUNCTION_ARGUMENTS) {
    return FunctionMovArray[mode](arg1, arg2, arg3, memory, registers, programCounter);
}