#ifndef TUI_H
#define TUI_H

#define CURSOR_UP "\x1b[A\r"
#define CLR_LINE "\33[2K\r"
#define CLR_SCREEN "\033c"

/**
 * @brief Runs the program's main menu.
 *
 * Prompts player to choose from the main menu
 * and takes corresponding action.
 *
 * @return Whether player wants to keep playing
 */
bool mainMenu();

/**
 * @brief Convenient alternative for scanf("%d"),
 *
 * Clears the input stream,
 * display an error message if input is invalid,
 * and returns success status
 *
 * @return whether input is valid
 */
bool scand(int *num);

/**
 * @brief scand, but the number must be positive.
 */
bool scandPositive(int *num);

/**
 * @brief Convenient wrapper for fgets with error handling
 *
 * Clear the input stream if there is a buffer overflow,
 * and returns the success status.
 *
 * @return Whether there is a buffer overflow
 */
bool scans(char *str);

/**
 * @brief scans, but the input must be non-empty.
 *
 * @return whether input is non-empty
 */
bool scansNonEmpty(char *str);

/**
 * Convenient wrapper for printf.
 *
 * Clears the current line and prints.
 */
void print(const char *format, ...);

/**
 * Convenient wrapper for printf.
 *
 * Clears the current line and prints with an ending <pre>\n</pre>.
 */
void println(const char *format, ...);

void invalidInput(char message[]);

void clrscr();

#endif // TUI_H