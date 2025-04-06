#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings


// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char *tryWord(char *plaintext, char *hashFilename)
{
    // Hash the plaintext
    char *hash = md5(plaintext, strlen(plaintext));

    // Open the hash file
    FILE *file = fopen(hashFilename, "r");
    if (file == NULL) 
    {
        return NULL;
    }

    // Loop through the hash file, one line at a time.
    char fileHash[HASH_LEN];
    while (fgets(fileHash, HASH_LEN, file)) 
    {
        
        // Remove newline character if it exists
        char *nl = strchr(fileHash, '\n');
        if (nl) *nl = '\0'; 

        // Attempt to match the hash from the file to the hash of the plaintext
        if (strcmp(hash, fileHash) == 0) 
        {
            // If there is a match, return the plaintext
            fclose(file); // Cleanup: close the file
            return hash;
        }
    }

    // If no match, return NULL.
    fclose(file); // Cleanup: close the file
    return NULL;  // Closing the function
}



int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // These two lines exist for testing. When you have
    // tryWord working, it should display the hash for "hello",
    // which is 5d41402abc4b2a76b9719d911017c592.
    // Then you can remove these two lines and complete the rest
    // of the main function below.


    // Open the dictionary file for reading.
    FILE *d = fopen(argv[2], "r");
    if(!d)
    {
        printf("Sorry can't open dictionary for reading\n");
        exit(1);
    }

    // For each dictionary word, pass it to tryWord, which
    // will attempt to match it against the hashes in the hash_file.
    char dictWord[PASS_LEN];
    int hashCrack = 0;

    while (fgets(dictWord, sizeof(dictWord), d)) 
    {
        // Remove newline character if it exists
        char *nl = strchr(dictWord, '\n');
        if (nl) *nl = '\0'; 

        // Attempt to match the current word against the hashes
        char *foundHash = tryWord(dictWord, argv[1]);
        
        // If we got a match, display the hash and the word.
        // For example: 5d41402abc4b2a76b9719d911017c592 hello
        if (foundHash != NULL) 
        {
            printf("%s %s\n", foundHash, dictWord);
            hashCrack++;  // Increment the counter for each cracked hash
        }
    }

    // Close the dictionary file.
    fclose(d);

    // Display the number of hashes that were cracked.
    printf("Cracked %d hashes.\n", hashCrack);
    
    // Free up any malloc'd memory?
    // If you allocated memory dynamically (e.g., using malloc), free it here.
    
}


