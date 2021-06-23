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
Unfortunately, this is something that I'm still researching and doesn't seem to be solved as of yet.  
I acknowledge that I'm coming from a position that, in all likelihood, isn't qualified to speak on these matters, but the confusion sowed by this issue makes it difficult for people who are trying to learn best practices to understand what standards to follow.  
As such, this section is not designed to propose any solution, nor is it claiming any understanding of matters related to the complex nature of C portability. Instead, this section was written in hopes that a solution to this issue would be eventually be reached with all due speed.
#### Background (As the Author Understands the Issue)
The background of the issue seems to be this: The low-level functions for C strings doesn't support bound checking which leads to the possibility for code to be exploited or broken through buffer overflows.  
The primary source of claims are from the Wikipedia article here: https://en.wikipedia.org/wiki/C_string_handling#Replacements, but specific information will be directly referenced.  
As far as I can understand, it seems very similar to the concerns raised in section "scanf Concerns" above.  
One of the proposed solutions, as shown in https://www.sudo.ws/todd/papers/strlcpy.html for OpenBSD, is to replace strcpy and strcat with strlcpy and strlcat.  
Another solution is is the usage of memcpy (https://en.cppreference.com/w/c/string/byte/memcpy) and memmove (https://en.cppreference.com/w/c/string/byte/memmove).  
Lastly, one other solution proposed is the use of \_s suffixed functions. This is the solution proposed by Microsoft.  
One troubling issue with this last solution is that it is treated as the de facto solution for this issue in Visual Studio.  
I'm currently using Visual Studio because it is the tool most readily available and because good solutions for linking in Visual Code seems to be unavailable at the time of writing.  
#### Solutions (For This Code)
The solution planned to be used for this code is to define compiler-specific code based on the defined flags and platforms of the compiler.  
This soultion isn't perfect: It enhances portability by sacrificing readability and consistency. 
However, the competeing standards and their viewed importance for implementation/deprecation is something that is argued between different compiler vendors.
This ugly, yet functional solution is necessary for an issue that hasn't been resolved yet.
#### Post-Script
It's difficult to determine what are good practices when dealing with conflicting standards.  
Standards should provide a baseline for which good code and good coding practices can be built upon.  
However, when there's arguments about what the standards should be, the people who are hurt most are the aspiring programmers who are trying to learn.  
I'm open to suggestions and improvements on the solution. But, the code should be as portable as possible within reasonable requirements.  
What is "reasonable"? For this code, the current minimum requirement that supports C99. If we accept that printf\_s is a valid solution, then the minimum requirement can be increased to C11 (and, optionally, \_\_STDC\_LIB\_EXT1\_\_ is defined within the compiler).
I know that this definition is very fast and loose, but, for casual programming, better definitions aren't needed and ANSI C may be too restrictive especially as the requirements for ANSI C conflicts with the CS50 style guide mentioned above.
