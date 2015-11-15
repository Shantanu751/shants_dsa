/*Contains all function prototypes and structure defination*/
#include <time.h>
typedef struct coupon{
	char key[16];
	time_t valid;
	int min;
	float off;
}coupon;
typedef struct type{
	char name[16];
}type;
typedef struct user{
	char username[32], pass[32];
}user;
typedef struct product {
	char name[32];
	char brand[16];
	char seller[32];
	char category[16];
	int price, quantity;
	struct product *next;
}product;
typedef struct bill{
	time_t t;
	int quantity, coupon;
	double total;
	product *head, *tail;
}bill;

void append(char *username);
void readprod(char *username);
void remov(char *username, int pos);
void changeprod(char *username, int choice, int pos, int temp);
int login(int choice, char *username, char *pass);
void adduser(int choice, user *p);
void admin();
void readusers(int choice);
void removuser(int choice, int choice2);
void seller(char *username);
char *readtype(int choice, int pos);
void addtype(int choice, type *p);
void removtype(int choice, int choice2);
void buyer(char *username);
int compare(char *string, char *product);
void initbill(bill *a);
bill *searchprod(char *string, char *category, char *brand);
int appendbill(bill *l, product *p, int quantity);
void readbill(bill *l);
product *removprod(bill *l, int pos);
void trashbill(bill *l);
void finalbill(char *username, bill *b);
int searchpos(product *p);
void transaction(char *username);
int cancelbill(char *username, int pos, int pos2);
void addcoupon(coupon *p);
void readcoupon();
void removecoupon(int pos);
