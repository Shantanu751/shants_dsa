
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
//functions used by seller
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "h.h"	
void append(char *username) {
	/* append a product to seller file*/
	char *temp;
	int choice;
	temp = (char *)malloc(strlen(username) + 8 );
	strcpy(temp,"seller/");
	strcat(temp, username);
	
	FILE *fp = fopen(temp, "a");
	free(temp);
	if(fp == NULL) {
		printf("error\n");
		return;
	}
	
	product tmp;
	printf("Category:\n");
	readtype(1, 0); //print all categories
	scanf("%d", &choice);
	temp = readtype(1, choice);
	strcpy(tmp.category, temp);
	free(temp);
	
	printf("Enter name of product, price of product and quantity\n");
	scanf("%s %d %d", tmp.name, &tmp.price, &tmp.quantity);
	
	printf("Brand:\n");
	readtype(2, 0); //printf all brands
	scanf("%d", &choice);
	temp = readtype(2, choice);
	strcpy(tmp.brand, temp);
	free(temp);
	strcpy(tmp.seller, username); //copy seller info to product
	fwrite(&tmp, sizeof(product), 1, fp);
	fclose(fp);
}
void readprod(char *username) {
	/*print all products by "seller"*/
	int i = 1;
	char *temp;
	temp = (char *)malloc(strlen(username) + 8 );
	strcpy(temp,"seller/");
	strcat(temp, username);
	int fd = open(temp, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	free(temp);
	if(fd == -1) {
		printf("error\n");
		return;
	}
	product p;
	while( read(fd, &p, sizeof(product)) ) {
		printf("%d. Name: %s\n   Brand: %s\n   Price: %d\n   Quantity: %d\n   Category: %s\n\n", i, p.name, p.brand, p.price, 														p.quantity, p.category);
		i++;
	}
	close(fd);
}
void remov(char *username, int pos) {
	/* Open file of seller
	 * remove pos th product*/
	int i = 1;
	char *temp;
	product p;
	FILE *fp = fopen("temp", "w");
	if(fp == NULL) {
		printf("error\n");
		return;
	}
	temp = (char *)malloc(strlen(username) + 8 );
	strcpy(temp,"seller/");
	strcat(temp, username);
	int fd = open(temp, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		free(temp);
		printf("error\n");
		return;
	}

	while( read(fd, &p, sizeof(product)) ) {
		if(i != pos) {
		fwrite(&p, sizeof(product), 1, fp);
		}
		i++;
	}
	fclose(fp);
	close(fd);
	if( remove(temp) )
		printf("error");
	if( rename("temp", temp) )
		printf("error");
	free(temp);
}
void changeprod(char *username, int choice, int pos, int new) {
	/* change price or quantity of  product
	 * choice 1 price
	 * 2 quantity*/
	char *temp;
	temp = (char *)malloc(strlen(username) + 8 );
	strcpy(temp,"seller/");
	strcat(temp, username);
	if(pos == 0)
		return;
	FILE *fp = fopen("temp", "w");
	if(fp == NULL) {
		printf("error\n");
		return;
	}

	int fd = open(temp, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		printf("error\n");
		return;
	}

	int i = 1;
	product p;
	while( read(fd, &p, sizeof(product)) ) {
		//search pos th position and change the required value
		if(i == pos) {
			if(choice == 1) {
				p.price = new;
			}
			else if(choice == 2) {
				p.quantity += new;
			}
		}
		fwrite(&p, sizeof(product), 1, fp);
		i++;
	}
	fclose(fp);
	close(fd);
	if( remove(temp) )
		printf("error");
	if( rename("temp", temp) )
		printf("error");
	free(temp);
}
