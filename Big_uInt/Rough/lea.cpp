#include <stdio.h>
#include <stdint.h>
#include <immintrin.h>

int main() {
    uint32_t base = 0x1000;
    uint32_t index = 0x200;
    uint32_t scale = 4;
    uint32_t displacement = 0x30;
    uint32_t result;
    __asm__ (
        "leal 0x30(%[base], %[index], 4), %[result]\n\t"
        // "subl 0x4(%ebx,%ecx,0x4),%eax\n\t"
        : [result] "=r" (result)
        : [base] "r" (base), [index] "r" (index), [scale] "r" (scale), [displacement] "r" (displacement)
    );
    printf("LEA result: 0x%X\n", result);
    return 0;
}