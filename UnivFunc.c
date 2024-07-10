#include <stdio.h>
#include <string.h>
#include "structs.h"

/*
	getString gets string input from the user
	@param string is the array of characters to be defined
*/
void 
getString(char *string)
{
	char ch;
	int i = 0;
	
	do
	{
		scanf("%c", &ch);
		
		if (ch != '\n') 
		{
			string[i] = ch;
			i++;
		}
	}while(ch != '\n'); // character gets added to string as long as it isn't \n.
	string[i] = '\0';
	
	//Ruiz's solution was used
}

/*
	swap swaps the positions of two items in the array of items
	@param a is an item whose position will be swapped with b
	@param b is an item whose position will be swapped with a
*/
void 
swap(itemType *a, 
	 itemType *b)
{
	itemType temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

/*
	sortProductID sorts the items in the item array in ascending order
	based on their product ID
	@param items is list of items with itemType data type
	@param itemNo is the amount of items in the list
*/
void 
sortproductID(itemType items[], 
			  int itemNo)
{
	int i, j, min;
	
	// selection sort for productID
	for(i = 0; i < itemNo - 1; i++)
	{
		min = i;
		for(j = i + 1; j < itemNo; j++) 
			if(items[min].productID > items[j].productID)
				min = j;
			
		if(min != i)
			swap(&items[i], &items[min]);
	}
	//Buencamino's solution was used
}

/*
	count counts the amount of items the user
	currently has by matching the userID and sellerID
	@param person is the logged in user
    @param items is list of items with itemType data type
	@param itemNo is the amount of items in the list
*/
int 
count(userType person, 
	  itemType items[], 
	  int itemNo)
{
	int i;
	int count = 0;
	
	for(i = 0; i < itemNo; i++)
	{// goes through all items
		if(person.userID == items[i].sellerID)
		{// checks if the item has the person's userID, if it does, count increments
			count++;
		}
	}
	return count;
	//Buencamino's solution was used
}

/*
	sortUserID sorts the registered users in ascending order
	based on their user ID
	@param otherpeople is the list of registered users
	@param numberofusers is the amount of users in the list
*/
void 
sortUserID(userType otherpeople[], 
		   int numberofusers)
{
	userType temp;
	int i, j, min;
	
	// selection sort for userID
	for(i = 0; i < numberofusers - 1; i++)
	{
		min = i;
		for(j = i + 1; j < numberofusers; j++)
		{
			if(otherpeople[min].userID > otherpeople[j].userID)
				min = j;
		}
		
		if(i != min)
		{
			temp = otherpeople[i];
			otherpeople[i] = otherpeople[min];
			otherpeople[min] = temp;
		}
	}
	
	//Improved version of both solutions
}

/*
	LoadUsers loads users from the "Users.txt" file
	@param otherpeople is the list of registered users
	@param numberofusers is the amount of users in the list
*/
void 
LoadUsers(userType users[], 
		  int *numberofusers)
{
	FILE *fp;
	int i;
	int valid;
	char ch;
	
	fp = fopen("Users.txt", "r");
	
	// if file opening was successful
	if(fp != NULL)
	{
		do
		{
			valid = fscanf(fp, "%d", &users[*numberofusers].userID);
			// if a userID got successfully scanned, scans for the rest
			if(valid == 1)
			{
				fscanf(fp, "%s ", users[*numberofusers].userPassword);
				
				i = 0; // scans username
				do
				{
					fscanf(fp, "%c", &ch);
					
					if (ch != '\n') 
					{
						users[*numberofusers].userName[i] = ch;
						i++;
					}
				}while(ch != '\n');
				users[*numberofusers].userName[i] = '\0';
				
				i = 0; // scans address
				do
				{
					fscanf(fp, "%c", &ch);
					
					if (ch != '\n') 
					{
						users[*numberofusers].userAddress[i] = ch;
						i++;
					}
				}while(ch != '\n');
				users[*numberofusers].userAddress[i] = '\0';
				
				fscanf(fp, "%d", &users[*numberofusers].userContactno);
				(*numberofusers)++; // starts at 0, increments after everything gets scanned
			}
		}while (valid == 1);
		fclose(fp);
	}
	else printf("Users.txt does not exist.\n"); // if file opening was not successful	
	//Ruiz's solution was used
}

/*
	LoadItems loads items from the "Items.txt" file
	@param items is list of items with itemType data type
	@param itemNo is the amount of items in the list
*/
void 
LoadItems(itemType items[], 
		  int *itemNo)
{
	FILE *fp;
	int i;
	int valid;
	char ch;
	char cdump;
	
	fp = fopen("Items.txt", "r");
	
	// if file opening was successful
	if(fp != NULL)
	{
		do
		{
			valid = fscanf(fp, "%d", &items[*itemNo].productID);
			// if a productID got successfully scanned, scans for the rest
			if(valid == 1)
			{	
				fscanf(fp, "%d", &items[*itemNo].sellerID);	
				fscanf(fp, "%c", &cdump);
				
				i = 0; // scans item name
				do
				{
					fscanf(fp, "%c", &ch);
					
					if (ch != '\n') 
					{
						items[*itemNo].itemName[i] = ch;
						i++;
					}
				}while(ch != '\n');
				items[*itemNo].itemName[i] = '\0';
				
				i = 0; // scans item category
				do
				{
					fscanf(fp, "%c", &ch);
					
					if (ch != '\n') 
					{
						items[*itemNo].itemCategory[i] = ch;
						i++;
					}
				}while(ch != '\n');
				items[*itemNo].itemCategory[i] = '\0';
				
				i = 0; // scans item description
				do
				{
					fscanf(fp, "%c", &ch);
					
					if (ch != '\n') 
					{
						items[*itemNo].itemDesc[i] = ch;
						i++;
					}
				}while(ch != '\n');
				items[*itemNo].itemDesc[i] = '\0';
				
				fscanf(fp, "%d", &items[*itemNo].itemQty);
				fscanf(fp, "%f", &items[*itemNo].itemPrice);
				(*itemNo)++; // starts at 0, increments after everything gets scanned
			}
		}while (valid == 1);
		fclose(fp);
	}
	else printf("Items.txt does not exist.\n"); // if file opening was not successful
	//Ruiz's solution was used
}

/*
	SaveUsers saves the array of users into the "Users.txt" file.
	@param users is the list of registered users
	@param numberofusers is the amount of users in the list
*/
void 
SaveUsers(userType users[], 
		  int numberofusers)
{
	FILE *fp;
	int i;
	
	fp = fopen("Users.txt", "w");
	
	if(fp != NULL)
	{
		for(i = 0; i < numberofusers; i++)
		{
			fprintf(fp, "%d %s\n", users[i].userID, users[i].userPassword);
			fprintf(fp, "%s\n", users[i].userName);
			fprintf(fp, "%s\n", users[i].userAddress);
			fprintf(fp, "%d\n", users[i].userContactno);
			fprintf(fp, "\n");
		}
		fclose(fp);
	}
	else printf("Error saving users.\n");
	//Ruiz's solution was used
}

/*
	SaveItems saves the array of items into the "Items.txt" file.
	@param items is list of items with itemType data type
	@param itemNo is the amount of items in the list
*/
void 
SaveItems(itemType items[], 
		  int itemNo)
{
	FILE *fp;
	int i;
	
	fp = fopen("Items.txt", "w");
	
	if(fp != NULL)
	{
		for(i = 0; i < itemNo; i++)
		{
			fprintf(fp, "%d %d\n", items[i].productID, items[i].sellerID);
			fprintf(fp, "%s\n", items[i].itemName);
			fprintf(fp, "%s\n", items[i].itemCategory);
			fprintf(fp, "%s\n", items[i].itemDesc);
			fprintf(fp, "%d %.2f\n", items[i].itemQty, items[i].itemPrice);
			fprintf(fp, "\n");
		}
		fclose(fp);
	}
	else printf("Error saving items.\n");
	//Improved version of both solutions
}
