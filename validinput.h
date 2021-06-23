/* This header prototypes a line reading function designed to get around the *
 * limitations and pitfalls of using scanf in most common C implementations. */

// Header guard.
#ifndef VALIDINPUT_H
#define VALIDINPUT_H
// Included stdio here due to size_t parameter in prototype.
#include <stdio.h>

// Exit codes.
extern const char OK;
extern const char SMALL_BUFFER;
extern const char NO_INPUT;
extern const char INPUT_TOO_LONG;

// Function prototype.
unsigned char get_user_input_c(char *user_prompt, char *input_buffer,
  size_t buffer_size);
unsigned char get_user_input_cc(const char *USER_PROMPT, char *input_buffer,
  size_t buffer_size);

// End header guard.
#endif