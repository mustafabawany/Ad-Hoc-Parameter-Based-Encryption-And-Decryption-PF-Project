int main ();
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include "Password.h"
#include "Common.h"
#include "Encryption.h"
#include "Decryption.h"
#include "Admin.h"

int main () {
	
	system ("cls");														// Clears screen.
	char string[] = "\n\t\t   *---- Encryption & Decryption ----*";
  	system("color 4F");													//Interface Color Change.	   
	for (int i = 0; i < strlen (string); i++) {	
		putchar(string[i]);													
		usleep(10000);													// Prints text slowly.
	}

	int Option = 1;
	while (Option != 3) {												// Loops ends when user enters 3.
		
		printf("\n\t\t\t   _____________");								// Prints menu.
		printf("\n\n\t\t\t     Main Menu");
		printf("\n\t\t\t   _____________");		
		printf("\n\n1. Encryption \n2. Decryption \n3. Exit \n");
		printf("___________________");
		printf("\n\nEnter your choice: ");
		scanf ("%d", &Option);											// Takes user's choice.
		fflush (stdin);													// Clears input buffer.
		
		switch (Option) {
			case 1:
				Encryption ();											// Calls encryption main function.
				break;
			case 2:
				Decryption (); 											// Calls decryption main function.
				break;
			case 3:
				break;
			case 0:
				DeletePasswords ();										// Deletes private and public keys.
				printf ("\a");											// Beep.
				system ("cls");											// Clears screen.
				Flash_Screen (5);										// Flashes screen three times.
				Skull ();												// Prints skull
				exit (42);												// Exits the program.
				break;
			case 7:
				AdminMain ();											// Calls admin main function.
				break;
			default:
				printf ("\nPlease enter a valid value.\n");				// If user enters an option not on the menu.
				break;
		}
	}
	return 0;	
}
