#include "structs.h"
	
/*
	stockMenu allows the user to modify the members of a specific struct itemType.
	@param *item is the item struct to be modified
*/
void 
stockMenu(itemType *item) 
{
	int nChoice, nNum;
	char dump;
	float fNum;
	
	do 
	{
		//print the display menu
		printf("\n|---------------------------------------|\n");
		printf("|               Edit Stock              |\n");
		printf("|---------------------------------------|\n");
		printf("|                                       |\n");
		printf("|     1 - Replenish                     |\n");
		printf("|     2 - Change Price                  |\n");
		printf("|     3 - Change Item Name              |\n");
		printf("|     4 - Change Category               |\n");
		printf("|     5 - Change Description            |\n");
		printf("|     6 - Finish Editing                |\n");
		printf("|                                       |\n");
		printf("|---------------------------------------|\n\n");
		//Ask user for input, loops until valid input is given
		do 
		{
			printf("Insert Valid Input: ");
			scanf("%d", &nChoice);
			scanf("%c", &dump);
		}while(nChoice > 6 || nChoice < 1);
		
		switch (nChoice) 
		{
			case 1: printf("Enter quantity to be added: ");
					scanf("%d", &nNum);
					item->itemQty += nNum; //Increase the item's quantity
					break;
			
			case 2: printf("Enter New Unit Price: ");
					scanf("%f", &fNum);
					item->itemPrice = fNum; //Changes item price
					break;
			
			case 3: printf("Enter New Item Name: ");
					getString(item->itemName); //Changes the string of itemName
					break;
			
			case 4: printf("Enter New Item Category: ");
					getString(item->itemCategory); //Changes itemCategory string
					break;
			
			case 5: printf("Enter New Item Description: ");
					getString(item->itemDesc); //Changes itemDesc string
					break;
			
			case 6: break;
		}
	}while(nChoice != 6);
	
	//Buencamino's solution was used
}

/*
	editStock asks the user for a specific product ID of an item they have the 
		intention to modify and calls the menu to do so.
	@param person is the logged in seller
	@param item is the list of items with itemType data type
	@param itemNo is the number of items in the list
*/
void 
editStock(userType person, 
		  arrayitems item, 
		  int itemNo) 
{
	int checkID, i, found = 0;
	
	showProducts(item, itemNo, person);
	printf("Enter Product ID: ");//Ask for input
	scanf("%d", &checkID);
	
	for (i = 0; i < itemNo && found == 0; i++) 
	{
		//Searches the entire item array to find an item with the same product ID as input as well as seller ID as the user
		if (item[i].productID == checkID && person.userID == item[i].sellerID) 
		{
			found = 1;
			stockMenu(&item[i]); //calls stockMenu then breaks the loop
		}
	}
	
	if(found == 0)
		printf("PRODUCT ID NOT FOUND");
		
	//Buencamino's solution was used
}

/*
	AddNewItem allows the user to add a new item to their list of items to be sold.
	@param person is the logged in seller
	@param items is the list of items with itemType data type
	@param itemNo is number of items in the list
*/
void 
AddNewItem(userType person, 
		   arrayitems items, 
		   int itemNo) 
{
	char cdump;
	int i, unique = 1;

	do{
		unique = 1;
		printf("Enter Unique Item Product ID: ");
		scanf("%d", &items[itemNo].productID);//Asks the user for input
		scanf("%c", &cdump);
		
		for(i = 0; i < itemNo && unique == 1; i++)
		{//search the entire item array to check if input productID is unique
			if(items[i].productID == items[itemNo].productID)
			{
				unique = 0;
				printf("Item Product ID has been taken already!\n");
			}
			
			if(items[itemNo].productID < 0)
			{
				unique = 0;
				printf("Item Product ID is Invalid!\n");
			}
		}
	}while(unique == 0);
	//Initialize the contents of the item struct
	printf("\nEnter Item Name: ");
	getString(items[itemNo].itemName);
	
	printf("\nEnter Item Category: ");
	getString(items[itemNo].itemCategory);
	
	printf("\nEnter Item Description: ");
	getString(items[itemNo].itemDesc);
	
	printf("\nEnter Item Quantity: ");
	scanf("%d", &items[itemNo].itemQty);
	
	printf("\nEnter Item Price: ");
	scanf("%f", &items[itemNo].itemPrice);
	
	items[itemNo].sellerID = person.userID;
	
	//Improved version of both solutions
}

/*
	LowStock displays the seller's product with less then 5 quantity.
	@param person is the logged in seller
	@param itemNo is number of items in the list
	@param items is the list of items with itemType data type
*/
void 
LowStock(userType person, 
		 int itemNo, 
		 arrayitems items)
{
	itemType temp[20]; //temp array to store products with qty <5
	int i, j = 0;
	
	for(i = 0; i < itemNo; i++) 
	{
		if(items[i].itemQty < 5 && items[i].sellerID == person.userID) 
		{
			temp[j] = items[i];
			j++;
		}
	}

	printf("Products with low stock: \n");
	if(j > 0)
		showProductByPage(temp, j); //displays contents of temp array
	else
		printf("ALL PRODUCTS ARE PROPERLY STOCKED!\n");
		
	//Ruiz's solution was used
}

/*
	SellMenu presents the seller multiple options to edit and display their catalogue 
		of products and calls other functions based on user input.
	@param *person is the logged in seller
	@param items is list of items with itemType data type
	@param *itemNo is the address that contains the number of items in the list
	@param numberofusers is the number of registered users in the list of users
*/
void 
SellMenu(userType *person, 
		 arrayitems items, 
		 int *itemNo, 
		 int numberofusers) 
{
	int nChoice;
	
	do
	{
		//display the menu to the user
		printf("\n|---------------------------------------|\n");
		printf("|               Sell Menu               |\n");
		printf("|---------------------------------------|\n");
		printf("|                                       |\n");
		printf("|     1 - Add New Item                  |\n");
		printf("|     2 - Edit Stock                    |\n");
		printf("|     3 - Show My Products              |\n");
		printf("|     4 - Show My Low Stock Products    |\n");
		printf("|     5 - Exit Sell Menu                |\n");
		printf("|                                       |\n");
		printf("|---------------------------------------|\n\n");
		
		do 
		{
			printf("Insert Valid Input: ");
			scanf("%d", &nChoice); //ask the user for input
		} while (nChoice > 5 || nChoice < 1);
		
		switch (nChoice) 
		{ //calls a function based on user input
			case 1: if (count(*person, items, *itemNo) >= 20)
					{
						printf("Max item limit reached!\n"); //makes sure the user has less than 20 items before they can add
					} 
					else 
					{
						AddNewItem(*person, items, *itemNo);
						*itemNo+=1;
					}
					break; //add a new product
			
			case 2: sortproductID(items, *itemNo);
					editStock(*person, items, *itemNo);
					break; //allows user to edit stock info
			
			case 3: sortproductID(items, *itemNo);
					showProducts(items, *itemNo, *person);
					break; //show user's products
			
			case 4: if(count(*person, items, *itemNo) > 0)
						LowStock(*person, *itemNo, items);
					else
						printf("USER HAS NO PRODUCTS!\n");
					break; //show user's low stock items
			
			case 5: break; //exit sell menu
		}
	}while(nChoice != 5);
	
	//Ruiz's solution was used
}
