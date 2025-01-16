#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Function to generate a password
void generatePassword(int length, int useLower, int useUpper, int useDigits, int useSpecial, char *password) {
    const char lower[] = "abcdefghijklmnopqrstuvwxyz";
    const char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char digits[] = "0123456789";
    const char special[] = "!@#$%^&*()";
    char possibleChars[100] = "";

    // Build the character pool
    if (useLower) strcat(possibleChars, lower);
    if (useUpper) strcat(possibleChars, upper);
    if (useDigits) strcat(possibleChars, digits);
    if (useSpecial) strcat(possibleChars, special);

    // Check if no character sets were selected
    if (strlen(possibleChars) == 0) {
        printf("Error: No character sets selected. Cannot generate password.\n");
        password[0] = '\0';  // Return an empty string
        return;
    }

    // Generate the password
    srand(time(0));  // Seed random number generator
    for (int i = 0; i < length; i++) {
        password[i] = possibleChars[rand() % strlen(possibleChars)];
    }
    password[length] = '\0';  // Null-terminate the password
}

// Function to analyze password strength
void analyzePasswordStrength(const char *password) {
    int length = strlen(password);
    int hasLower = 0, hasUpper = 0, hasDigit = 0, hasSpecial = 0, score = 0;

    // Analyze the password
    for (int i = 0; i < length; i++) {
        if (islower(password[i])) hasLower = 1;
        else if (isupper(password[i])) hasUpper = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else hasSpecial = 1;
    }

    // Calculate score
    if (hasLower) score += 10;
    if (hasUpper) score += 10;
    if (hasDigit) score += 10;
    if (hasSpecial) score += 10;
    if (length >= 12) score += 20;  // Bonus for longer passwords
    else if (length >= 8) score += 10;

    // Provide feedback
    if (score < 30)
        printf("Strength: Weak\n");
    else if (score < 50)
        printf("Strength: Moderate\n");
    else
        printf("Strength: Strong\n");
}

int main() {
    int length, useLower, useUpper, useDigits, useSpecial;
    char password[100];

    // Get user inputs for password generation
    printf("Enter the desired password length: ");
    scanf("%d", &length);

    printf("Include lowercase letters? (1 for Yes, 0 for No): ");
    scanf("%d", &useLower);

    printf("Include uppercase letters? (1 for Yes, 0 for No): ");
    scanf("%d", &useUpper);

    printf("Include digits? (1 for Yes, 0 for No): ");
    scanf("%d", &useDigits);

    printf("Include special characters? (1 for Yes, 0 for No): ");
    scanf("%d", &useSpecial);

    // Generate the password
    generatePassword(length, useLower, useUpper, useDigits, useSpecial, password);

    if (strlen(password) > 0) {
        // Display the generated password
        printf("Generated Password: %s\n", password);

        // Analyze and display the strength of the password
        analyzePasswordStrength(password);
    }

    return 0;
}


