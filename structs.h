#pragma once
#include <stdio.h>
#include <string.h>

#define MAXUSERS 100
#define MAXITEMS 2000

typedef char String10[11]; // for password
typedef char String15[16]; // for item category
typedef char String20[21]; // for user name, item name
typedef char String30[31]; // for user address, item desc.

struct itemTag {
  int productID;
  String20 itemName;
  String15 itemCategory;
  String30 itemDesc;
  int itemQty;
  float itemPrice;
  int sellerID;
};

typedef struct itemTag itemType;
typedef itemType arrayitems[MAXITEMS];

struct userTag {
  int userID;
  String10 userPassword;
  String30 userAddress;
  int userContactno;
  String20 userName;
};

typedef struct userTag userType;
typedef userType arrayusers[MAXUSERS];

struct dateTag {
  int month, day, year;
};

typedef struct dateTag dateType;

struct transactionTag {
  dateType dates;
  itemType items[5]; // each receipt can only have at most 5 items from the same seller
  int buyerID;
  int sellerID;
  float transactAmount;
};

typedef struct transactionTag transactionType;

void LoadUsers(userType users[], int *numberofusers);
void LoadItems(itemType items[], int *itemNo);
void getString(char *iteminfo);
void swap(itemType *a, itemType *b);
void sortproductID(itemType items[], int itemNo);
int count(userType person, itemType items[], int itemNo);
void sortUserID(userType otherpeople[], int numberofusers);
void SaveUsers(userType users[], int numberofusers);
void SaveItems(itemType items[], int itemNo);
