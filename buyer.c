
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
//functions used by buyer
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "h.h"
char *readtype(int choice, int pos) { 
	/* returns name of category or brand at position "pos" as a string pointer
	 * choice 1 is for category
	 * 2 is for brand								*/
	char *temp = NULL;
	char *filename[2] = {"type/category", "type/brand"};
	int i = 1;
	int fd = open(filename[choice - 1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		printf("error\n");
		return;
	}
	type p;
	if(pos == 0) {
		while( read(fd, &p, sizeof(type)) ) {
			printf("%d. %s\n", i, p.name);
			i++;
		}
		close(fd);
		return NULL;
	}
	else
		while( read(fd, &p, sizeof(type)) ) {
			if(i == pos) {
				temp = (char *)malloc(strlen(p.name) + 1);
				strcpy(temp, p.name);
				break;
			}
			i++;
		}
	close(fd);
	return temp;
}
bill *searchprod(char *string, char *category, char *brand) {
	/* returns a bill(linked list) of all products with name "string" in "category" of "brand"*/
	user a;
	char *temp;
	temp = (char *)malloc(64);
	product b;
	bill *p;
	p = (bill *)malloc(sizeof(bill));
	initbill(p);
	int fd, fd2;
	fd = open("login/seller", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		printf("error\n");
		return NULL;
	}
	while( read(fd, &a, sizeof(user)) ) {
		strcmp(temp,"seller/");
		strcat(temp, a.username);
		fd2 = open(temp, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
		if(fd2 == -1) {
			printf("error\n");
			return NULL;
		}
		while( read(fd2, &b, sizeof(product)) ) {
			if(category != NULL) {
				if(strcmp(category, b.category) )
					continue;
			}
			if(brand != NULL) {
				if(strcmp(brand, b.brand) )
					continue;
			}
			if( compare(string, b.name) )
				appendbill(p, &b, b.quantity);
		}
		close(fd2);
	}
	close(fd);
	free(temp);
	return p;
}
	
int compare(char *b, char *a) {
	/* Compares if b is a substring of a*/
	char *p = a, *string = b;
	while(*p != '\0' && *string != '\0') {
		if(*p == *string || *p + ('a' - 'A') == *string || *p - ('a' - 'A')== *string) {
			p++;
			string++;
		} else {
			p = p - (string - b) + 1;
			string = b;
		}
	}
	if(*string == '\0')
		return 1;
	else
		return 0;
}

int searchpos(product *p) {
	/* search product p and return its position in the file*/
	if(p == NULL)
		return 0;
	int i = 1;
	char *temp;
	temp = (char *)malloc(strlen(p->seller) + 8 );
	strcpy(temp,"seller/");
	strcat(temp, p->seller);
	int fd = open(temp, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		printf("error\n");
		return;
	}
	product tmp;
	while( read(fd, &tmp, sizeof(product)) ) {
		if(!strcmp(tmp.name,p->name) && !strcmp(tmp.brand, p->brand) && !strcmp(tmp.category, p->category)) {
			close(fd);
			return i;
		}
		i++;
	}
	free(temp);
	close(fd);
	return 0;
}
void transaction(char *username) {
	/* Open file of buyer
	 * View all past transaction				*/
	int i, j = 1;
	char *temp;
	temp = (char *)malloc(strlen(username) + 7 );
	strcpy(temp,"buyer/");
	strcat(temp, username);
	product *tmp;
	bill b;
	product p;
	
	int fd = open(temp, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		printf("error\n");
		free(temp);
		return;
	}
	
	while( read(fd, &b, sizeof(bill)) ) {
		printf("\n%d. Total Amount: %lf\n", j, b.total);
		for(i = 1; i <= b.quantity; i++) {
			read(fd, &p, sizeof(product));
			printf("\t%d. Name: %s\n\t   Brand: %s\n\t   Price: %d\n\t   Quantity: %d\n\t   Category: %s\n", i, p.name, p.brand, p.price, p.quantity, p.category);
		}
		j++;
	}
	close(fd);
	free(temp);
}
int cancelbill(char *username, int pos, int pos2) {
	/*returns 0 if an order is successfully cancelled
	 *else returns 1					*/
	char *temp;
	product p, *q;
	bill a, b;
	time_t currenttime;
	int j, i = 1;
	
	temp = (char *)malloc(strlen(username) + 7 );
	strcpy(temp,"buyer/");
	strcat(temp, username);
	//Open file
	int fd = open(temp, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		printf("error\n");
		free(temp);
		return 1;
	}
	
	FILE *fp = fopen("temp", "w");
	if(fp == NULL) {
		printf("error\n");
		return 1;
	}
	while( read(fd, &b, sizeof(bill)) ) {
		//Find bill to be cancelled
		if(i == pos) {
			//return 1 if coupon was used for transaction
			if(b.coupon) {
				close(fd);
				close(fp);
				remove("temp");
				return 1;
			}
			//return 1 if transaction is older than 7 days
			currenttime = time(NULL);
			if((currenttime - b.t) > (7 * 60 * 60 * 24) ){
				close(fd);
				close(fp);
				remove("temp");
				return 1;
			}
			initbill(&a);
			for(j = 1; j <= b.quantity; j++) {
				//traverse to required product
				read(fd, &p, sizeof(product));
				if(j != pos2)
					appendbill(&a, &p, p.quantity);
			}
			fwrite(&a, sizeof(bill), 1, fp);
			q = a.head;
			while(q) {
				fwrite(q, sizeof(product), 1, fp);
				q = q->next;
			}
			trashbill(&a);
		}	
		else{
			fwrite(&b, sizeof(bill), 1, fp);
			for(j = 1; j <= b.quantity; j++) {
				read(fd, &p, sizeof(product));
				fwrite(&p, sizeof(product), 1, fp);		
			}
		}
		i++;
	}
	fclose(fp);
	close(fd);
	//remove old file
	if( remove(temp) )
		printf("error");
	//rename new file
	if( rename("temp", temp) )
		printf("error");
	free(temp);
	return 0;
}
int applycoupon(bill *b, char *key) {
	/* returns 0 if coupon in successfully applied
	 * else returns 1					*/
	int n;
	time_t curr;
	curr = time(NULL);
	if(b->coupon)
		return 1;
	coupon p;
	int fd = open("type/coupon", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		printf("error\n");
		return;
	}
	while(n = read(fd, &p, sizeof(coupon)) ) {
		if(!strcmp(key, p.key)) //check if key is correct
			break;
	}
	if(n == 0) //return  if searched whole file and key is not found
		return 1;
	if( (b->total < p.min) || curr > p.valid ) //check if coupon is valid for bill b
		return 1;
	b->total = b->total * p.off/100;
	b->coupon = 1;
	close(fd);
	return 0;
}
