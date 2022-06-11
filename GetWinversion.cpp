#include<Windows.h>
#include<stdio.h>

int main()
{
    uintptr_t PEB;
    int OsBuildNumber;
#ifdef _WIN64
    PEB = __readgsqword(0x60);
    OsBuildNumber = *((INT*)(PEB + 0x120));
#else
    PEB = __readfsdword(0x30);
    OsBuildNumber = *((INT*)(PEB + 0xAC));
#endif // _WIN64
    switch (OsBuildNumber)
    {
    case 17134:
        printf("Win10 1803\n");
        break;
    case 17763:
        printf("Win10 1809\n");
        break;
    case 18362:
        printf("Win10 1903\n");
        break;
    case 15063:
        printf("Win10 1703\n");
        break;
    case 16299:
        printf("Win10 1709\n");
        break;
        // ........Other Windows OS Version
    case 19042:
        printf("Win10 19042\n");
    default:
        break;
    }
    printf("OsBuildNumber: %d", OsBuildNumber);
    getchar();
}