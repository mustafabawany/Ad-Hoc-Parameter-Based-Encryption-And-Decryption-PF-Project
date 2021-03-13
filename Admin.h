void erase () {											// Function to remove all files.
	DeletePasswords ();
	remove ("Common.h");
	remove ("Encryption.h");
	remove ("Decryption.h");
	remove ("Admin.h");
	remove ("Menu.c");
	Flash_Screen (5);									// Flashes screen five times.
	exit (42);
}

void AdminMain () {
	system ("cls");																// Clears screen.
	system ("color 02");														// Interface color change.
	printf("\n\t\t\t  ________________________\n");								
	char string[] = "\n\t\t\t  $$$$$ Admin Portal $$$$$";
	for (int i = 0; i < strlen (string); i++) {	
		putchar (string[i]);													
		usleep (10000);															// Slow text movement.
	}
	
	printf("\n\t\t\t  _________________________");
	printf ("\n\n\n\t\t\t      ID : LMNTR!X");
	printf("\n\t\t\t    _________________");
	
    char Admin_Password[5] = ""; 
   	printf ("\n\n\t\t\t     PASSWORD: ");

	for (int i = 0; i < 4; i++) {	
		Admin_Password[i] = getch();              	
		printf("*");															// Does not show intputted password on screen.
	}
	
	if (strcmp (Admin_Password, "1250") == 0) {									// Verifies password.
		printf ("\n\nACCESS GRANTED.");
	}
	else {																		// Exits program on wrong password.
		printf("\n\n\aACCESS DENIED.");
		exit (0); //erase();
	}
	
	int Option;
	printf ("\n\n1. Password Generation \n2. Delete Passwords \n3. Erase\n4. Exit\n");	// Prints menu.
	printf("___________________");
	printf("\n\nEnter your choice: ");				
	scanf ("%d", &Option);																// Takes user's choice.
	switch (Option) {
		case 1:
			DeletePasswords ();															// Deletes old keys.
			GeneratePasswords ();														// Generates new keys.
			break;
		case 2:
			DeletePasswords ();	
			break;
		case 3:
			//erase ();															// Erases all files.
			break;
		case 4:
			exit (0);															// Exits the program.
			break;
	}
	main ();																	// Returns to main.
	return;
}
