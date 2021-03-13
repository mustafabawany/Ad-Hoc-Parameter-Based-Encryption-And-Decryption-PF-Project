void TimeDecrypt (char *Source_Name, char *Target_Name) {
	FILE *source = fopen (Source_Name, "r");					// Opens source and target files.
	FILE *target = fopen (Target_Name, "w");
	char Cypher_Text, Plain_Text;								// Character to read and character to print.
	int Seconds, Minutes;										// Encryption variables.
	long long int Source_Length = File_Length (source); 		// Fetches length of (encrypted) source file.
	fseek (source, ((Source_Length - 6) / 2), SEEK_SET);  	 	// Sets cursor to middle of unencrypted file.
	fscanf (source, "%d %d", &Seconds, &Minutes); 				// Fetches decryption variables "Seconds" and "Minutes".
	fseek (source, 0, SEEK_SET); 								// Resets cursor to beginning of file.
	for (int i = 0; i < Source_Length - 6; i++) { 				// Decryption loop.
		if (i == (Source_Length - 6) / 2) { 
			fseek (source, 6, SEEK_CUR);						// Skips part of file where encryption variables are stored.
		}
		Cypher_Text = fgetc (source);							// Fetches encrypted character from source file.
		Plain_Text = Cypher_Text - Seconds;						// All characters are decrypted using "Seconds".
		if (Prime_Check (i) == 1) {								// Characters which would have been at prime numbered positions in the unencrypted file are decrypted using both "Seconds" and "Minutes".
			Plain_Text -= Minutes;
		}
		fputc (Plain_Text, target);								// Prints decrypted character onto target file.
	}
	fclose (source);											// Closes source and target files.
	fclose (target);
	return;
}

void CaeserDecrypt (char *Source_Name, char *Target_Name) {
	FILE *source = fopen (Source_Name, "r");						// Opens source and target files.
	FILE *target = fopen (Target_Name, "w");
	char Plain_Text, Cypher_Text;
	while ((Cypher_Text = fgetc (source)) != EOF) {					// Fetches encrypted character from source file.
		if (Cypher_Text >= 'a' && Cypher_Text <= 'z') {				// Checks if "Cypher_Text" is a lowercase alphabet.
      		Plain_Text = Cypher_Text - Crypto_Key[1];				// Decrypts lowercase alphabet using 2nd digit of "Crypto_Key".
      		if (Plain_Text < 'a') {									// Checks if decrypted character is also a lowercase alphabet.
        		Plain_Text += 26;									// If not, makes it a lowercase alphabet.
      		}
		}
		else if (Cypher_Text >= 'A' && Cypher_Text <= 'Z') {		// Checks if "Cypher_Text" is an uppercase alphabet.
      		Plain_Text = Cypher_Text - Crypto_Key[3];				// Decrypts uppercase alphabet using 4th digit of "Crypto_Key".
      		if (Plain_Text < 'A') {									// Checks if decrypted character is also an uppercase alphabet.
        		Plain_Text += 26;									// If not, makes it an uppercase alphabet.
      		}
		}
		else {
			Plain_Text = Cypher_Text;								// If "Cypher_Text" is not an alphabet, it is not decrypted.
		}
		fputc (Plain_Text, target);									// Prints decrypted character onto target file.
	}
	fclose (source);												// Closes source and target files.
	fclose (target);
	return;
}

void LatinDecrypt (char *Source_Name, char *Target_Name) {
	FILE *source = fopen (Source_Name, "r");									// Opens source and target files.
	FILE *target = fopen (Target_Name, "w");
	char Cypher_Text[50], ch;
	int i;
	while (fscanf (source, "%s", Cypher_Text) != EOF) {							// File decryption loop.
		int String_Length = strlen (Cypher_Text);
		char Plain_Text[50] = "";														
		char ch = Cypher_Text[String_Length  - 2]; 								// Fetches 2nd last character of encrypted string which gives the number of characters
		int count = ch - 96;													// before the first vowel in the unencrypted string, and converts it into an integer.
		strncpy (Plain_Text, Cypher_Text + String_Length - 2 - count, count);	// Copies the characters that were originally placed before the vowel.
		strncat (Plain_Text, Cypher_Text, String_Length - 2 - count);			// Appends the rest of the characters starting with the vowel, drops the final 2 encrypting characters.
		fprintf (target, "%s", Plain_Text);
		if ((ch = fgetc(source)) != EOF) {										// Fetches the space or newline character after the string.
			fputc (ch, target);													// Prints it onto the target file.
		}
	}
	fclose (source);															// Closes source and target files.
	fclose (target);
	return;
}

void Decryption () {
	char File_Names[3][40] = {"", "", ""};																			// 2D array to store filenames.
	Get_File_Names ("decrypt", File_Names); 																		// Gets source file name from user, updates "File_Names" with file names to be used.
	password ("decrypt");																							// Validates decryption password and stores its relevant Crypto_Key digits.
	void (*Decryption_Functions[4]) (char *, char *) = {ReverseFile, LatinDecrypt, CaeserDecrypt, TimeDecrypt};		// Array of function pointers to hold all decryption functions.
	int FileNumber = 1;
	Decryption_Functions[3] (File_Names[0], File_Names[1]);
	for (int i = Crypto_Key[0] + 3; i > Crypto_Key[0]; i--) {														// Loop to call all decryption functions in a specific order based on the "Crypto_Key".
		Decryption_Functions[i % 3] (File_Names[2 - FileNumber % 2], File_Names[FileNumber % 2 + 1]);				// FileNumber is used to jump between files.
		FileNumber++;
	}
	remove (File_Names[1]);												// Removes temporary file.
	printf ("\n\nDecryption Sucessfull.");
	return;
}
