#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

//creates a constant string of the alphabet to compare the plaintext to, in order to match it to the key
const string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//creates a constant integer of the number of letters in the alphabet
const int A = 26;

//uses command line arguments to collect key
int main(int argc, string argv[])
{
//checks if there are 2 command line arguments (1 is the name of the file, other is the key). If not, prints error message
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int let[A];
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
// Checking if characters are alphabetical. If not, prints error message
        if (! isalpha(argv[1][i]))
        {
            printf("The key must only contain alphabetic characters.\n");
            return 1;
        }

//checks if there are not 26 characters, and if there aren't, prints error message
        else if (strlen(argv[1]) != A)
        {
            printf("The key must consist of least 26 alphabetical characters.\n");
            return 1;
        }

//checks if key is lowercase and converts to uppercase
        else if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
        {
            argv[1][i] = toupper(argv[1][i]);
        }

//checks for repeated characters using originally blank array which becomes filled
        for (int j = 0; j < A; j++)
        {
            if (argv[1][i] == let[j])
            {
                printf("The key must not contain repeated characters.\n");
                return 1;
            }
        }

        let[i] = argv[1][i];
    }

//prompts for plaintext
    string plain = get_string("plaintext: ");

//stores length of plaintext string
    int b = strlen(plain);

//creates array of one more element than plaintext length to store null
    char ciphert[b + 1];

    for (int i = 0; i < b; i++)
    {
// Check if uppercase, and then uses the already uppercase key and constant ALPHA
        if (isupper(plain[i]) != 0)
        {
            for (int j = 0; j < A; j++)
            {
//if plaintext character matches up with one of the alphabet letters, then the ciphert array matches the same location of the letter in the key
                if (plain[i] == ALPHA[j])
                {
                    ciphert[i] = argv[1][j];
                    break;
                }
            }
        }

//if the plain text is lowercase, the same process as above is executed except the constant and key are converted to lowercase
        else if (islower(plain[i]) != 0)
        {
            for (int j = 0, r = strlen(ALPHA); j < r; j++)
            {
                if (plain[i] == tolower(ALPHA[j]))
                {
                    ciphert[i] = tolower(argv[1][j]);
                    break;
                }
            }
        }

//if the plaintext is not alphabetical, then it stays the same (e.g. punctuation)
        else
        {
            ciphert[i] = plain[i];
        }
    }
    ciphert[b] = '\0';

//print ciphertext
    printf("ciphertext: %s\n", ciphert);
    return 0;
}