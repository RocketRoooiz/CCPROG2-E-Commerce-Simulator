#include "AdminMenu.c"
#include "BuyMenu.c"
#include "SellMenu.c"
#include "structs.h"

/*
	UserReg allows the user to register modify an element in the list of users and
		adds to the number of users. The users in this list can login and navigate 
		the program based on their credentials.
	@param users is the list of users with userType data type
	@param *numberofusers is the address that contains the number of users in the list
*/

void
UserReg(userType users[], 
		int *numberofusers)
{
	int i;
	char cdump;
	
	printf("\nUser Registration Selected!\n\nInput the following:\n");
	printf("Enter your user ID: ");
	scanf("%d", &users[*numberofusers].userID); //ask user for input
	
	for(i = 0; i < *numberofusers; i++) //for checking if userID is unique
	{
		if(users[*numberofusers].userID == users[i].userID)
		{ //Keep checking until inputted user ID is unique
			printf("UserID already taken! Please enter a new one: ");
			scanf("%d", &users[*numberofusers].userID);
			i = -1;
		}
	}
	//Initialize the user struct at that index
	printf("Enter your password: ");
	scanf("%s", users[*numberofusers].userPassword);
	scanf("%c", &cdump);
	
	printf("Enter your address: ");
	getString(users[*numberofusers].userAddress);
	
	printf("Enter your contact number: ");
	scanf("%d", &users[*numberofusers].userContactno);
	scanf("%c", &cdump);
	
	printf("Enter your username: ");
	getString(users[*numberofusers].userName);
	
	printf("\nUser registration complete!\nHeading to main menu...\n");
	(*numberofusers)++; //Makes sure the next user to register is on the next index
	
	//Ruiz's solution was used
}

/*
	LoadCart loads the user's cart from the "<userID>.txt" file.
	@param person is the logged in user
	@param cart is an itemType that holds the user's cart
	@param *itemsincart is the address that contains the number of items in the user's cart
*/
void
LoadCart(userType person, 
		 itemType cart[], 
		 int *itemsincart)
{
	FILE *fp;
	int i, valid;
	String20 fileName;
	char ch, cdump;
	
	sprintf(fileName, "%d", person.userID);
	strcat(fileName, ".txt"); 
	
	fp = fopen(fileName, "r"); //Opens a text file with their user ID as a name
	
	if(fp != NULL)
	{
		do
		{
			valid = fscanf(fp, "%d", &cart[*itemsincart].productID);
			if(valid == 1) //Continues to scan the file when a product ID integer is scanned
			{
				//Initialize the contents of the carts based on the contents of the file
				fscanf(fp, "%d", &cart[*itemsincart].sellerID);	
				fscanf(fp, "%c", &cdump);
				
				i = 0;
				do
				{//scans item name
					fscanf(fp, "%c", &ch);
					
					if (ch != '\n') 
					{
						cart[*itemsincart].itemName[i] = ch;
						i++;
					}
				}while(ch != '\n');
				cart[*itemsincart].itemName[i] = '\0';
				
				i = 0;
				do
				{//scans item category
					fscanf(fp, "%c", &ch);
					
					if (ch != '\n') 
					{
						cart[*itemsincart].itemCategory[i] = ch;
						i++;
					}
				}while(ch != '\n');
				cart[*itemsincart].itemCategory[i] = '\0';
				
				i = 0;
				do
				{//scans item description
					fscanf(fp, "%c", &ch);
					
					if (ch != '\n') 
					{
						cart[*itemsincart].itemDesc[i] = ch;
						i++;
					}
				}while(ch != '\n');
				cart[*itemsincart].itemDesc[i] = '\0';
				
				fscanf(fp, "%d", &cart[*itemsincart].itemQty);
				fscanf(fp, "%f", &cart[*itemsincart].itemPrice);
				(*itemsincart)++; //note: it started at 0
			}
		}while (valid == 1);
		fclose(fp);
	}
	else printf("No previous carts found.");
	//Improved version of both solutions
}

/*
	ExitUserMenu saves the user's cart to a "<userID>.txt" file.
	@param person is the logged in user
	@param cart is an itemType that holds the user's cart
	@param *itemsincart is the address that contains the number of items in the user's cart
*/
void 
ExitUserMenu(userType person, 
			 itemType cart[], 
			 int itemsincart)
{
	FILE *fp;
	int i;
	String20 fileName;
	
	sprintf(fileName, "%d", person.userID);
	strcat(fileName, ".txt");
	
	fp = fopen(fileName, "w"); //creates a text file with the userID as name
	
	for(i = 0; i < itemsincart; i++)
	{
		//prints the contents of the cart to the file with same format to items.txt
		fprintf(fp, "%d %d\n", cart[i].productID, cart[i].sellerID);
		fprintf(fp, "%s\n", cart[i].itemName);
		fprintf(fp, "%s\n", cart[i].itemCategory);
		fprintf(fp, "%s\n", cart[i].itemDesc);
		fprintf(fp, "%d %.2f\n", cart[i].itemQty, cart[i].itemPrice);
		fprintf(fp, "\n");
	}
	fclose(fp);
	
	//Buencamino's solution was used
}

/*
	UserMenu asks the user of their ID and password and allow them to purchase from
		the buy menu or modify or check their products with the sell menu.
	@param users is the list of users with userType data type
	@param *numberofusers is the address that contains the number of users in the list
	@param items is the list of items with the itemType data type
	@param *itemNo is the address that contains the number of items in the list
*/
void
UserMenu(userType users[], 
		 int *numberofusers, 
		 arrayitems items, 
		 int *itemNo)
{
	int inputID, i, nUserChoice = 0;
	int validID, itemsincart = 0;
	//validID also serves as index.
	String10 inputPassword;
	itemType cart[10];
	//Ask the user for inputs
	printf("Enter your user ID: ");
	scanf("%d", &inputID);
	printf("Enter your password: ");
	scanf("%s", inputPassword);
	
	for(i = 0, validID = -1; i < *numberofusers && validID == -1; i++) 
	{
		if (inputID == users[i].userID)
		{//if inputted ID is in the list of userIDs.
			validID = i;
		}//it saves the index of where that userID is found.
	}
	
	if(strcmp(inputPassword, users[validID].userPassword) == 0) 
	{//compares to see if inputted password is in the index of where the userID is found.
		printf("\n        Successful Login!\n");
		
		do
		{
			printf("\n|-------------------------------|\n");
			printf("|           User Menu           |\n");
			printf("|-------------------------------|\n");
			printf("|                               |\n");
			printf("|     1 - Sell Menu             |\n");
			printf("|     2 - Buy Menu              |\n");
			printf("|     3 - Exit User Menu        |\n");
			printf("|                               |\n");
			printf("|-------------------------------|\n\n");
			
			do 
			{
				printf("Insert Valid Input: ");
				scanf("%d", &nUserChoice); //Ask the user for inputs
			}while(nUserChoice > 3 || nUserChoice < 1);
			
			switch (nUserChoice) 
			{
				case 1: SellMenu(&users[validID], items, itemNo, *numberofusers); //Access the sell menu
						break;
						
				case 2: if(itemsincart == 0)
							LoadCart(users[validID], cart, &itemsincart); //Load cart of the user
							
						BuyMenu(&users[validID], items, itemNo, *numberofusers, users, cart, &itemsincart); //Access the buy menu
						break;
						
				case 3: ExitUserMenu(users[validID], cart, itemsincart); //Returns to the main menu and saves the cart of the user
						break;
			}
		}while(nUserChoice != 3);
	}
	
	else
		printf("Invalid credentials!\n");
		
	//Ruiz's solution was used
}

/*
	MainMenu presents the user with a menu and a choice of inputs which allows them to
		navigate the entire program as either a seller, buyer, or admin.
	@param users is the list of users with userType data type
	@param *numberofusers is the address that contains the number of users in the list
	@param items is the list of items with the itemType data type
	@param *itemNo is the address that contains the number of items in the list
*/
void 
MainMenu(userType users[], 
		 int *numberofusers, 
		 arrayitems items, 
		 int *itemNo)
{
	int nChoice;
	do 
	{
		//Displays the main menu
		printf("\n      Welcome to Not Shopee!\n");
		printf("|-------------------------------|\n");
		printf("|        Select Function        |\n");
		printf("|-------------------------------|\n");
		printf("|                               |\n");
		printf("|     1 - User Registration     |\n");
		printf("|     2 - User Menu             |\n");
		printf("|     3 - Admin Menu            |\n");
		printf("|     4 - Exit                  |\n");
		printf("|                               |\n");
		printf("|-------------------------------|\n\n");
		
		printf("Insert Valid Input: ");
		scanf("%d", &nChoice); //Ask user for input
	
		switch(nChoice) 
		{
			case 1: if(*numberofusers < 100)
						UserReg(users, numberofusers);
					else
						printf("MAX USERS REACHED!\n");
					break; //register new user
					
			case 2: UserMenu(users, numberofusers, items, itemNo);
					break; //Access the user menu
					
			case 3: AdminMenu(users, numberofusers, items, *itemNo);
					break; //Access admin menu
					
			case 4: SaveUsers(users, *numberofusers);
					SaveItems(items, *itemNo);
					break; //End the program and save contents to Users.txt and Items.txt
		}
	}while(nChoice != 4);
	
	//Buencamino's solution was used
}
