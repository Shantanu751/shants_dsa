
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
//All functions related to admin
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "h.h"
int login(int choice, char *username, char *pass) {
	/*returns 1 for correct username and password details else 0*/
	/* choice 1 is for buyer
	 * 2 is for seller
	 * 3 is for admin*/
	char *filename[3] = {"login/buyer", "login/seller", "login/admin"};
	int fd = open(filename[choice - 1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		printf("error\n");
		return;
	}
	user p;
	while( read(fd, &p, sizeof(user)) ) {
		if( !strcmp(p.username, username) ) {
			if( !strcmp(p.pass, pass) )
				return 1;
			else {
				printf("Incorrect pass\n");
				return 0;
			}
		}
	}
	printf("Incorrect username\n");
	close(fd);
	return 0;
}
void adduser(int choice, user *p) {
	/* choice 1 is for buyer
	 * 2 is for seller
	 * 3 is for admin*/
	char *filename[3] = {"login/buyer", "login/seller", "login/admin"};
	FILE *fp = fopen(filename[choice - 1], "a");
	if(fp == NULL) {
		printf("error\n");
		return;
	}
	fwrite(p, sizeof(user), 1, fp);/*append login file*/
	fclose(fp);
}
void readusers(int choice) {
	/* prints all users along with their password*/
	/* choice 1 is for buyer
	 * 2 is for seller
	 * 3 is for admin*/
	int i = 1;
	user p;
	char *filename[3] = {"login/buyer", "login/seller", "login/admin"};
	int fd = open(filename[choice - 1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		printf("error\n");
		return;
	}
	while( read(fd, &p, sizeof(user)) ) {
		printf("%d. username: %s\n   pass:%s\n\n", i, p.username, p.pass);
		i++;
	}
	close(fd);
}
void removuser(int choice, int choice2) {
	/* removes choice2 entry from login file*/
	/* choice 1 is for buyer
	 * 2 is for seller
	 * 3 is for admin*/
	user p;
	int i = 1;
	char *filename[3] = {"login/buyer", "login/seller", "login/admin"};
	FILE *fp = fopen("temp", "w");
	if(fp == NULL) {
		printf("error\n");
		return;
	}

	int fd = open(filename[choice - 1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		printf("error\n");
		return;
	}
	while( read(fd, &p, sizeof(user)) ) {
		if(i != choice2) {
		fwrite(&p, sizeof(user), 1, fp);
		}
		i++;
	}
	fclose(fp);
	close(fd);
	if( remove(filename[choice - 1]) )
		printf("error");
	if( rename("temp", filename[choice - 1]) )
		printf("error");
}
void addtype(int choice, type *p) {
	/* adds a brand or category*/
	/* choice 1 is for category
	 * 2 is for brand*/
	char *filename[2] = {"type/category", "type/brand"};
	FILE *fp = fopen(filename[choice - 1], "a");
	if(fp == NULL) {
		perror("fopen failed");
		return;
	}
	fwrite(p, sizeof(type), 1, fp);
	fclose(fp);
}
void removtype(int choice, int choice2) {
	/* removes a brand or category*/
	/* choice 1 is for category
	 * 2 is for brand*/
	type p;
	int i = 1;
	char *filename[2] = {"type/category", "type/brand"};
	
	int fd = open(filename[choice - 1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		printf("error\n");
		return;
	}
	
	FILE *fp = fopen("temp", "w");
	if(fp == NULL) {
		printf("error\n");
		return;
	}

	while( read(fd, &p, sizeof(type)) ) {
		if(i != choice2) {
		fwrite(&p, sizeof(type), 1, fp);
		}
		i++;
	}
	close(fd);
	fclose(fp);
	if( remove(filename[choice - 1]) )
		printf("error");
	if( rename("temp", filename[choice - 1]) )
		printf("error");
}
void readcoupon() {
	//print all coupons
	int i = 1;
	coupon p;
	int fd = open("type/coupon", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		printf("error\n");
		return;
	}
	while( read(fd, &p, sizeof(coupon)) ) {
		printf("%d. key %s\n   min:%d\n   off:%f\n  valid till:", i, p.key, p.min, p.off);
		printf("%s", ctime(&(p.valid)) ); 
		printf("\n\n");
		i++;
	}
	close(fd);
}
void addcoupon(coupon *p) {
	//Add coupon 'p' to coupon file
	FILE *fp = fopen("type/coupon", "a");
	if(fp == NULL) {
		perror("fopen failed");
		return;
	}
	fwrite(p, sizeof(coupon), 1, fp);
	fclose(fp);
}
void removecoupon(int pos) {
	//remove pos th position of coupon
	int i = 1;
	coupon p;
	int fd = open("type/coupon", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1) {
		printf("error\n");
		return;
	}
	
	FILE *fp = fopen("type/temp", "w");
	if(fp == NULL) {
		printf("error\n");
		return;
	}
	while( read(fd, &p, sizeof(coupon)) ) {
		if(i != pos) {
		fwrite(&p, sizeof(coupon), 1, fp);
		}
		i++;
	}
	if( remove("type/coupon") )
		printf("error");
	if( rename("type/temp", "type/coupon") )
		printf("error");
}
