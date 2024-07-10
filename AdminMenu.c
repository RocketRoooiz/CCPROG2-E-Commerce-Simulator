#include "structs.h"

/*
	showUsers displays the list of all registered users in the program
	in a table format
	@param users is the list of users with userType data type
	@param userNo number of users in the list
*/

void 
showUsers(arrayusers users, 
		  int userNo) 
{
	int i;
	printf("\nShowing Users [sorted by user ID]:");
	printf("\n|   userID   |  Password  |         Name         |            Address            | Phone Number |\n");
	
	for (i = 0; i < userNo; i++)
	{
		printf("|%-12d|%12s|%22s|%31s|%-14d|\n", users[i].userID, users[i].userPassword, users[i].userName,
												 users[i].userAddress, users[i].userContactno);
	}
}

/*
	showAllSellers displays all the users that are selling at least one
	item in a table format
	@param users is the list of users with userType data type
	@param userNo number of users in the list
	@param items is list of items with itemType data type
	@param itemNo is the number of items in the list
*/

void 
showAllSellers(arrayusers users, 
			   int userNo, 
			   arrayitems items, 
			   int itemNo)
{
	int i;
	
	printf("\nShowing Sellers [sorted by user ID]:");
	printf("\n|   userID   |  Password  |         Name         |            Address            | Phone Number | # of Items for Sale |\n");
	
	for (i = 0; i < userNo; i++)
	{ // if user has a product, it prints the user in table format
		if (count(users[i], items, itemNo) > 0)
			printf("|%-12d|%12s|%22s|%31s|%-14d|%-21d|\n", users[i].userID, users[i].userPassword, users[i].userName,
														   users[i].userAddress, users[i].userContactno, count(users[i], items, itemNo));
	}
	//Buencamino's solution was used
}

/*
	checkWithin checks if startdate is less than transaction date, 
		and if transaction date is less than end date
	@param date1 is the date that should be smaller than date2 to be considered within
	@param date2 is the date that should be bigger than date1 to be considered within
	@return 1 if date1 is smaller than date 2, 0 if it isn't
*/
int 
checkWithin(dateType date1, 
			dateType date2)
{
	int isWithin = 0;
	
	if(date1.year < date2.year)
		isWithin = 1; // if within years
	else if(date1.year == date2.year && date1.month < date2.month)
		isWithin = 1; // if same years, check within month
	else if(date1.year == date2.year && date1.month == date2.month && date1.day < date2.day)
		isWithin = 1; // if same years and month, check within day
	else if(date1.year == date2.year && date1.month == date2.month && date1.day == date2.day)
		isWithin = 1; // if transaction occurs on the day
	
	return isWithin;
}

/*
	checkDateRange calls checkWithin and sees if the date of the transaction is within the start 
		and end date inputted by the user
	@param transactions is the list of transactions with transactionType data type
	@param WithinDate is the true or false integer value that changes based on the condition
	@param i is the index of the transaction being checked
	@param startDate is the lower bound of the range wherein the date is valid
	@param endDate is the upper bound of the range wherein the date is valid
	@return 1 if the value 1 if date is within range, 0 if not
*/
int 
checkDateRange(transactionType transactions[],
			   int WithinDate,
			   int i,
			   dateType startDate,
			   dateType endDate)
{
	WithinDate = 0;
	
	// if transaction date is greater than/equal to startDate and less than/equal to end date, it's within the 2 dates
	if(checkWithin(startDate, transactions[i].dates) == 1 && checkWithin(transactions[i].dates, endDate) == 1)
		WithinDate = 1;
	else
		WithinDate = 0;
	
	return WithinDate;
	//Improved version of both solutions
}

/*
	getTransaction scans the contents of the Transactions.txt file 
	and stores the contents in the list of transactions
	@param transactions is the list of transactions with transactionType data type
	@param transNo is the address where the number of transactions in the list are placed
	@param itemNo is the address where the number of items in the a transaction are placed
	@param string is the array of characters that takes in the seller's name
*/
void 
getTransaction(transactionType transactions[],
			   int *transNo,
			   int *itemNo,
			   String20 string)
{	
	/*scan the inputs until the - character, if scans a dash line then increment number of transactions*/
	FILE *fp;
	int i;
	int valid;
	char ch;
	char cdump;
	
	fp = fopen("Transactions.txt", "r");
	
	// if file opening was successful
	if(fp != NULL)
	{
		do
		{
			*itemNo = 0;
			valid = fscanf(fp, "%d", &transactions[*transNo].buyerID);
			// if a buyerID got successfully scanned, scans for the rest
			if(valid == 1)
			{	
				fscanf(fp, "%d %d %d", &transactions[*transNo].dates.month, &transactions[*transNo].dates.day, &transactions[*transNo].dates.year);
				fscanf(fp, "%c", &cdump); // takes in /n?
				
				do
				{
					i = 0; // scans item name
					do
					{
						fscanf(fp, "%c", &ch);
						
						if (ch != '\n') 
						{
							transactions[*transNo].items[*itemNo].itemName[i] = ch;
							i++;
						}
					}while(ch != '\n');
					transactions[*transNo].items[*itemNo].itemName[i] = '\0';
					
					fscanf(fp, "%d %d %f", &transactions[*transNo].items[*itemNo].itemQty, &transactions[*transNo].items[*itemNo].productID, &transactions[*transNo].items[*itemNo].itemPrice);
					fscanf(fp, "%c", &cdump);
					fscanf(fp, "%c", &cdump);
					
					if(cdump != '=')
						fseek(fp, -1, SEEK_CUR);
					
					(*itemNo)++;
				
				// '=' is the marker before showing seller details and transactAmount, if it's not '=', it means there's still another item in the receipt.
				}while(cdump != '='); 
				
				fscanf(fp, "%d", &transactions[*transNo].sellerID);
				fscanf(fp, "%c", &cdump);
				
				i = 0; // scans seller name
				do
				{
					fscanf(fp, "%c", &ch);
					
					if (ch != '\n') 
					{
						string[i] = ch;
						i++;
					}
				}while(ch != '\n');
				string[i] = '\0';
				
				fscanf(fp, "%f", &transactions[*transNo].transactAmount);

				(*transNo)++;
				valid = fscanf(fp, "%c", &cdump); // takes in the '-', signifying the end of a receipt
			}
		}while (valid != -1);
		fclose(fp);
	}
	else printf("Cannot open file.\n");
	//Improved version of both solutions
}

/*
	ShowTotalSales displays the total amount of transactions made within a
	given date range scanned from a Transactions.txt text file
*/
void 
ShowTotalSales()
{
	transactionType transactions[MAXITEMS];
	int transNo = 0;
	int itemNo = 0;
	String20 string;
	dateType startDate;
	dateType endDate;
	float totalTransaction = 0.00;
	int i;
	int WithinDate = 0;
	
	printf("Enter Starting Date [MM/DD/YYYY]: ");
	scanf("%d %d %d", &startDate.month, &startDate.day, &startDate.year);
	printf("Enter End Date [MM/DD/YYYY]: ");
	scanf("%d %d %d", &endDate.month, &endDate.day, &endDate.year);

	getTransaction(transactions, &transNo, &itemNo, string); // scans the data from the Transactions.txt file
	
	for(i = 0; i < transNo; i++)
	{ // checks all transactions
		WithinDate = checkDateRange(transactions, WithinDate, i, startDate, endDate);
		// if the transaction day is within the given startDate and endDate, add the transactAmount to the totalAmount
		if(WithinDate)
			totalTransaction += transactions[i].transactAmount;
	}

	printf("TOTAL TRANSACTION AMOUNT FROM %d/%d/%d to %d/%d/%d is %.2f", startDate.month, startDate.day, startDate.year, endDate.month, endDate.day, endDate.year, totalTransaction);
	//Buencamino's solution was used
}

/*
	printSeller is the helper function that allows the display
	of all sellers and their transactionAmount
	@param users is the list of users with userType data type
	@param userNo number of users in the list
	@param items is list of items with itemType data type
	@param itemNo is the number of items in the list
	@param totalAmount is the list of the total amount of sales made by a specific seller
*/
void 
printSeller(arrayusers users,
			int userNo, 
			arrayitems items, 
			int itemNo, 
			float totalAmount[])
{
	int i;
	printf("|   Seller ID   |     Seller Name     |   Total Sales   |\n");
	for (i = 0; i < userNo; i++)
	{	// only shows users that has a product
		if (count(users[i], items, itemNo) > 0)
			printf("|%-15d|%21s|%-17.2f|\n", users[i].userID, users[i].userName, totalAmount[i]);
	}
}

/*
	ShowSellersSales displays all the users that are selling at least one
	item in a table format as well as their total sales within a date range
	@param users is the list of users with userType data type
	@param userNo number of users in the list
	@param items is the list of items with the itemType data type
	@param itemNum is the number of items in the list
*/
void 
ShowSellersSales(arrayusers users,
				 int userNo, 
				 arrayitems items, 
				 int itemNum)
{
	transactionType transactions[MAXITEMS];
	int transNo = 0;
	int itemNo = 0;
	String20 string;
	dateType startDate;
	dateType endDate;
	int WithinDate = 0;
	float totalAmount[userNo];
	int i, j;
	
	printf("Enter Starting Date [MM/DD/YYYY]: ");
	scanf("%d %d %d", &startDate.month, &startDate.day, &startDate.year);
	printf("Enter End Date [MM/DD/YYYY]: ");
	scanf("%d %d %d", &endDate.month, &endDate.day, &endDate.year);
	
	getTransaction(transactions, &transNo, &itemNo, string); // scans the data from the Transactions.txt file
	
	// set it all to 0.00, just in case
	for(i = 0; i < userNo; i++)
		totalAmount[i] = 0.00;
	
	for(i = 0; i < transNo; i++)
	{ // checks all transactions
		WithinDate = checkDateRange(transactions, WithinDate, i, startDate, endDate);
		
		if(WithinDate == 1)
		{ // if the transaction is within the given startDate and endDate
			for(j = 0; j < userNo; j++)
			{ // checks all users
				if(users[j].userID == transactions[i].sellerID)
				{ // if the user is the seller who made the transaction, add the transactAmount to their totalAmount
					totalAmount[j] += transactions[i].transactAmount;
				}
			}
		}
	}
	
	printSeller(users, userNo, items, itemNum, totalAmount);
	//Improved version of both solutions
}

/*
	printBuyer is the helper function that allows ShowShopaholics
	to displayer the users
	@param users is the list of users with userType data type
	@param userNo number of users in the list
	@param totalAmount is the list of the total amount of sales made by a specific seller
*/
void 
printBuyer(arrayusers users, 
		   int userNo, 
		   float totalAmount[])
{
	int i;
	printf("|   Buyer ID   |     Buyer Name     |   Total Bought  |\n");
	for (i = 0; i < userNo; i++)
	{ // only shows the users that actually bought something
		if(totalAmount[i] > 0.0)
			printf("|%-14d|%20s|%-17.2f|\n", users[i].userID, users[i].userName, totalAmount[i]);
	}
}

/*
	ShowShopaholics displays all the users in a table format as well
	as their total amount spent within a given date range
	@param users is the list of users with userType data type
	@param userNo number of users in the list
	@param items is the list of items with the itemType data type
	@param itemNum is the number of items in the list
*/
void 
ShowShopaholics(arrayusers users, 
				int userNo, 
				arrayitems items, 
				int itemNum)
{
	transactionType transactions[MAXITEMS];
	int transNo = 0;
	int itemNo = 0;
	String20 string;
	dateType startDate;
	dateType endDate;
	float totalAmount[userNo];
	int i, j;
	int WithinDate = 0;
	
	printf("Enter Starting Date [MM/DD/YYYY]: ");
	scanf("%d %d %d", &startDate.month, &startDate.day, &startDate.year);
	printf("Enter End Date [MM/DD/YYYY]: ");
	scanf("%d %d %d", &endDate.month, &endDate.day, &endDate.year);
	
	getTransaction(transactions, &transNo, &itemNo, string); // scans the data from the Transactions.txt file
	
	for(i = 0; i < userNo; i++)
		totalAmount[i] = 0.00;
	
	for(i = 0; i < transNo; i++)
	{ // checks all transactions
		WithinDate = checkDateRange(transactions, WithinDate, i, startDate, endDate);
		
		if(WithinDate == 1)
		{ // if the transaction is within the given startDate and endDate
			for(j = 0; j < userNo; j++)
			{ // checks all users
				if(users[j].userID == transactions[i].buyerID)
				{ // if the user is the buyer who made the transaction, add the transactAmount to their totalAmount
					totalAmount[j] += transactions[i].transactAmount;
				}
			}
		}
	}
	printBuyer(users, userNo, totalAmount);
	//Ruiz's solution was used
}

/*
	AdminMenu allows the user to choose from a set of options
	that allows the display of all users and sellers, sales within
	a given duration, as well as all shoppers
	@param users is the list of users with userType data type
	@param userNo number of users in the list
	@param items is list of items with itemType data type
	@param itemNo is the number of items in the list
*/
void 
AdminMenu(arrayusers users, 
		  int *numberofusers, 
		  arrayitems items, 
		  int itemNo)
{
	int nUserChoice = 0;
	String10 inputPassword;

	printf("Enter your password: ");
	scanf("%s", inputPassword);
	
	if(strcmp(inputPassword, "H3LLo?") == 0) 
	{
		printf("\n             Successful Login!\n");
		
		do
		{
			printf("\n|------------------------------------------------|\n");
			printf("|                  Admin Menu                    |\n");
			printf("|------------------------------------------------|\n");
			printf("|                                                |\n");
			printf("|      1 - Show All Users      	                 |\n");
			printf("|      2 - Show All Sellers                      |\n");
			printf("|      3 - Show Total Sales Given Duration       |\n");
			printf("|      4 - Show Sellers Sales                    |\n");
			printf("|      5 - Show Shopaholics                      |\n");
			printf("|      6 - Exit                                  |\n");
			printf("|                                                |\n");
			printf("|------------------------------------------------|\n\n");
			
			do
			{
				printf("Insert Valid Input: ");
				scanf("%d", &nUserChoice);
			}while (nUserChoice > 6 || nUserChoice < 1); // continuously asks user for input if their input is out of bounds
			
			sortUserID(users, *numberofusers);
			
			switch (nUserChoice)
			{
				case 1: showUsers(users, *numberofusers); break;
				case 2: showAllSellers(users, *numberofusers, items, itemNo); break;
				case 3: ShowTotalSales(); break;
				case 4:	ShowSellersSales(users, *numberofusers, items, itemNo); break;
				case 5: ShowShopaholics(users, *numberofusers, items, itemNo); break;
			}
		}while (nUserChoice != 6); // if user input is 6 (exit), do while loop ends
	}
	else printf("Wrong Password!\n"); // if inputted password is incorrect
	//Improved version of both solutions
}
