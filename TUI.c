#include "TUI.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "main.h"


bool scans(char *str)
{
        fgets(str, CHAR_BUFFER, stdin);

        // Find the pointer to the newline character
        char *EOL = strchr(str, '\n');
        if (EOL) {
                *EOL = '\0'; // Replace '\n' with '\0'
                return true;
        }

        // If not found, it means user entered more characters than allowed
        // Clear the input stream
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
                ;
        // Print error message
        char errorMessage[CHAR_BUFFER];
        sprintf(errorMessage, "Maximum %d characters allowed.", CHAR_BUFFER);
        invalidInput(errorMessage);
        return false;
}

bool scansNonEmpty(char *str)
{
        if (!scans(str))
                return false;
        if (strlen(str) > 0)
                return true;
        printf(CURSOR_UP);
        return false;
}

bool scand(int *num)
{
        // Use scans and convert it to int instead of scanf("%d),
        // because the former can handle empty input.

        char input[CHAR_BUFFER];
        if (!scansNonEmpty(input))
                return false;

        char *endptr;
        *num = strtol(input, &endptr, 10);
        if (*endptr == '\0')
                return true;
        invalidInput("Input must be a number.");
        return false;
}

bool scandPositive(int *num)
{
        if (!scand(num))
                return false;
        if (*num >= 0)
                return true;
        invalidInput("Number must be non-negative.");
        return false;
}

void print(const char *format, ...)
{
        va_list args;
        va_start(args, format);
        printf(CLR_LINE);
        vprintf(format, args);
        va_end(args);
}

void println(const char *format, ...)
{
        va_list args;
        va_start(args, format);
        printf(CLR_LINE);
        char fmtWithNewLine[CHAR_BUFFER + 1];
        sprintf(fmtWithNewLine, "%s\n", format);
        vprintf(fmtWithNewLine, args);
        va_end(args);
}

void invalidInput(char message[])
{
        if (message == NULL)
                message = "Invalid input.";
        printf(CLR_LINE);
        printf("%s", message);
        printf(CURSOR_UP);
        printf(CLR_LINE);
}

void clrscr()
{
        printf(CLR_SCREEN);
        fflush(stdout);
}