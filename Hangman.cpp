// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>
// #include <time.h>

// #define WORDLIST_SIZE 10 // number of words in word list
// #define MAX_WORD_LENGTH 20 // max length of a word
// #define HASH_SIZE 26 // size of hash table

// char wordlist[WORDLIST_SIZE][MAX_WORD_LENGTH] = {"computer", "programming", "algorithm", "language", "database", "software", "developer", "application", "internet", "network"}; // word list
// int wordlen; // length of current word
// char word[MAX_WORD_LENGTH]; // current word
// int tries; // number of guesses left
// int correct; // number of correct guesses
// int hash_table[HASH_SIZE]; // hash table for tracking guessed letters

// void init_hash_table() {
//     for (int i = 0; i < HASH_SIZE; i++) {
//         hash_table[i] = 0;
//     }
// }

// int hash(char c) {
//     return tolower(c) - 'a';
// }

// void update_hash_table(char c) {
//     hash_table[hash(c)] = 1;
// }

// int is_guess_correct(char c) {
//     return (strchr(word, tolower(c)) != NULL);
// }

// int is_game_over() {
//     return (tries <= 0 || correct == wordlen);
// }

// void display_word() {
//     for (int i = 0; i < wordlen; i++) {
//         if (hash_table[hash(word[i])]) {
//             printf("%c ", word[i]);
//         } else {
//             printf("_ ");
//         }
//     }
//     printf("\n");
// }

// void display_hash_table() {
//     for (int i = 0; i < HASH_SIZE; i++) {
//         printf("%c ", i + 'a');
//     }
//     printf("\n");
// }

// int main() {
//     srand(time(NULL));
//     int index = rand() % WORDLIST_SIZE; // choose a random word from the word list
//     strcpy(word, wordlist[index]); // copy the chosen word into the current word variable
//     wordlen = strlen(word); // get the length of the chosen word
//     init_hash_table(); // initialize the hash table to 0
//     tries = 6; // set the number of guesses allowed
//     correct = 0; // initialize the number of correct guesses to 0
//     printf("Welcome to Hangman!\n");
//     printf("The word has %d letters.\n", wordlen);
//     while (!is_game_over()) {
//         printf("You have %d guesses left.\n", tries);
//         printf("Guessed letters: ");
//         display_hash_table();
//         display_word();
//         char guess;
//         printf("Enter a letter: ");
//         scanf(" %c", &guess);
//         if (is_guess_correct(guess)) {
//             printf("Correct!\n");
//             update_hash_table(guess);
//             correct++;
//         } else {
//             printf("Incorrect.\n");
//             update_hash_table(guess);
//             tries--;
//         }
//     }
//     if (correct == wordlen) {
//         printf("Congratulations, you guessed the word: %s\n", word);
//     } else {
//         printf("Sorry, you ran out of guesses. The word was: %s\n", word);
//     }
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct node {
    char letter;
    struct node *prev;
    struct node *next;
} Node;

int main() {
    char word[100];
    int word_length, i, guesses_left, correct_guesses;
    Node *head = NULL, *tail = NULL, *curr_node;
    char guess[2];
    srand(time(NULL));
    
    // Prompt user for word to guess
    printf("Enter a word for the player to guess: ");
    scanf("%s", word);
    word_length = strlen(word);
    
    // Initialize the doubly linked list with underscores for each letter in the word
    for (i = 0; i < word_length; i++) {
        curr_node = (Node*) malloc(sizeof(Node));
        curr_node->letter = '_';
        curr_node->prev = tail;
        curr_node->next = NULL;
        if (tail != NULL) {
            tail->next = curr_node;
        } else {
            head = curr_node;
        }
        tail = curr_node;
    }
    
    guesses_left = 6;  // Set initial number of guesses
    correct_guesses = 0;  // Set initial number of correct guesses
    
    // Play the game until the word is guessed or there are no more guesses left
    while (guesses_left > 0 && correct_guesses < word_length) {
        printf("You have %d guesses left.\n", guesses_left);
        printf("Current word: ");
        
        // Print the current state of the word
        curr_node = head;
        while (curr_node != NULL) {
            printf("%c ", curr_node->letter);
            curr_node = curr_node->next;
        }
        printf("\n");
        
        // Prompt user for a guess
        printf("Enter a letter guess: ");
        scanf("%s", guess);
        guess[0] = tolower(guess[0]);
        
        // Check if the guess is correct
        curr_node = head;
        i = 0;
        while (curr_node != NULL) {
            if (word[i] == guess[0]) {
                curr_node->letter = guess[0];
                correct_guesses++;
            }
            curr_node = curr_node->next;
            i++;
        }
        
        // Decrement number of guesses left if the guess is incorrect
        if (strchr(word, guess[0]) == NULL) {
            guesses_left--;
        }
    }
    
    // Print final message and reveal the word
    if (guesses_left == 0) {
        printf("Sorry, you lost! The word was %s.\n", word);
    } else {
        printf("Congratulations, you won! The word was %s.\n", word);
    }
    
    return 0;
}
