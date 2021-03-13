int Crypto_Key[4];																	// Global array to hold digits of encryption/decryption key.

void GeneratePasswords () {										// Function to generate public and private keys.
	srand (time (NULL));										// Seeds random generator using time.
	int flag[9999] = {0};										// Flag array to ensure unique keys.
	FILE *fptr = fopen ("passwords.txt", "w");					// Opens password file in write mode.
	int Private_Key, Public_Key;
	for (int i = 0; i < 100; i++) {
		Private_Key = rand () % 9000 + 1000;					// Generates a random 4 digit private key.
		Public_Key =  ((rand () % 10) * 1000) + ((Private_Key / 1000) * 100) + ((Private_Key % 10) * 10) + rand () % 10;	// Generates Public_Key based on Private_Key
		if (Public_Key < 1000) {							
			Public_Key += 1000;									// Ensures Public_Key is a 4 digit number.
		}
		if (flag[Private_Key] == 1) {							// Ensure Private_Key is unique.
			continue;
		}
		else if (flag[Public_Key] == 1) {						// Ensures Public_Key is unique.
			continue;
		}
		else {
			flag[Private_Key] = 1;								// Flags the keys that have been generated.
			flag[Public_Key] = 1;
			fprintf (fptr, "%d!%d\n", Private_Key, Public_Key);	// Prints generated keys onto file.
		}
	}
	fclose (fptr);												// Closes password file.
	return;
}

void DeletePasswords () {								// Function to delete public and private keys.	
	remove ("passwords.txt");
	return;
}

void password (char Type[]) {
	FILE *passwordDB = fopen ("passwords.txt", "r");								// Opens password database.
	if (passwordDB == NULL) {
		printf ("\n\aPassword Database Not Found.");
		exit (1);
	}
	int User_Password, Private_Key = 0, Public_Key = 0;
	printf ("\nEnter File %sion Password: ", Type);										// Takes user's password.
	scanf ("%d", &User_Password);
	while (Private_Key != User_Password && Public_Key != User_Password) {			// Ensures password is in database.
		if (fscanf (passwordDB, "%d!%d\n", &Private_Key, &Public_Key) == EOF) {		// If password is not found in entire database.
			Private_Key = Public_Key = 0;
			fseek (passwordDB, 0, SEEK_SET);										// Resets cursor to beginning of database.
			printf ("\n\aInvalid Password. \nPlease enter again: ");					// Asks for a new password.
			scanf ("%d", &User_Password);
		}
	}
	if (Private_Key == User_Password) {												// If the user entered a private key.
		printf ("\nPrivate Key Validated.");
		Crypto_Key[0] = (User_Password / 1000) % 10;								// 1st digit of "Crypto_Key" is the 1st digit of "Private_Key".
		Crypto_Key[1] = User_Password % 10;											// 2nd digit of "Crypto_Key" is the 4th digit of "Private_Key"
	}
	else {																			// If the user entered a public key.
		printf ("\nPublic Key Validated.");
		Crypto_Key[0] = (User_Password / 100) % 10;									// 1st digit of "Crypto_Key" is the 2nd digit of "Public_Key".
		Crypto_Key[1] = (User_Password / 10) % 10;									// 2nd digit of "Crypto_Key" is the 3rd digit of "Public_Key"
	}
	Crypto_Key[2] = (Crypto_Key[0] + Crypto_Key[1]) % 10;							// 3rd digit of "Crypto_Key" is the sum of its 1st and 2nd digits.
	Crypto_Key[3] = (Crypto_Key[0] * Crypto_Key[1]) % 10;							// 4th digit of "Crypto_Key" is the product of its 1st and 2 digits.
	printf ("\n\n%sion Key Generated.\n", Type);
	fclose (passwordDB);															// Closes password database.
	return;
}
