/* This file implements a line reading function designed to get around the   *
 * limitations and pitfalls of using scanf in most common C implementations. */

 // Add this to enable *_s suffixes for C11 compilers that support _s functions.
#if defined(__STDC_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ < 1
#define __STDC_WANT_LIB_EXT1__ 1
#endif

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
// Link the appropriate header.
#include "validinput.h"

// Exit Codes
const char OK = 0;
const char SMALL_BUFFER = 1;
const char NO_INPUT = 2;
const char INPUT_TOO_LONG = 3;

// Obtain the entire line of user input.
unsigned char get_user_input_c(char *user_prompt, char *input_buffer,
  size_t buffer_size)
{   
    // Trivial case: We need to store at least one null terminator, so we need
    // a buffer of sufficient size for this to use useful at all.
    if (buffer_size < 2)
        return SMALL_BUFFER;

    // Display the user prompt.
    if (user_prompt != NULL)
    {
#if defined(WIN32) || defined(__STDC_WANT_LIB_EXT1__)
        printf_s("%s", user_prompt);
#else
        printf("%s", user_prompt);
#endif
        fflush(stdout);
    }

    // fgets should read everything and either return a pointer to the same
    // output string, or give us a null if no input is given.
    if (fgets(input_buffer, buffer_size, stdin) == NULL)
        return NO_INPUT;
    
    // The stream might return a null character, so we should also catch this
    // as well.
    size_t input_buffer_size = strlen(input_buffer);
    if (input_buffer_size < 1)
        return NO_INPUT;
    
    // If the line is too long to process, the resulting string should not have
    // a newline char.
    if (input_buffer[input_buffer_size - 1] != '\n')
    {
        // If the input is too large, this flag will trip.
        bool long_flag = false;

        // Handle stream errors (EOF)
        char check_char;

        while (((check_char = getchar()) != '\n') && (check_char != EOF))
            long_flag = true;
        
        return (long_flag == true) ? INPUT_TOO_LONG : OK;
    }

    // Replace the newline with a null-termination.
    input_buffer[input_buffer_size - 1] = '\0';
    return OK;
}

unsigned char get_user_input_cc(const char *USER_PROMPT, char *input_buffer,
                          size_t buffer_size)
{
    // Trivial case: We need to store at least one null terminator, so we need
    // a buffer of sufficient size for this to use useful at all.
    if (buffer_size < 2)
        return SMALL_BUFFER;

    // Display the user prompt.
    if (USER_PROMPT != NULL)
    {
#if defined(WIN32) || defined(__STDC_WANT_LIB_EXT1__)
        printf_s("%s", USER_PROMPT);
#else
        printf("%s", USER_PROMPT);
#endif
        fflush(stdout);
    }

    // fgets should read everything and either return a pointer to the same
    // output string, or give us a null if no input is given.
    if (fgets(input_buffer, buffer_size, stdin) == NULL)
        return NO_INPUT;
    
    // The stream might return a null character, so we should also catch this
    // as well.
    size_t input_buffer_size = strlen(input_buffer);
    if (input_buffer_size < 1)
        return NO_INPUT;
    
    // If the line is too long to process, the resulting string should not have
    // a newline char.
    if (input_buffer[input_buffer_size - 1] != '\n')
    {
        // If the input is too large, this flag will trip.
        bool long_flag = false;

        // Handle stream errors (EOF)
        char check_char;

        while (((check_char = getchar()) != '\n') && (check_char != EOF))
            long_flag = true;
        
        return (long_flag == true) ? INPUT_TOO_LONG : OK;
    }

    // Replace the newline with a null-termination.
    input_buffer[input_buffer_size - 1] = '\0';
    return OK;
}