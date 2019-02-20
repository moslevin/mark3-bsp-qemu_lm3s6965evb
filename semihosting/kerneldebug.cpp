#include "semihosting.h"

using namespace Mark3;

extern "C" {
void DebugPrint(const char* szString_)
{
    auto* pcChar = szString_;
    while (*pcChar != '\0') {
        SemiHosting::Write(1, pcChar, 1);
        pcChar++;
    }
}
}
