#include "structs.h"

/*
	showProducts presents all the items that are being sold by a specific seller.
	@param item is the list of items with the itemType data type
	@param itemNo is the number of items in the list
	@param person is a registered user
*/
void 
showProducts(itemType item[], 
			 int itemNo, 
			 userType person)
{
	int i;
	
	printf("\nShowing Products [sorted by product ID]:");
	printf("\n|  Product ID  |      Item Name      |    Category    |   Price   |  Quantity  |\n");
	
	for (i = 0; i < itemNo; i++) 
	{
		if(item[i].sellerID == person.userID)
		{ // for making sure itemID is the same as sellerID
			printf("|%-14d|%21s|%16s|%-11.2f|%-12d|\n", item[i].productID, item[i].itemName, item[i].itemCategory,
			item[i].itemPrice, item[i].itemQty);
		}
	}
}

/*
	showProductByPage presents all the items that meets a certain criteria in page format.
	@param temp is the list of items with the itemType data type that meets the criteria
	@param limit is the number of items that meets that criteria
*/
void 
showProductByPage(itemType temp[], 
				  int limit)
{
	char input;
	int i = 0;
	
	do 
	{
		printf("\nProduct ID: %d\n", temp[i].productID);
		printf("Item Name: %s\n", temp[i].itemName);
		printf("Category: %s\n", temp[i].itemCategory);
		printf("Description: %s\n", temp[i].itemDesc);
		printf("Quantity: %d\n", temp[i].itemQty);
		printf("Price: %.2f\n", temp[i].itemPrice);
		
		printf("\nActions\n");
		printf("N - Next Product\n");
		printf("X - Exit\n");
		
		do 
		{
			printf("Input Next Action: ");
			scanf(" %c", &input);
		}while(input != 'X' && input != 'N'); // continuously asks user for input when it's invalid
		
		if (input == 'N') 
		{ // if user input is to go check the next product
			if (i < limit - 1) 
			{ // makes sure it doesnt go out of bounds
				i++;
			} 
			else 
			{
				printf("No more products to show!\n");
			}
		}
	}while(input != 'X'); // stops the do while when user input is X (Exit)
	//Ruiz's solution was used
}

/*
	SearchCategory allows the user to input a string category then searches all
		available items to see if any of the products matches the category.
	@param itemNo is the number of items in the list	
	@param items is the list of items with the itemType data type
*/
void 
SearchCategory(int itemNo, 
			   arrayitems items)
{
	itemType temp[MAXITEMS]; // temp array to store products
	int i, j = 0;
	String15 category;
	char cdump;
	
	printf("Input category to be searched: ");
	scanf("%c", &cdump);
	getString(category);
	
	for(i = 0; i < itemNo; i++) 
	{ // checks all items
		if(strcmp(items[i].itemCategory, category) == 0) // if inputted category is the same as item category
		{
			temp[j] = items[i]; // the item with the same category gets stored into a temp array
			j++; // number of items with the same category increments
		}
	}
	printf("Products of category '%s': \n", category);
	
	// if there are items to display, call showProductByPage
	if(j > 0)
		showProductByPage(temp, j);
	else
		printf("NO PRODUCTS TO SHOW!\n");
	//Ruiz's solution was used
}

/*
	SearchPName allows the user to input a string name then searches all
		available items to see if any of the products matches the name.
	@param itemNo is the number of items in the list	
	@param items is the list of items with the itemType data type
*/
void 
SearchPName(int itemNo, 
			arrayitems items)
{
	itemType temp[MAXITEMS]; // temp array to store products
	int i, j = 0, x;
	int count = 0;
	String20 name;
	char cdump;
	
	printf("Input name to be searched: ");
	scanf("%c", &cdump);
	getString(name);
	
	for(i = 0; i < itemNo; i++) 
	{ // checks all items
		if(strcmp(items[i].itemName, name) == 0) 
		{ // if the item name is exactly the same as the inputted name
			temp[j] = items[i];
			j++;
		}
		else
		{
			count = 0; // count for how many letters are the same in a row
			for(x = 0; x < strlen(items[i].itemName) && count != strlen(name); x++)
			{ // stops when x is larger than the amount of letters in itemName and also when count is equal to length of input name
				if(items[i].itemName[x] == name[count] + 32 || items[i].itemName[x] == name[count] - 32 || items[i].itemName[x] == name[count])//Possibly include caps and no caps
					count++;
				else
					count = 0; // if they're not the same letter, it gets reset back to 0
						
			}
			
			if(count == strlen(name))
			{ // if the count of similar letters in a row is equal to the length of the name
				temp[j] = items[i]; // item gets stored in temp and j increments
				j++;
			}
		}
	}
	printf("Products of name '%s': \n", name);
	
	// if there are items to display, call showProductByPage
	if(j > 0)
		showProductByPage(temp, j);
	else
		printf("NO PRODUCTS TO SHOW!\n");
	//Buencamino's solution was used
}

/*
	AddtoCart allows the user to input a productID and quantity then searches
		available items to see if the product is available, if it is, it then
		adds the product and quantity to the user's cart.
	@param person is a registered user
	@param itemNo is the number of items in the list	
	@param items is the list of items with the itemType data type
	@param cart is an itemType that holds the user's cart
	@param *itemsincart is the address that contains the number of items in the user's cart
*/
void 
AddtoCart(userType person, 
		  int itemNo, 
		  arrayitems items, 
		  itemType cart[], 
		  int *itemsincart)
{
	int inputproductID, inputquantity, i;
	int found = 0;
	int alreadyincart = 0;
	
	//if cart is already at max limit
	if(*itemsincart >= 10)
	{
		printf("Cart is already full!\n");
		printf("Please consider editing the cart or checking out first before adding more items.\n");
	}
	else
	{
		printf("Enter Product ID: ");
		scanf("%d", &inputproductID);
		printf("Enter Quantity: ");
		scanf("%d", &inputquantity);
		
		for(i = 0; i < *itemsincart; i++)
		{ // for checking if inputted item already exists in cart.
			if(cart[i].productID == inputproductID)
			{
				printf("Item already exists in cart!");
				alreadyincart = 1;
			}
		}
		
		// only runs when item is not found and item does not already exist in cart
		for(i = 0; i < itemNo && found == 0 && alreadyincart == 0; i++)
		{
			if(items[i].productID == inputproductID)
			{ // if inputproductID is found in the item array
				found = 1;
				printf("Product found! Checking quantity...\n");
				if(inputquantity <= items[i].itemQty)
				{ // if there is enough stock
					printf("Quantity available!\n");
					if(items[i].sellerID != person.userID)
					{ // if the seller isn't the same as the buyer
						cart[*itemsincart] = items[i];
						cart[*itemsincart].itemQty = inputquantity;
						(*itemsincart)++;
						printf("Item added to cart!");
					}
					else
					{ // if seller if the same as the buyer
						printf("Can't buy your own item!");
					}
				}
				else
				{ // if there is not enough stock
					printf("Quantity not available!\n");
				}
			}
		}
		if(found == 0 && alreadyincart == 0)
		{ // if product isn't found and item is not in cart already
			printf("Product not found!\n");
		}
	}
	//Ruiz's solution was used
}

/*
	showCart shows the user's cart.
	@param cart is an itemType that holds the user's cart
	@param itemsincart is the number of items in the user's cart
*/
void 
showCart(itemType cart[], 
		 int itemsincart)
{
	int i;
	
	printf("\nShowing Cart:");
	printf("\n|  Item No.  |  Product ID  |      Item Name      |    Category    |   Price   |  Quantity  |\n");
	
	for (i = 0; i < itemsincart; i++) 
	{
		printf("|%-12d|%-14d|%21s|%16s|%-11.2f|%-12d|\n", i + 1, cart[i].productID, cart[i].itemName, cart[i].itemCategory,
		cart[i].itemPrice, cart[i].itemQty);
	}
}

/*
	searchcart searches the user's cart to see if param key can be found.
	@param key is int input from the "RemoveAllItems" function
	@param cart is an itemType that holds the user's cart
	@param itemsincart is the number of items in the user's cart
	@return index of where the key is found
*/
int 
searchcart(int key, 
		   itemType cart[], 
		   int itemsincart)
{
	int i = 0;
	int index = -1; // sets index to -1 so that when key is not found in the system it returns -1
	
	while(i < itemsincart && index == -1)
		if(key == cart[i].sellerID)
			index = i; // if key is the same as the sellerID in cart[i], index is updated
		else
			i++;
			
	return index;
	//Buencamino's solution was used
}

/*
	copycart "deletes" an entry from the cart then moves the indexes.
	@param cart is an itemType that holds the user's cart
	@param itemsincart is the number of items in the user's cart
*/
void 
copycart(itemType cart[], 
		 int itemsincart)
{
	int i;
	
	for (i = 1; i < itemsincart; i++)
		cart[i - 1] = cart[i]; // cart[0] now has info of cart[1], cart[1] of cart[2], etc.
	//Buencamino's solution was used
}

/*
	RemoveAllItems takes in a user inputted sellerID then removes all items with the sellerID
		from the cart.
	@param cart is an itemType that holds the user's cart
	@param *itemsincart is the address that contains the number of items in the user's cart
*/
void 
RemoveAllItems(itemType cart[], 
			   int *itemsincart)
{
	int tempsellerID, index;
	int found = 0;
	
	printf("Enter Seller ID: ");
	scanf("%d", &tempsellerID);
	
	//go through the items inside the cart, if that item has the seller ID, call copy
	do
	{
		index = searchcart(tempsellerID, cart, *itemsincart);
		if(index != -1)
		{
			found = 1;
			copycart(&cart[index], *itemsincart - index);
			(*itemsincart)--;
		}
	}while(index != -1);
	
	if(found == 0)
		printf("SELLER NOT FOUND!\n");
	
	//Improved version of both solutions
}

/*
	RemoveSpecificItem takes in a user inputted productID then removes the item with the 
		productID from the cart.
	@param cart is an itemType that holds the user's cart
	@param *itemsincart is the address that contains the number of items in the user's cart
*/
void 
RemoveSpecificItem(itemType cart[], 
				   int *itemsincart)
{
	int tempprodID, i;
	int found = 0;
	
	printf("Enter Product ID: ");
	scanf("%d", &tempprodID);
	
	for(i = 0; i < *itemsincart; i++)
	{ // goes through all of the items in cart
		if(tempprodID == cart[i].productID)
		{ // if inputted ID is found in one of the items in cart, remove that item
			copycart(&cart[i], *itemsincart - i);
			(*itemsincart)--;
			found = 1;
		}
	}
	
	if(found == 0)
		printf("PRODUCT NOT FOUND!\n");
	//Improved version of both solutions
}

/*
	EditQuantity takes in a user inputted productID and quantity, it then checks to see if 
		the productID exists, if it does, it then checks if the current stock can handle the
		the  inputted quantity will be set, if yes, the quantity of the item in the cart will 
		be updated.
	@param cart is an itemType that holds the user's cart
	@param itemsincart is the number of items in the user's cart
	@param itemNo is the number of items in the list	
	@param items is the list of items with the itemType data type
*/
void 
EditQuantity(itemType cart[], 
			 int itemsincart, 
			 int itemNo, 
			 arrayitems items)
{
	int tempprodID, newQuantity;
	int i, j;
	int found = 0;
	
	printf("Enter Product ID: ");
	scanf("%d", &tempprodID);
	printf("Enter New Quantity: ");
	scanf("%d", &newQuantity);
	
	for(i = 0; i < itemsincart && found == 0; i++)
	{ // goes through all of the items in cart
		for(j = 0; j < itemNo; j++)
		{ // goes through all of the items in the system
			if(tempprodID == cart[i].productID && cart[i].productID == items[j].productID)
			{
				found = 1;
				if(newQuantity <= items[j].itemQty && newQuantity > 0)
				{ // makes sure that newQuantity isn't invalid (above 0 and also within stock)
					cart[i].itemQty = newQuantity;
					found = 1;
				}
				else if(newQuantity <= 0)
					printf("INVALID INPUT!\n");	// user inputted an invalid quantity number (negatives/0)
				else
					printf("NOT ENOUGH STOCK!\n"); // user inputted a value that is greater than stock
			}
		}
	}
	if(found == 0)
		printf("PRODUCT NOT FOUND!\n");
	//Buencamino's solution was used
}

/*
	EditCart presents the user with a menu and a choice of inputs which allows them to
		edit their carts.
	@param cart is an itemType that holds the user's cart
	@param *itemsincart is the address that contains the number of items in the user's cart
	@param itemNo is the number of items in the list	
	@param items is the list of items with the itemType data type
*/
void 
EditCart(itemType cart[], 
		 int *itemsincart, 
		 int itemNo, 
		 arrayitems items)
{
	int nChoice;
	
	do
	{
		showCart(cart, *itemsincart);
		
		printf("\n|----------------------------------------|\n");
		printf("|                Edit Cart               |\n");
		printf("|----------------------------------------|\n");
		printf("|                                        |\n");
		printf("|     1 - Remove all items from Seller   |\n");
		printf("|     2 - Remove Specific Item           |\n");
		printf("|     3 - Edit Quantity                  |\n");
		printf("|     4 - Finish Edit Cart               |\n");
		printf("|                                        |\n");
		printf("|----------------------------------------|\n\n");
		
		do 
		{
			printf("Insert Valid Input: ");
			scanf("%d", &nChoice);
		} while (nChoice > 4 || nChoice < 1); // continuously asks user for input if their input is out of bounds
		
		switch(nChoice)
		{
			case 1: RemoveAllItems(cart, itemsincart); break;
			case 2: RemoveSpecificItem(cart, itemsincart); break;
			case 3: EditQuantity(cart, *itemsincart, itemNo, items); break;
		}
	}while(nChoice != 4); // if user input is 4 (finish edit cart), do while loop ends
	//Buencamino's solution was used
}

/*
	CheckOutAll checks out all of the items the user has in their cart
	@param person is a registered user
	@param itemNo is the number of items in the list	
	@param items is the list of items with the itemType data type
	@param cart is an itemType that holds the user's cart
	@param *itemsincart is the address that contains the number of items in the user's cart
	@param receipt is the array of transactionTypes
	@param purchasedate contains the date inputted by the user
	@param *receiptAmount is the address that contains the current number of receipts
	@param otherpeople is the list of users
	@param numberofusers is the number of registered users in the list of users
*/
void 
CheckOutAll(userType person, 
			int itemNo, 
			arrayitems items, 
			itemType cart[], 
			int *itemsincart, 
			transactionType receipt[], 
			dateType purchasedate, 
			int *receiptAmount, 
			arrayusers otherpeople, 
			int numberofusers)
{
	int i, j, l = 0; //l is for indicating how many items are inside each receipt[*receiptAmount].
	int k, tempsellerID;
	FILE *fp;
	String20 sellerName;
	
	fp = fopen("Transactions.txt", "a");
	
	if(fp != NULL)
	{ // if file opening was successful
		do{
			for(i = 0; i < *itemsincart; i++)
			{ // goes through all items in cart
				l = 0;
				receipt[*receiptAmount].transactAmount = 0;
				tempsellerID = cart[i].sellerID;
				
				for(j = 0; j < *itemsincart; j++)
				{
					
					if(cart[j].sellerID == tempsellerID && l != 5)
					{ // if the seller of the item is the same and receipt isn't full yet (max 5)
						receipt[*receiptAmount].dates = purchasedate;
						receipt[*receiptAmount].items[l] = cart[j];
						receipt[*receiptAmount].buyerID = person.userID;
						receipt[*receiptAmount].sellerID = cart[j].sellerID;
						receipt[*receiptAmount].transactAmount += (cart[j].itemPrice * cart[j].itemQty);
	
						for(k = 0; k < numberofusers; k++)
						{ // goes through all the users to find the sellername
							if(cart[j].sellerID == otherpeople[k].userID)
								strcpy(sellerName, otherpeople[k].userName);
						}
						
						for(k = 0; k < itemNo; k++)
						{ // goes through all the items
							if(cart[j].productID == items[k].productID)
							{ // updates the quantity of the item in the item array
								items[k].itemQty -= receipt[*receiptAmount].items[l].itemQty;
							}
						}
						l++;
						copycart(&cart[j], *itemsincart - j); // removes the item from the cart
						(*itemsincart)--;
						j=-1; // makes j start from index 0 again just in case new index 0 contains an item from the same seller
					}
				}
				
				// if there's an item in the receipt
				if(l != 0)
				{ // shows receipt to buyer.
					printf("\nBUYER ID: %d\n", person.userID);
					printf("DATE: %d/%d/%d\n", purchasedate.month, purchasedate.day, purchasedate.year);
					printf("|  Quantity  |   Product ID   |      Item Name      |   Unit Price   |  Total Price  |\n");
					for(k = 0; k < l; k++)
					{
						printf("|%-12d|%-16d|%21s|%-16.2f|%-15.2f|\n", receipt[*receiptAmount].items[k].itemQty, receipt[*receiptAmount].items[k].productID,
						receipt[*receiptAmount].items[k].itemName, receipt[*receiptAmount].items[k].itemPrice, receipt[*receiptAmount].items[k].itemPrice * receipt[*receiptAmount].items[k].itemQty);
					}
					printf("SELLER ID: %d\n", receipt[*receiptAmount].sellerID);
					printf("SELLER NAME: %s\n", sellerName);
					printf("TOTAL TRANSACTION: %.2f\n", receipt[*receiptAmount].transactAmount);
					printf("\n");
					
					// adds the info to Transactions.txt
					fprintf(fp, "%d\n", person.userID);
					fprintf(fp, "%d %d %d\n", purchasedate.month, purchasedate.day, purchasedate.year);
					for(k = 0; k < l; k++)
					{
						fprintf(fp, "%s\n", receipt[*receiptAmount].items[k].itemName);
						fprintf(fp, "%d %d %.2f\n", receipt[*receiptAmount].items[k].itemQty, receipt[*receiptAmount].items[k].productID,
						receipt[*receiptAmount].items[k].itemPrice);
					}
					fprintf(fp, "=\n");
					fprintf(fp, "%d\n", receipt[*receiptAmount].sellerID);
					fprintf(fp, "%s\n", sellerName);
					fprintf(fp, "%.2f\n", receipt[*receiptAmount].transactAmount);
					fprintf(fp, "-\n");
					(*receiptAmount)++; // receipt amount increments
				}
			}
		}while(*itemsincart > 0); // do this until there are no more items in the cart
	}	
	fclose(fp);
	//Ruiz's solution was used
}

/*
	CheckOutSeller allows the user to input a sellerID then checks out all of the items that
		has the inputted sellerID
	@param person is a registered user
	@param itemNo is the number of items in the list	
	@param items is the list of items with the itemType data type
	@param cart is an itemType that holds the user's cart
	@param *itemsincart is the address that contains the number of items in the user's cart
	@param receipt is the array of transactionTypes
	@param purchasedate contains the date inputted by the user
	@param *receiptAmount is the address that contains the current number of receipts
	@param otherpeople is the list of users
	@param numberofusers is the number of registered users in the list of users
*/
void 
CheckOutSeller(userType person, 
			   int itemNo, 
			   arrayitems items, 
			   itemType cart[], 
			   int *itemsincart, 
			   transactionType receipt[], 
			   dateType purchasedate, 
			   int *receiptAmount, 
			   arrayusers otherpeople, 
			   int numberofusers)
{
	FILE *fp;
	int i, j, x, l = 0;
	//l is for item inside each receipt[*receiptAmount].
	int tempsellerID;
	String20 sellerName;
	
	printf("Enter Seller ID: ");
	scanf("%d", &tempsellerID);
	
	fp = fopen("Transactions.txt", "a");
	
	if(fp != NULL)
	{ // if file opening was successful
		for(i = 0; i < *itemsincart; i++)
		{ // goes through all items in cart
			l = 0;
			receipt[*receiptAmount].transactAmount = 0;
			
			for(j = 0; j < *itemsincart; j++)
			{
				if(cart[j].sellerID == tempsellerID && l != 5)
				{ // if the seller of the item is the same and receipt isn't full yet (max 5)
					receipt[*receiptAmount].dates = purchasedate;
					receipt[*receiptAmount].items[l] = cart[j];
					receipt[*receiptAmount].buyerID = person.userID;
					receipt[*receiptAmount].sellerID = cart[j].sellerID;
					receipt[*receiptAmount].transactAmount += (cart[j].itemPrice * cart[j].itemQty);
					for(x = 0; x < numberofusers; x++)
					{ // goes through all the users to find the sellername
						if(cart[j].sellerID == otherpeople[x].userID)
							strcpy(sellerName, otherpeople[x].userName);
					}
					
					for(x = 0; x < itemNo; x++)
					{ // goes through all the items
						if(cart[j].productID == items[x].productID)
						{ // updates the quantity of the item in the item array
							items[x].itemQty -= receipt[*receiptAmount].items[l].itemQty;
						}
					}
					
					l++;
					copycart(&cart[j], *itemsincart - j); // removes the item from the cart
					(*itemsincart)--;
					j=-1; // makes j start from index 0 again just in case new index 0 contains an item from the same seller
				}
			}
			
			// if there's an item in the receipt
			if(l != 0)
			{//shows receipt to buyer.
				printf("\nBUYER ID: %d\n", person.userID);
				printf("DATE: %d/%d/%d\n", purchasedate.month, purchasedate.day, purchasedate.year);
				printf("|  Quantity  |   Product ID   |      Item Name      |   Unit Price   |  Total Price  |\n");
				for(x = 0; x < l; x++)
				{
					printf("|%-12d|%-16d|%21s|%-16.2f|%-15.2f|\n", receipt[*receiptAmount].items[x].itemQty, receipt[*receiptAmount].items[x].productID,
					receipt[*receiptAmount].items[x].itemName, receipt[*receiptAmount].items[x].itemPrice, receipt[*receiptAmount].items[x].itemPrice * receipt[*receiptAmount].items[x].itemQty);
				}
				printf("SELLER ID: %d\n", receipt[*receiptAmount].sellerID);
				printf("SELLER NAME: %s\n", sellerName);
				printf("TOTAL TRANSACTION: %.2f\n", receipt[*receiptAmount].transactAmount);
				printf("\n");
				
				// adds the info to Transactions.txt
				fprintf(fp, "%d\n", person.userID);
				fprintf(fp, "%d %d %d\n", purchasedate.month, purchasedate.day, purchasedate.year);
				for(x = 0; x < l; x++)
				{
					fprintf(fp, "%s\n", receipt[*receiptAmount].items[x].itemName);
					fprintf(fp, "%d %d %.2f\n", receipt[*receiptAmount].items[x].itemQty, receipt[*receiptAmount].items[x].productID,
					receipt[*receiptAmount].items[x].itemPrice);
				}
				fprintf(fp, "=\n");
				fprintf(fp, "%d\n", receipt[*receiptAmount].sellerID);
				fprintf(fp, "%s\n", sellerName);
				fprintf(fp, "%.2f\n", receipt[*receiptAmount].transactAmount);
				fprintf(fp, "-\n");
				(*receiptAmount)++; // receipt amount increments
			}
		}
	}
	fclose(fp);
	//Ruiz's solution was used
}

/*
	CheckOutItem allows the user to input a productID then checks out the item that has the
		same productID
	@param person is a registered user
	@param itemNo is the number of items in the list	
	@param items is the list of items with the itemType data type
	@param cart is an itemType that holds the user's cart
	@param *itemsincart is the address that contains the number of items in the user's cart
	@param receipt is the array of transactionTypes
	@param purchasedate contains the date inputted by the user
	@param *receiptAmount is the address that contains the current number of receipts
	@param otherpeople is the list of users
	@param numberofusers is the number of registered users in the list of users
*/
void 
CheckOutItem(userType person, 
			 int itemNo, 
			 arrayitems items, 
			 itemType cart[], 
			 int *itemsincart, 
			 transactionType receipt[], 
			 dateType purchasedate, 
			 int *receiptAmount, 
			 arrayusers otherpeople, 
			 int numberofusers)
{
	FILE *fp;
	int tempprodID, i, j, found = 0;
	String20 sellerName;
	
	showCart(cart, *itemsincart);
	printf("Enter Product ID: ");
	scanf("%d", &tempprodID);
	
	for(i = 0; i < *itemsincart; i++)
	{ // goes through all items in cart
		if(tempprodID == cart[i].productID)
		{ // if inputted productID has been found in the cart
			receipt[*receiptAmount].dates = purchasedate;
			receipt[*receiptAmount].buyerID = person.userID;
			receipt[*receiptAmount].sellerID = cart[i].sellerID;
			receipt[*receiptAmount].transactAmount = cart[i].itemPrice * cart[i].itemQty;
			receipt[*receiptAmount].items[0] = cart[i];
			for(j = 0; j < numberofusers; j++)
			{ // goes through all the users to find the sellername
				if(cart[i].sellerID == otherpeople[j].userID)
					strcpy(sellerName, otherpeople[j].userName);	
			}
			
			for(j = 0; j < itemNo; j++)
			{ // goes through all the items
				if(cart[i].productID == items[j].productID)
				{ // updates the quantity of the item in the item array
					items[j].itemQty -= receipt[*receiptAmount].items[0].itemQty;
				}
			}
			
			//shows receipt to buyer.
			printf("\nBUYER ID: %d\n", person.userID);
			printf("DATE: %d/%d/%d\n", purchasedate.month, purchasedate.day, purchasedate.year);
			printf("|  Quantity  |   Product ID   |      Item Name      |   Unit Price   |  Total Price  |\n");
			printf("|%-12d|%-16d|%21s|%-16.2f|%-15.2f|\n", receipt[*receiptAmount].items[0].itemQty, receipt[*receiptAmount].items[0].productID,
			receipt[*receiptAmount].items[0].itemName, receipt[*receiptAmount].items[0].itemPrice, receipt[*receiptAmount].items[0].itemPrice * receipt[*receiptAmount].items[0].itemQty);
			printf("SELLER ID: %d\n", receipt[*receiptAmount].sellerID);
			printf("SELLER NAME: %s\n", sellerName);
			printf("TOTAL TRANSACTION: %.2f\n", receipt[*receiptAmount].transactAmount);
			printf("\n");
			
			// adds the info to Transactions.txt
			fp = fopen("Transactions.txt", "a");
			if(fp != NULL)
			{ // if file opening was successful
				fprintf(fp, "%d\n", person.userID);
				fprintf(fp, "%d %d %d\n", purchasedate.month, purchasedate.day, purchasedate.year);
				fprintf(fp, "%s\n", receipt[*receiptAmount].items[0].itemName);
				fprintf(fp, "%d %d %.2f\n", receipt[*receiptAmount].items[0].itemQty, receipt[*receiptAmount].items[0].productID,
				receipt[*receiptAmount].items[0].itemPrice);
				fprintf(fp, "=\n");
				fprintf(fp, "%d\n", receipt[*receiptAmount].sellerID);
				fprintf(fp, "%s\n", sellerName);
				fprintf(fp, "%.2f\n", receipt[*receiptAmount].transactAmount);
				fprintf(fp, "-\n");
			}
			fclose(fp);
		
			found = 1;
			(*receiptAmount)++; // receipt amount increments
			copycart(&cart[i], *itemsincart - i); // removes the item from the cart
			(*itemsincart)--;
		}	
	}
	if(found == 0)
		printf("PRODUCT NOT FOUND!\n");
	//Buencamino's solution was used
}

/*
	CheckOutMenu checks to see cart item availability first then presents the user with a 
		menu and a choice of inputs which allows them to check out items in their cart.
	@param person is a registered user
	@param itemNo is the number of items in the list	
	@param items is the list of items with the itemType data type
	@param cart is an itemType that holds the user's cart
	@param *itemsincart is the address that contains the number of items in the user's cart
	@param otherpeople is the list of users
	@param numberofusers is the number of registered users in the list of users
*/
void 
CheckOutMenu(userType person, 
			 int itemNo, 
			 arrayitems items, 
			 itemType cart[], 
			 int *itemsincart, 
			 arrayusers otherpeople, 
			 int numberofusers)
{
	int nChoice;
	transactionType receipt[10]; // just in case all items in cart come from different sellers.
	dateType purchasedate;
	int receiptAmount = 0;
	int i, j;
	int found = 0;
	
	for(i = 0 ; i < *itemsincart; i++)
	{ // goes through all items in cart
		for(j = 0; j < itemNo; j++)
		{ // goes through all items in items array
			if(cart[i].productID == items[j].productID)
			{
				if(cart[i].itemQty > items[j].itemQty || cart[i].itemPrice != items[j].itemPrice)
				{ // if the item quantity in cart is greater than in stock or if the item price in cart is not the same as in listing (aka price has been updated).
					if(cart[i].itemQty > items[j].itemQty)
						cart[i].itemQty = items[j].itemQty;
					// if cart amount is greater than current stock, update cart amount to current stock.
					
					cart[i].itemPrice = items[j].itemPrice; // update cart to new price.
					printf("SELLER HAS UPDATED ITEM '%s''s PRICE AND/OR QUANTITY\n", items[j].itemName);
					printf("NEW PRICE: %.2f\nNEW QUANTITY: %d\n", items[j].itemPrice, items[j].itemQty);
					found = 1;
				}
			}
		}
	}
	if(found)
		printf("You can still edit your cart if you want to make changes!\n");
	
	printf("Please input date [MM/DD/YYYY]: ");
	scanf("%d %d %d", &purchasedate.month, &purchasedate.day, &purchasedate.year);
	
	sortproductID(cart, *itemsincart);
	do
	{
		printf("\n|----------------------------------|\n");
		printf("|          Check Out Menu          |\n");
		printf("|----------------------------------|\n");
		printf("|                                  |\n");
		printf("|     1 - All                      |\n");
		printf("|     2 - By a Specific Seller     |\n");
		printf("|     3 - Specific Item            |\n");
		printf("|     4 - Exit Checkout            |\n");
		printf("|                                  |\n");
		printf("|----------------------------------|\n\n");
		
		do 
		{
			printf("Insert Valid Input: ");
			scanf("%d", &nChoice);
		} while (nChoice > 4 || nChoice < 1); // continuously asks user for input if their input is out of bounds
		
		switch (nChoice) 
		{
			case 1: CheckOutAll(person, itemNo, items, cart, itemsincart, receipt, purchasedate, &receiptAmount, otherpeople, numberofusers); break;
			case 2: CheckOutSeller(person, itemNo, items, cart, itemsincart, receipt, purchasedate, &receiptAmount, otherpeople, numberofusers); break;
			case 3: CheckOutItem(person, itemNo, items, cart, itemsincart, receipt, purchasedate, &receiptAmount, otherpeople, numberofusers); break;
		}
	}while(nChoice != 4); // if user input is 4 (Exit Checkout), do while loop ends
	//Ruiz's solution was used
}

void
ShowSpecificSeller(int sellerIDinputfor2, 
				   arrayusers otherpeople, 
				   int numberofusers, 
				   arrayitems items, 
				   int itemNo)
{
	int i;
	int sellerIDfoundfor2 = 0;
	
	for(i = 0; i < numberofusers; i++)
	{ // goes through all the users
		if(sellerIDinputfor2 == otherpeople[i].userID)
		{ // if inputted userID is found in the list of users, show the products of that user
			showProducts(items, itemNo, otherpeople[i]);
			sellerIDfoundfor2 = 1;
		}
	}
	if(sellerIDfoundfor2 == 0)
	{ // if inputted userID isn't found in the list of users
		printf("UserID not found!");
	}
	//Improved version of both solutions
}

/*
	BuyMenu presents the user with a menu and a choice of inputs which allows them to
		look at products, add to cart, and check them out.
	@param *person is the logged in seller
	@param items is the list of items with the itemType data type
	@param itemNo is the number of items in the list	
	@param numberofusers is the number of registered users in the list of users
	@param otherpeople is the list of users
	@param cart is an itemType that holds the user's cart
	@param *itemsincart is the address that contains the number of items in the user's cart
*/
void 
BuyMenu(userType *person, 
		arrayitems items, 
		int *itemNo, 
		int numberofusers,
		userType otherpeople[], 
		itemType cart[], 
		int *itemsincart) 
{
	int nChoice, i = 0;
	char choicefor1;
	int sellerIDinputfor2;
	
	do
	{
		printf("\n|----------------------------------------|\n");
		printf("|                Buy Menu                |\n");
		printf("|----------------------------------------|\n");
		printf("|                                        |\n");
		printf("|     1 - View all Products              |\n");
		printf("|     2 - Specific Seller's Products     |\n");
		printf("|     3 - Search Products by Category    |\n");
		printf("|     4 - Search Products by Name        |\n");
		printf("|     5 - Add to Cart                    |\n");
		printf("|     6 - Edit Cart                      |\n");
		printf("|     7 - Check Out Menu                 |\n");
		printf("|     8 - Exit Buy Menu                  |\n");
		printf("|                                        |\n");
		printf("|----------------------------------------|\n\n");
		
		sortproductID(items, *itemNo);
		do 
		{
			printf("Insert Valid Input: ");
			scanf("%d", &nChoice);
		} while (nChoice > 8 || nChoice < 1); // continuously asks user for input if their input is out of bounds
		
		switch (nChoice) 
		{
			case 1: i = 0;
					sortUserID(otherpeople, numberofusers);
					do 
					{
						printf("\nProducts of user #%d", otherpeople[i].userID);
						showProducts(items, *itemNo, otherpeople[i]);
						
						printf("\nActions\n");
						printf("N - Next Person\n");
						printf("X - Exit\n");
						
						do 
						{
							printf("Input Next Action: ");
							scanf(" %c", &choicefor1);
						} while (choicefor1 != 'X' && choicefor1 != 'N'); // continuously asks user for input when it's invalid
							
						if (choicefor1 == 'N') 
						{ // if user input is to go check the next product
							if (i < numberofusers-1) 
							{ // makes sure it doesnt go out of bounds
								i++;
							} 
							else 
							{
								printf("No more people to show!\n");
							}
						}
					}while(choicefor1 != 'X'); // stops the do while when user input is X (Exit)
					break;
			
			case 2: printf("Input specific seller's ID: ");
					scanf("%d", &sellerIDinputfor2);
					ShowSpecificSeller(sellerIDinputfor2, otherpeople, numberofusers, items, *itemNo);
					break;
			
			case 3: SearchCategory(*itemNo, items); 
					break;
			case 4: SearchPName(*itemNo, items); 
					break;
			case 5: AddtoCart(*person, *itemNo, items, cart, itemsincart);
					break;
			case 6: EditCart(cart, itemsincart, *itemNo, items); 
					break;
			case 7: CheckOutMenu(*person, *itemNo, items, cart, itemsincart, otherpeople, numberofusers); 
					break;
			case 8: break;
		}
	}while(nChoice != 8); // if user input is 8 (Exit Buy Menu), do while loop ends
	//Improved version of both solutions
}
