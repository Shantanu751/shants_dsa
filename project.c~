
/*****************************************************************************
 * Copyright (C) Shantanu R Pande shantanupande751@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
 
 /* This file contains main function
  * All functions are called in this function*/
#include <stdio.h>
#include <stdlib.h>
#include "h.h"
main() {
	system("clear");
	char username[32], pass[32];
	int choice;
	printf("\nAt any point enter \"0\" to go back to previous state\n");
	while(1) {
		printf("\n1. Buyer\n2. Seller\n3. Administrator\n");
		scanf("%d", &choice);
		system("clear");
		switch(choice) {
			case 1: //Buyer
				printf("Enter username and pass:");
				scanf("%s %s", username, pass);
				if(login(choice, username, pass) )
					buyer(username);
				getchar();
				system("clear");
				continue;
			case 2:	//Seller
				printf("Enter username and pass:");
				scanf("%s %s", username, pass);
				if(login(choice, username, pass) )
					seller(username);
				getchar();
				system("clear");
				continue;
			case 3: //Admin
				printf("Enter username and pass:");
				scanf("%s %s", username, pass);
				if(login(choice, username, pass) )
					admin();
				getchar();
				system("clear");
				continue;
			default:
				break;
		}
		break;
	}
}
void buyer(char *username){	/*Buyer related activity*/
	char string[32], *category, *brand;
	bill *a, b;
	product *temp;
	initbill(&b);
	int choice, choice2, quantity;
	while(1) {
		system("clear");
		category = brand = NULL;
		printf("\n1. Add a product\n2. Remove a product\n3. Check bill\n4. Pay the bill\n5. Logout\n6. View previous transactions\n7. Cancel previous order\n");
		scanf("%d", &choice);
		switch(choice) {
			case 1:
				system("clear");
				/*Searching for a product*/
				printf("Search for:");
				scanf("%s", string);
				if(!strcmp(string, "0"))
					string[0] = '\0';
				printf("CATEGORY:\n");
				printf("0. Search all categories\n");
				readtype(1 , 0);
				scanf("%d", &choice2);
				if(choice2)
					category = readtype(1, choice2);
				else
					category = NULL;
				printf("BRAND:\n");
				printf("0. Search all brands\n");
				readtype(2 , 0);
				scanf("%d", &choice2);
				if(choice2)
					brand = readtype(2, choice2);
				else
					brand = NULL;
				a = searchprod(string, category, brand);
				readbill(a);
				//print search results
				scanf("%d", &choice2);
				temp = removprod(a, choice2);
				//append product to bill
				while(choice2) {
					printf("Quantity:");
					scanf("%d", &quantity);
					if(quantity == 0)
						break;
					choice2 = appendbill(&b, temp, quantity);
				}
				choice2 = searchpos(temp);
				changeprod(temp->seller, 2, choice2, -quantity);
				//decrement quantity from available products
				if(category)
					free(category);
				if(brand)
					free(brand);
				free(temp);
				trashbill(a);
				free(a);
				continue;
			case 2:
				/*Removing a product from bill*/
				system("clear");
				readbill(&b);
				scanf("%d", &choice2);
				temp = removprod(&b, choice2);
				free(temp);
				continue;
			case 3:
				/*Viewing bill*/
				system("clear");
				readbill(&b);
				printf("Total = %lf", b.total);
				printf( "%s", ctime(&(b.t)) );
				getchar();
				getchar();
				continue;
			case 4:
				/*Paying bill*/
				system("clear");
				readbill(&b);
				printf("Total = %lf", b.total);
				printf("\n1. Checkout\n2. Continue Shopping\n3. Apply coupon");
				scanf("%d", &choice2);
				system("clear");
				switch(choice2) {
					case 1:
						finalbill(username, &b);
						break;
					case 2:
						continue;
					case 3:
						printf("Enter coupon:");
						scanf("%s", string);
						if( applycoupon(&b, string) )
							printf("invalid coupon");
						else
							printf("Coupon succesfully applied");
						getchar();
						getchar();
						continue;
					default:
						printf("Invalid input:");
						getchar();
						getchar();
						continue;
				}
				break;
			case 5:
				/*Trashing bill*/
				temp = b.head;
				while(temp){
					choice2 = searchpos(temp);
					changeprod(temp->seller, 2, choice2, temp->quantity);
					temp = temp->next;
				}
				trashbill(&b);
				initbill(&b);
				break;
			case 6:
				/*Viewing previous transactions*/
				system("clear");
				transaction(username);
				getchar();
				getchar();
				continue;
			case 7:
				/*cancelling a bill*/
				system("clear");
				transaction(username);
				scanf("%d", &choice);
				if(!choice)
					continue;
				scanf("%d", &choice2);
				if(!choice2)
					continue;
				cancelbill(username, choice, choice2);	
				continue;
			default:
				printf("Invalid input\n");
				getchar();
				getchar();
				continue;
		}
		break;
	}
}
void seller(char *username) {	/*Seller related activity*/
	int choice, choice2, new;
	char name[32], brand[16], category[16];
	while(1) {
		system("clear");
		printf("\n1. Add a product\n2. Remove a product\n3. Change price of a product\n4. Change quantity of a product\n5. View all products\n");
		scanf("%d", &choice);
		switch(choice) {
			case 0:
				break;
			case 1:
				/*Add a product*/
				append(username);
				system("clear");
				readprod(username);
				getchar();
				getchar();
				continue;
			case 2:
				/*Remove a product*/
				readprod(username);
				scanf("%d", &choice);
				remov(username, choice);
				continue;
			case 3:
				/*Change price of product*/
				readprod(username);
				scanf("%d", &choice2);
				system("clear");
				printf("Enter new price:");
				scanf("%d", &new);
				changeprod(username, choice - 2, choice2, new);
				continue;
			case 4:
				/*Change quantity of a product*/
				readprod(username);
				scanf("%d", &choice2);
				system("clear");
				printf("Quantity to be added");
				scanf("%d", &new);
				changeprod(username, choice - 2, choice2, new);
				continue;
			case 5:
				/*View all products*/
				readprod(username);
				getchar();
				getchar();
				continue;
			default:
				printf("Invalid input\n");
				getchar();
				getchar();
				continue;
		}
		break;
	}
}
void admin() {	/*Admin related activity*/
	int choice, choice2;
	type a;
	user b;
	coupon c;
	while(1) {
		system("clear");
		printf("\n1. Buyer\n2. Seller\n3. Category\n4. Brand\n5. Coupon\n");
		scanf("%d", &choice);
		switch(choice) {
			case 0:
				break;
			case 1:	/*change buyer info*/
				while(1) {
					system("clear");
					printf("\n1. Add a buyer\n2. Remove a buyer\n3. View all buyers\n");
					scanf("%d", &choice2);
					switch(choice2) {
						case 0:
							break;
						case 1: //Add a buyer
							system("clear");
							printf("Enter username:");
							scanf("%s", b.username);
							printf("Enter password:");
							scanf("%s", b.pass);
							adduser(choice, &b);
							continue;
						case 2: //Remove a buyer
							system("clear");
							readusers(choice);
							scanf("%d", &choice2);
							removuser(choice, choice2);
							continue;
						case 3: //View all buyers
							system("clear");
							readusers(choice);
							getchar();
							getchar();
							continue;
						default:
							system("clear");
							printf("Invalid input\n");
							getchar();
							getchar();
							continue;
					}
					break;
				}
				continue;
			case 2:/*change seller info*/
				while(1) {
					system("clear");
					printf("\n1. Add a seller\n2. Remove a seller\n3. View all sellers\n");
					scanf("%d", &choice2);
					switch(choice2) {
						case 0:
							break;
						case 1: //Add a seller
							system("clear");
							printf("Enter username:");
							scanf("%s", b.username);
							printf("Enter password:");
							scanf("%s", b.pass);
							adduser(choice, &b);
							continue;
						case 2: //Remove a seller
							system("clear");
							readusers(choice);
							scanf("%d", &choice2);
							removuser(choice, choice2);
							continue;
						case 3: //View all sellers
							system("clear");
							readusers(choice);
							getchar();
							getchar();
							continue;
						default:
							system("clear");
							printf("Invalid input\n");
							getchar();
							getchar();
							continue;
					}
					break;
				}
					continue;
			case 3:	/*category info*/
				while(1) {
					system("clear");
					printf("\n1. Add a category\n2. Remove a category\n3. View all categories\n");
					scanf("%d", &choice2);
					switch(choice2) {
						case 0:
							break;
						case 1: //Add a category
							system("clear");
							printf("Enter new category:");
							scanf("%s", a.name);
							addtype(choice - 2, &a);
							continue;
						case 2: //Remove a category
							system("clear");
							readtype(choice - 2, 0);
							scanf("%d", &choice2);
							removtype(choice - 2, choice2);
							continue;
						case 3: //View all categories
							system("clear");
							readtype(choice - 2, 0);
							getchar();
							getchar();
							continue;
						default:
							system("clear");
							printf("Invalid input\n");
							getchar();
							getchar();
							continue;
					}
					break;
				}
				continue;
			case 4:	/*brand info*/
				while(1) {
					system("clear");
					printf("\n1. Add a brand\n2. Remove a brand\n3. View all brands\n");
					scanf("%d", &choice2);
					switch(choice2) {
						case 0:
							break;	
						case 1: //Add a brand
							system("clear");
							printf("Enter new brand:");
							scanf("%s", a.name);
							addtype(choice - 2, &a);
							continue;
						case 2: //Remove a brand
							system("clear");
							readtype(choice - 2, 0);
							scanf("%d", &choice2);
							removtype(choice - 2, choice2);
							continue;
						case 3: //View all brands
							system("clear");
							readtype(choice - 2, 0);
							getchar();
							getchar();
							continue;
						default:
							system("clear");
							printf("Invalid input\n");
							getchar();
							getchar();
							continue;
					}
					break;
				}
				continue;
			case 5:/*coupon*/
				while(1) {
					system("clear");
					printf("\n1. Add a coupon\n2. Remove a coupon\n3. View all coupon\n");
					scanf("%d", &choice);
					switch(choice) {
						case 0:
							break;
						case 1:	//Add a coupon
							system("clear");
							printf("Enter coupon key:");
							scanf("%s", c.key);
							printf("Enter minimum amount:");
							scanf("%d", &c.min);
							printf("Days valid for:");
							scanf("%d", &choice);
							c.valid = time(NULL) + choice * 24 * 60 *60;
							printf("Percent off:");
							scanf("%f", &c.off);
							readcoupon();
							addcoupon(&c);
							getchar();
							getchar();
							continue;
						case 2: //Remove a coupon
							system("clear");
							readcoupon();
							scanf("%d", &choice2);
							continue;
						case 3: //View all coupon
							system("clear");
							readcoupon();
							getchar();
							getchar();
							continue;
						default:
							system("clear");
							printf("Invalid input");
							getchar();
							getchar();
							continue;
					}
					break;
				}
			default:
				system("clear");
				printf("Invalid input\n");
				getchar();
				getchar();
				continue;
		}
		break;
	}
}
