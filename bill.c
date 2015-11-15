
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
//functions related to bill
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "h.h"
void initbill(bill *a) {
	//Initializing a bill
	a->head = a->tail = NULL;
	a->quantity = a->total = a->coupon = 0;
}
int appendbill(bill *l, product *p, int quantity) {
	/* Create a product using tmp pointer
	 * Store the data
	 * change  tmp->next, tmp->prev, head->prev, tail->next, tail 
	 */
	if(quantity > p->quantity) {
		printf("Requested quantity not available\n");
		return 1;
	}
	if(p == NULL)
		return 1;
	l->total = l->total + p->price * quantity;
	l->quantity++;
	product *tmp = (product *)malloc(sizeof(product));
	*tmp = *p;
	tmp->quantity = quantity;
	tmp->next = NULL;
	if(l->head) {
		l->tail->next = tmp;
	} else {
		l->head = tmp;
	}
	l->tail = tmp;
	return 0;
}
void readbill(bill *l) {
	//read bill l
	product *p;
	p = l->head;
	int i = 1;
	while(p != NULL) {
		printf("%d. Name: %s\n   Brand: %s\n   Price: %d\n   Quantity: %d\n   Category: %s\n\n", i, p->name, p->brand, p->price, 														p->quantity, p->category);
		i++;
		p = p->next;
	}
}
product *removprod(bill *l, int pos) {
	//remove product a pos th position from bill l
	product *p, *value, *temp = NULL;
	int i;
	/* Locate the product at position = pos
	 * Rechain 
	 * Free the product
	 */
	/* Locate the product */
	if(pos < 1 || pos > l->quantity)
		return NULL;
	/* pos is correct */
	value = (product *)malloc(sizeof(product));
	p = l->head;
	for(i = 1; i < pos; i++) {
		temp = p;
		p = p->next;
	}
	*value = *p;
	if(p == l->head) {
		l->head = p->next;
	}
	else {
		temp->next = p->next;
	}
	if(p == l->tail)
		l->tail = temp;
	free(p);	
	return value;
}
void finalbill(char *username, bill *b) {
	/* Open file of the buyer
	 * Add the recent bill at the end of the file
	 * Close the file*/
	char *temp;
	temp = (char *)malloc(strlen(username) + 7 );
	strcpy(temp, "buyer/");
	strcat(temp, username);
	b->t = time(NULL);
	product *tmp;
	int i;
	FILE *fp = fopen(temp, "a");
	if(fp == NULL) {
		printf("error\n");
		free(temp);
		return;
	}
	fwrite(b, sizeof(bill), 1, fp);
	tmp = b->head;
	for(i = 0; i < b->quantity; i++) {
		fwrite(tmp, sizeof(product), 1, fp);
		tmp = tmp->next;
	}
	fclose(fp);
	free(temp);
}
void trashbill(bill *l) {
	/*Free all the nodes of linked list l*/
	product *p, *temp;
	p = l->head;
	while(p != NULL) {
		temp = p;
		p = p->next;
		free(temp);
	}
}
