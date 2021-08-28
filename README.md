# DailyProgrammerEasy1
Repository for DailyProgrammer Challenge 1 (Easy). The link to the challenge is here: https://www.reddit.com/r/dailyprogrammer/comments/pih8x/easy_challenge_1/.
## Style
The C code included in this repository should strive to adopt CS50 style guide without CS50 libraries. See https://cs50.readthedocs.io/style/c/.
## Requirements
* A C Compiler that supports at least C99.
## Lessions Learned

### scanf Concerns
At the beginning of the project, the initial concern was about handling user input in C:  
I suspected that the typical scanf solution had some major concerns regarding its use to handle arbitrary user input.
* It seems like there really isn't any checks on whether the input is valid or not.
* What is the buffer size of scanf? And what happens when we exceed the buffer size?
* What happens if the size of the user input exceed the size of the destination array? Do we just start writing to memory in the stack?  
A lot of these concerns aren't usually present in other programming languages because they either handle it in the backend (so that the developer doesn't have to worry about things like memory allocation) or will spit out an error (because the language has strict restrictions on behavior like this... or contain data structures that have such strict restrictions).  
As far as I'm aware, C doesn't always have convenient ways to handle things like this and will, on occasion, just let you write to memory that shouldn't be written or read from.  
Are these concerns necessary for a project like this? Most likely not. But, it does seem like a good idea to be in the habit of sanitizing input to prevent unintended consequences.  
Also, it does give me some reason to experiment in the topic of the C Linker and linking header files.  
The solution implemented is from this Stack Overflow discussion: https://stackoverflow.com/questions/2430303/disadvantages-of-scanf
### Booleans
While the C language doesn't offer a boolean primitive, the common solution is to use an integer with the smallest size.  
However, there does exist a standard boolean library: stdbool.h  
Hopefully, this will allow the code to be more portable between devices (as long as the compiler is compliant to C99 or newer).  
Also, having a bool type might make the code easier to read.
### File IO Portability
Please see https://hydroargentum.blogspot.com/2021/08/a-beginner-c-programmers-perspective-on.html
