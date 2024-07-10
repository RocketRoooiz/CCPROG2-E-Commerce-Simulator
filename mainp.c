/***********************************************************************************************************
This is to certify that this project is our own work, based on our personal efforts in studying and applying
the concepts learned. We have constructed the functions and their respective algorithms and corresponding 
code by ourselves. The program was run, tested, and debugged by our own efforts. We further certify that we 
have not copied in part or whole or otherwise plagiarized the work of other students and/or persons.

														  Buencamino, Prince Bendrik C., DLSU ID# 12205478
																 Ruiz, Chester Bryan C., DLSU ID# 12290190
***********************************************************************************************************/

#include "BaseMenu.c"
#include "structs.h"
#include "UnivFunc.c"

//gcc -Wall mainp.c -o run.exe

int main() 
{
	int numberofusers = 0;
	arrayusers users;
	int itemNo = 0;
	arrayitems items;
	
	LoadUsers(users, &numberofusers);
	LoadItems(items, &itemNo);
	MainMenu(users, &numberofusers, items, &itemNo);
	return 0;
}
