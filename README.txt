Title: ONLINE SHOPPING MODEL
NAME: SHANTANU R PANDE
MIS: 111308077
-------------------------------------------------------------------------------------------------------------------------------------
DISCRIPTION:
Project is similar to a online shopping model.

Project is divided into three parts:
1. Admin
2. Seller
3. Buyer
Each of these parts have a separate .c file
-------------------------------------------------------------------------------------------------------------------------------------
Admin:
The login and pass of admin is "admin".
The admin has control over 5 things: Buyers, Sellers, Brands, Category, Coupons.
Admin can view, add, remove all above mentioned things.
*Coupon is valid only till a particular date and for a minimum amount of bill*
----------------------------------------------------------------------------------
Seller:
Seller has to login through a username and password that could be created only by admin.
Seller can offer any product and has to specify its prize, quantity, category and brand.
Seller can change price of a product or even remove a product.
All its data is stored in a folder "Seller"
---------------------------------------------------------------------------------------
Buyer:
Buyer has to login through a username and password that could be created only by admin.
Buyer can search for any product in the basis of brand and category.
*To view all products of a particular brand and category, search for "0" *
Add products to his cart, view his bill and apply coupons.
Buyer can all view his transaction history and cancel his previous orders if it is
not older than 7 days.
*A product bought with a coupon cannot be cancelled*
All its data is stored in a folder "Buyer"

All functions related to 'Bill' are separated in a file "bill.c" which could have been
a part of "buyer.c"
--------------------------------------------------------------------------
Coupons, brands and categories as stored in a folder "Type"
Login data is stored in folder "Login"

------------------------------------------------------------------------------------------------------------------------------------------

I tried to make a online shopping model.
A similar service is provided by flipkart, ebay and many other companies.
Each buyer and seller has a username and pass.
Admin overlooks everything like sellers, buyers and all other offers.
Seller can offer products for a price.
Seller can also manage price and available quantity of products he offers.
Buyer can search for a product.
He could search in different categories and brands and apply coupons.
View and cancel previous transactions.
Money transactions and networking was ignored.
---------------------------------------------------------------------------------------------------------------------------------------
