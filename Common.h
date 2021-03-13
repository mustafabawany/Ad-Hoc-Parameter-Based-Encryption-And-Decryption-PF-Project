void Get_File_Names (char* Type, char File_Names[3][40]) {
	printf ("\nEnter the Name of the File to %s: ", Type);
	gets (File_Names[0]);												// Gets source file name from user.
	strcpy (File_Names[2], Type);										// Copies encrypt/decrypt into target file name.
	strcat (File_Names[2], "ed_");										// Appends ed_ to target file name.
	strcat (File_Names[2], File_Names[0]);								// Target name is in format: encrypted_(source name)
	strcat (File_Names[0], ".txt");										// Appends file format at end of source name.
	strcat (File_Names[2], ".txt");										// Appends file format at end of target name.
	strcpy (File_Names[1], "temp.txt");									// Name of temporary file.
	
	FILE *fptr;															// Checks if files can be opened/created.
	fptr = fopen (File_Names[0], "r");									// Check if source file exists.
	if (fptr == NULL) {
		printf ("\n\aSource file not found.");
		exit (1);
	}
	fclose (fptr);
	fptr = fopen (File_Names[1], "w");									// Checks if temporary file can be created.
	if (fptr == NULL) {
		printf ("\n\aCould not create temporary file.");
		exit (1);
	}
	fclose (fptr);
	fptr = fopen (File_Names[2], "w");									// Checks if target file can be created.
	if (fptr == NULL) {
		printf ("\n\aCould not create target file.");
		exit (1);
	}
	fclose (fptr);
	return;
}

int Prime_Check (int a) {												// Function to check if number is prime.
	for (int i = 2; i < a; i++) {
		if (a % i == 0) {
			return 0;													// Returns 0 if number is not prime.
		}
	}
	return 1;															// Returns 1 if number is prime.
}	

int VowelCheck (char x) {					// Function to check if given character is a vowel or not, returns 1 for vowel, 0 for consonant.
	return (x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u' || x == 'A' || x == 'E' || x == 'I' || x == 'O' || x == 'U');		
}

long long int File_Length (FILE *fptr) {						// Function to calculate file length.
	long long int i;
	for (i = 0; fgetc (fptr) != EOF; i++);						// Counts number of characters in file.
	fseek (fptr, 0, SEEK_SET);									// Resets file cursor to start of file.
	return i;													// Returns number of characters in file.
}

void Flash_Screen (int count) {									// Function to flash screen.
	char string[9] = "color 0F";
	for (int i = 0; i < count; i++) {							// Flashes screen 'count' times.
		string[6] = i % 2 + 48;									// Changes background color between blue and black.
		system (string);										// Flashes between blue and black.
	}
	return;
}

void Skull () {													// Function to print skull.
	system ("color 02");
	printf ("\n\t\t\t");
	printf (" _;~)                  (~;_");
	printf ("\n\t\t\t");
	printf ("(   |                  |   )");
	printf ("\n\t\t\t");
	printf(" ~', ',    ,''~'',   ,' ,'~");
	printf ("\n\t\t\t");
	printf("    ', ','       ',' ,'    ");
	printf ("\n\t\t\t");
	printf("      ',: {'} {'} :,'      ");
	printf ("\n\t\t\t");
	printf("        ;   /^\\   ;        ");
	printf ("\n\t\t\t");
	printf("         ~\\  ~  /~         ");
	printf ("\n\t\t\t");
	printf("       ,' ,~~~~~, '       ");
	printf ("\n\t\t\t");
	printf("     ,' ,' ;~~~; ', ',     ");
	printf ("\n\t\t\t");
	printf("   ,' ,'    '''    ', ',   ");
	printf ("\n\t\t\t");
	printf(" (~  ;               ;  ~) ");
	printf ("\n\t\t\t");
	printf("  -;_)               (_;-  ");
	return;
}
