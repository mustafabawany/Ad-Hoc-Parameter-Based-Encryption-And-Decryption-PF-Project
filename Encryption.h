void TimeEncrypt (char *Source_Name, char *Target_Name) {
	FILE *source = fopen (Source_Name, "r");				// Opens source and target files.
	FILE *target = fopen (Target_Name, "w");
	char Plain_Text , Cypher_Text;
	long long int Source_Length = File_Length (source); 	// Fetches length of source file.
	time_t System_Time;								 		// Declaration of variable to store time.
	time (&System_Time);							 		// Stores system time in System_Time.
	struct tm *Time_Components = localtime (&System_Time); 	// Converts time into its components.
	int Seconds = Time_Components->tm_sec; 			 		// Fetches seconds in current system time.
	int Minutes = Time_Components->tm_min; 			 		// Fetches minutes in current system time.
	for (int i = 0; i < Source_Length; i++) { 				// Encryption loop.
		Plain_Text = fgetc (source);						// Unencrypted character is fetched from file.
		if (i == Source_Length / 2) { 					 	// Prints encryption variables "Seconds" and "Minutes" into the middle of the encrypted file.
			if (Seconds < 10) {								// Adds leading zero if "Seconds" is a single digit integer.
				fprintf (target, "0");
			}
			fprintf (target, "%d ", Seconds);
			if (Minutes < 10) {								// Adds leading zero if "Minutes" is a single digit integer.
				fprintf (target, "0");
			}
			fprintf (target, "%d ", Minutes);
		}
		Cypher_Text = Plain_Text + Seconds;					// All characters are encrypted using "Seconds".
		if (Prime_Check (i) == 1) {							// Characters at prime numbered positions are encrypted using both "Seconds" and "Minutes".
			Cypher_Text += Minutes;
		}
		fputc (Cypher_Text, target);						// Encrypted character is printed onto file.
	}
	fclose (source);										// Closes source and target files.
	fclose (target);
	return;
}

void CaeserEncrypt (char *Source_Name, char *Target_Name) {
	FILE *source = fopen (Source_Name, "r");						// Opens source and target files.
	FILE *target = fopen (Target_Name, "w");
	char Plain_Text, Cypher_Text;
	while ((Plain_Text = fgetc (source)) != EOF) {					// Fetches unencrypted character from source file.
		if (Plain_Text >= 'a' && Plain_Text <= 'z') {				// Checks if Plain_Text is a lowercase alphabet.
      		Cypher_Text = Plain_Text + Crypto_Key[1];				// Encrypts lowercase alphabet using 2nd digit of "Crypto_Key".
      		if (Cypher_Text > 'z') {								// Checks if encrypted character is also a lowercase alphabet.
        		Cypher_Text -= 26;									// If not, makes it a lowercase alphabet.
      		}
		}
		else if (Plain_Text >= 'A' && Plain_Text <= 'Z') {			// Checks if Plain_Texttext is an uppercase alphabet.
      		Cypher_Text = Plain_Text + Crypto_Key[3];				// Encrypts uppercase alphabet using 4th digit of "Crypto_Key".
      		if (Cypher_Text > 'Z') {								// Checks if encrypted character is also an uppercase alphabet.
        		Cypher_Text -= 26;									// If not, makes it an uppercase alphabet.
      		}
		}
		else {
			Cypher_Text = Plain_Text;								// If Plain_Text is not an alphabet, it is not encrypted.
		}
		fputc (Cypher_Text, target);								// Prints encrypted character onto target file.
	}
	fclose (source);												// Closes source and target files.
	fclose (target);
	return;
}

void ReverseFile (char *Source_Name, char *Target_Name) {
	FILE *source = fopen (Source_Name, "r");					// Opens source and target files.
	FILE *target = fopen (Target_Name, "w");
	char plain;
	long long int Source_Length = File_Length (source);			// Fetches length of source file.
	fseek (source, -1, SEEK_END);            					// Sets cursor to one character before end of file.
	while (Source_Length > 0) {									// Loop runs till all characters of the file have been accessed.
		plain = getc (source);									// Fetches character from source file, starting with the last character.
		fputc (plain, target);									// Prints the fetches character onto the target file.
		fseek (source, -2, SEEK_CUR);							// Sets cursor back 2 characters to read next character (in reverse order).
		if (plain == '\n') {									
			fseek (source, -1, SEEK_CUR);						// Sets cursor back one more character if a newline is encountered.
		}
		Source_Length--;										// Decrements remaining characters.
	}
	fclose (source);											// Closes source and target files.
	fclose (target);
	return;
}

void LatinEncrypt (char *Source_Name, char *Target_Name) {
	FILE *source = fopen (Source_Name, "r");					// Opens source and target files.
	FILE *target = fopen (Target_Name, "w");
	char Plain_Text[50], ch;
	int i;
	while (fscanf (source, "%s", Plain_Text) != EOF) {			// File encryption loop.
		char Cypher_Text[50] = "";
		for (i = 0; i < strlen (Plain_Text); i++) {				// String encryption loop.
			if (VowelCheck (Plain_Text[i]) == 1) {				// Executed when the first vowel in the "Plain_Text" is found.
				strcpy (Cypher_Text, Plain_Text + i); 		 	// Copies "Plain_Text" into "Cypher_Text" excluding the characters before the first vowel.
				strncat (Cypher_Text, Plain_Text, i);			// Appends the characters before the first vowel in "Plain_Text" onto "Cypher_Text"
				break;											// Breaks out of loop after encryption.
			}
		}
		if (i == strlen (Plain_Text)) {							// Executed if string contained no vowels.
			strcpy (Cypher_Text, Plain_Text);					// String is left unencrypted if it contained no vowels.
		}
		fprintf (target, "%s", Cypher_Text);					// Prints encrypted string onto file.
		fprintf (target, "%cy", i + 96);						// Prints two characters after the string - the first one is a counter for the number of characters before the first vowel, the second is always 'y'.
		if ((ch = fgetc(source)) != EOF) {						// Fetches the space or newline character after the string.
			fputc (ch, target);									// Prints it onto the target file.
		}
	}
	fclose (source);											// Closes source and target files.
	fclose (target);
	return;
}

void Encryption () {
	char File_Names[3][40] = {"", "", ""};																		// 2D array to store filenames.
	Get_File_Names ("encrypt", File_Names); 																	// Gets source file name from user, updates "File_Names" with file names to be used.
	password ("encrypt");																						// Validates password and stores both its components.
	void (*Encryption_Functions[4]) (char *, char *) = {LatinEncrypt, CaeserEncrypt, ReverseFile, TimeEncrypt}; // Array of function pointers to hold all encryption functions.
	int FileNumber_A = 0, FileNumber_B = 0;
	for (int i = Crypto_Key[0]; i < Crypto_Key[0] + 3; i++) {		 											// Loop to call all encryption functions in a specific order based on the "Crypto_Key".
		Encryption_Functions[i % 3] (File_Names[FileNumber_A], File_Names[FileNumber_B % 2 + 1]);				// FileNumber_A and FileNumber_B are used to jump between files.
		FileNumber_B++;
		FileNumber_A = 2 - FileNumber_B % 2;
	}
	Encryption_Functions[3] (File_Names[1], File_Names[2]);
	remove (File_Names[1]);											// Removes temporary file.
	printf ("\n\nEncryption Succesful.");
	return;
}
