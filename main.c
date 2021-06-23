// Ask the user for their name, age, and username and output this data.

// Add this to enable *_s suffixes for C11 compilers that support _s functions.
#if defined(__STDC_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ < 1
#define __STDC_WANT_LIB_EXT1__ 1
#endif

#include <stdio.h>
#include "validinput.h"

// Error code:
// X X X X X X X X
//       |-|-|-|-|- File I/O Error
//         |-|-|-|- No Input
//           |-|-|- Large name input
//             |-|- Large age input
//               |- Large username input
#define ERR_IO_ERROR   0x10
#define ERR_NO_INPUT   0x08
#define ERR_LARGE_NAME 0x04
#define ERR_LARGE_AGE  0x02
#define ERR_LARGE_USER 0x01
#define STD_OP         0x00

int main(void)
{
    // Contain the user prompts in const char strings.
    const char FIRST_PROMPT[25] = "Please enter your name: ";
    const char SECOND_PROMPT[24] = "Please enter your age: ";
    const char THIRD_PROMPT[29] = "Please enter your username: ";
    // Contain the constant strings that will be used in the output.
    const char FIRST_OUTPUT[14] = "Your name is";
    const char SECOND_OUTPUT[11] = ", you are";
    const char THIRD_OUTPUT[34] = " years old, and your username is";
    // Contain the messages used to indicate issues with user input.
    const char ERROR[7] = "ERROR:";
    const char NO_USER_INPUT[26] = "No user input found for:";
    const char WARNING[10] = "WARNING:";
    const char WARN_LONG_STR[46] = "entered was too long. The output was cut off.";

    // Variables to hold user input.
    char input_name[11];
    char input_age[4];
    char input_username[51];

    // File IO
    FILE *log_file;
    int file_close_code = 0;
#if defined(WIN32) || defined(__STDC_WANT_LIB_EXT1__)
    file_close_code = fopen_s(&log_file, "run.log", "w");
#else
    log_file = fopen("run.log", "w");
#endif

    // This weird hacky logic is needed to prevent Visual Studio from
    // complaining about printf_s. Please fix, Microsoft.
    if (log_file == NULL)
    {
        return ERR_IO_ERROR;
    }
    else if (file_close_code != 0)
    {
        fclose(log_file);
        return ERR_IO_ERROR;
    }

    // Prompt the user, passthrough the input variables to hold responses,
    // and take note of any issues with the user input.
    unsigned char name_result = get_user_input_cc(FIRST_PROMPT, input_name,
        sizeof(input_name));
    unsigned char age_result = get_user_input_cc(SECOND_PROMPT, input_age,
        sizeof(input_age));
    unsigned char username_result = get_user_input_cc(THIRD_PROMPT,
        input_username, sizeof(input_username));
    
    if (name_result == NO_INPUT || age_result == NO_INPUT || username_result == NO_INPUT)
    {
        // Error messages.
        if (name_result == NO_INPUT)
        {
#if defined(WIN32) || defined(__STDC_WANT_LIB_EXT1__)
            printf_s("%s %s name.\n\r", ERROR, NO_USER_INPUT);
            fprintf_s(log_file, "%s %s name.\n\r", ERROR, NO_USER_INPUT);
#else
            printf("%s %s name.\n\r", ERROR, NO_USER_INPUT);
            fprintf(log_file, "%s %s name.\n\r", ERROR, NO_USER_INPUT)
#endif
        }
        if (age_result == NO_INPUT)
        {
#if defined(WIN32) || defined(__STDC_WANT_LIB_EXT1__)
            printf_s("%s %s age.\n\r", ERROR, NO_USER_INPUT);
            fprintf_s(log_file, "%s %s age.\n\r", ERROR, NO_USER_INPUT);
#else
            printf("%s %s age.\n\r", ERROR, NO_USER_INPUT);
            fprintf(log_file, "%s %s age.\n\r", ERROR, NO_USER_INPUT);
#endif
        }
        if (username_result == NO_INPUT)
        {
#if defined(WIN32) || defined(__STDC_WANT_LIB_EXT1__)
            printf_s("%s %s username.\n\r", ERROR, NO_USER_INPUT);
            fprintf_s(log_file, "%s %s username.\n\r", ERROR, NO_USER_INPUT);
#else
            printf("%s %s username.\n\r", ERROR, NO_USER_INPUT);
            fprintf(log_file, "%s %s username.\n\r", ERROR, NO_USER_INPUT);
#endif
        }
        
        // Return a no input error exit code.
        fclose(log_file);
        return ERR_NO_INPUT;
    }

    // Output.
#if defined(WIN32) || defined(__STDC_WANT_LIB_EXT1__)
    printf_s("%s %s%s %s%s %s.\n\r", FIRST_OUTPUT, input_name, SECOND_OUTPUT,
        input_age, THIRD_OUTPUT, input_username);
    fprintf_s(log_file, "%s %s%s %s%s %s.\n\r", FIRST_OUTPUT, input_name, SECOND_OUTPUT,
        input_age, THIRD_OUTPUT, input_username);
#else
    printf("%s %s%s %s%s %s.\n\r", FIRST_OUTPUT, input_name, SECOND_OUTPUT,
        input_age, THIRD_OUTPUT, input_username);
    fprintf(log_file, "%s %s%s %s%s %s.\n\r", FIRST_OUTPUT, input_name, SECOND_OUTPUT,
        input_age, THIRD_OUTPUT, input_username);
#endif
    
    // Additional output for warnings.
    if (name_result == INPUT_TOO_LONG || age_result == INPUT_TOO_LONG || username_result == INPUT_TOO_LONG)
    {
        unsigned char exit_code = 0;
        // Warning messages.
        if (name_result == INPUT_TOO_LONG)
        {
#if defined(WIN32) || defined(__STDC_WANT_LIB_EXT1__)
            printf_s("%s Name %s\n\r", WARNING, WARN_LONG_STR);
            fprintf_s(log_file, "%s Name %s\n\r", WARNING, WARN_LONG_STR);
#else
            printf("%s Name %s\n\r", WARNING, WARN_LONG_STR);
            fprintf(log_file, "%s Name %s\n\r", WARNING, WARN_LONG_STR);
#endif
            exit_code |= ERR_LARGE_NAME;
        }
        if (age_result == INPUT_TOO_LONG)
        {
#if defined(WIN32) || defined(__STDC_WANT_LIB_EXT1__)
            printf_s("%s Age %s\n\r", WARNING, WARN_LONG_STR);
            fprintf_s(log_file, "%s Age %s\n\r", WARNING, WARN_LONG_STR);
#else
            printf("%s Age %s\n\r", WARNING, WARN_LONG_STR);
            fprintf(log_file, "%s Age %s\n\r", WARNING, WARN_LONG_STR);
#endif
            exit_code |= ERR_LARGE_AGE;
        }
        if (username_result == INPUT_TOO_LONG)
        {
#if defined(WIN32) || defined(__STDC_WANT_LIB_EXT1__)
            printf_s("%s Username %s\n\r", WARNING, WARN_LONG_STR);
            fprintf_s(log_file, "%s Username %s\n\r", WARNING, WARN_LONG_STR);
#else
            printf("%s Username %s\n\r", WARNING, WARN_LONG_STR);
            fprintf(log_file, "%s Username %s\n\r", WARNING, WARN_LONG_STR);
#endif
            exit_code |= ERR_LARGE_USER;
        }

        fclose(log_file);
        // Return an appropriate error code.
        return exit_code;
    }

    // Close file to finalize changes.
    if (fclose(log_file) != 0)
    {
        return ERR_IO_ERROR;
    }

    // Everything ran successfully.
    return STD_OP;
}
