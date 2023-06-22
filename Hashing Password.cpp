#include <stdio.h>
#include <string.h>

unsigned int hash(const char *str) {
    unsigned int hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

int main() {
    char password[100];
    unsigned int hashed_password;

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; 

    hashed_password = hash(password);

    printf("Hashed password: %u\n", hashed_password);

    return 0;
}

// //The function takes a pointer to a string str as its input and returns 
// an unsigned integer hash as its output. Inside the function, the initial 
// value of hash is set to 5381. Then, the function loops through each 
// character of the input string str using a while loop.

//hash = ((hash << 5) + hash) + c;
// multiplying the current value of hash by 33 and adding the ASCII value of 
// the current character c. The << operator is the left shift operator, which 
// shifts the binary representation of hash to the left by 5 bits, effectively
// multiplying hash by 32. The + operator simply adds the two values together.
// After the loop finishes, the function returns the final value of hash.   

// The main() function first declares an array of characters password with a 
// length of 100 and an unsigned integer variable hashed_password. Then, it prompts
// the user to enter a password using printf() and reads the user's input using fgets().
// The sizeof() function is used to ensure that no more than 100 characters are read into
// the password array, preventing buffer overflow. The next line removes the newline 
// character from the end of the input string, if it exists, by replacing it with a null
// character.
// The hashed_password variable is assigned the hash value of the input password by
// calling the hash() function. The resulting hash value is printed to the console using printf().

// input example: hahalolnoob
// expected output: random numbers