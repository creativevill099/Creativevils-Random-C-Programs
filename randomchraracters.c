/*
 * randomchraracters.c
 *
 * Generates random letters, numbers, and symbols forever in the CMD box.
 * Target: Windows (console). Written in C.
 *
 * Compile (MinGW/gcc):   gcc randomchraracters.c -o randomchraracters.exe
 * Compile (MSVC):        cl randomchraracters.c
 * Run:                   randomchraracters.exe
 * Stop:                  Ctrl+C or close the console window
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

/* The pool of characters we pick from: letters, digits, and symbols */
static const char POOL[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789"
    "!@#$%^&*()-_=+[]{}|;:,.<>?/~`";

int main(void)
{
#ifdef _WIN32
    /* Make console output handle symbols nicely (UTF-8 code page) */
    SetConsoleOutputCP(CP_UTF8);

    /* Optional: enable virtual terminal processing so ANSI colors work on Win10+ */
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(hOut, &mode))
        SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif

    /* Seed the random number generator with current time */
    srand((unsigned)time(NULL));

    const int POOL_SIZE = (int)(sizeof(POOL) - 1); /* exclude trailing '\0' */
    const int CHARS_PER_LINE = 64;                 /* how many chars per line */

    printf("Generating random characters... Press Ctrl+C to stop.\n\n");

    while (1) /* loop forever */
    {
        /* Print one line of random characters */
        for (int i = 0; i < CHARS_PER_LINE; i++)
        {
            int idx = rand() % POOL_SIZE;
            putchar(POOL[idx]);
        }
        putchar('\n');

        /* Flush so it appears immediately in the CMD box */
        fflush(stdout);

        /* Small delay so the screen isn't an unreadable blur (optional).
         * Remove this block if you want maximum speed. */
#ifdef _WIN32
        Sleep(10); /* milliseconds */
#else
        /* Fallback for non-Windows testing: busy-wait ~10ms */
        clock_t start = clock();
        while ((clock() - start) < CLOCKS_PER_SEC / 100) { /* spin */ }
#endif
    }

    return 0; /* never reached */
}
