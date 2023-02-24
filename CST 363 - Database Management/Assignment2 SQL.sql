-- e5.1 Exercises from chapter 5
--
-- Before you begin:
-- re-create the tables and data using the script 
--   zagimore_schema.sql

-- 1  Display the RegionID, RegionName and number of stores in each region.
SELECT r.regionid, r.regionname, COUNT(s.storeid)
FROM region r
INNER JOIN store s ON r.regionid=s.regionid
GROUP BY (r.regionid);
-- 2 Display CategoryID and average price of products in that category.
--   Use the ROUND function to show 2 digits after decimal point in average price.
SELECT categoryid, ROUND(AVG(productprice),2)
FROM product 
GROUP BY (categoryid); 
-- 3 Display CategoryID and number of items purchased in that category.
SELECT categoryid, SUM(quantity)
FROM product p
INNER JOIN includes i ON p.productid=i.productid
GROUP BY (categoryid);
-- 4 Display RegionID, RegionName and total amount of sales as "AmountSpent"
SELECT r.regionid, r.regionname, SUM(productprice*quantity) AS AmountSpent
FROM region r
INNER JOIN store s ON r.regionid=s.regionid
INNER JOIN salestransaction st ON s.storeid=st.storeid
INNER JOIN includes i ON st.tid=i.tid
INNER JOIN product p ON i.productid=p.productid
GROUP BY(regionid);
-- 5 Display the TID and total number of items in the sale
--    for all sales where the total number of items is greater than 3
SELECT tid, SUM(quantity)
FROM includes
GROUP BY (tid)
HAVING(SUM(quantity)  > 3);
-- 6 For vendor whose product sales exceeds $700, display the
--    VendorID, VendorName and total amount of sales as "TotalSales"
SELECT v.vendorid, v.vendorname, SUM(quantity*productprice) AS TotalSales
FROM vendor v
INNER JOIN product p ON v.vendorid=p.vendorid
INNER JOIN includes i ON p.productid=i.productid
GROUP BY (vendorid)
HAVING TotalSales > 700;
-- 7 Display the ProductID, Productname and ProductPrice
--    of the cheapest product.
SELECT productid, productname, productprice 
FROM product 
WHERE productprice = (SELECT MIN(productprice) FROM product);
-- 8 Display the ProductID, Productname and VendorName
--    for products whose price is below average price of all products
--    sorted by productid.
SELECT productid, productname, vendorname
FROM product p
INNER JOIN vendor v ON p.vendorid=v.vendorid
WHERE productprice < (SELECT AVG(productprice) FROM product)
ORDER BY productid;
-- 9 Display the ProductID and Productname from products that
--    have sold more than 2 (total quantity).  Sort by ProductID
SELECT productid, productname
FROM product
WHERE(SELECT SUM(quantity) > 2 FROM includes)
ORDER BY productid;
-- 10 Display the ProductID for the product that has been 
--    sold the most (highest total quantity across all
--    transactions). 
SELECT productid
FROM includes
GROUP BY productid
HAVING SUM(quantity) = 
(select MAX(total_quantity) AS max_quantity
 FROM (select productid, SUM(quantity) AS total_quantity FROM includes GROUP BY productid) AS temp
);
-- 11 Rewrite query 30 in chapter 5 using a join.
SELECT p.productid, p.productname, p.productprice
FROM product p
INNER JOIN includes i ON p.productid=i.productid
GROUP BY productid
HAVING SUM(quantity) > 3;
-- 12 Rewrite query 31 using a join.
SELECT p.productid, p.productname, p.productprice
FROM product p
INNER JOIN includes i ON p.productid=i.productid
GROUP BY productid
HAVING COUNT(tid) > 1;
-- 13 create a view over the product, salestransaction, includes, customer, store, region tables
--     with columns: tdate, productid, productname, productprice, quantity, customerid, customername, 
--                   storeid, storezip, regionname
CREATE VIEW all_tables AS  
SELECT tdate, p.productid, productname, productprice, quantity, c.customerid, customername, 
		s.storeid, storezip, regionname
FROM product p
INNER JOIN includes i ON p.productid=i.productid
INNER JOIN salestransaction st ON i.tid=st.tid
INNER JOIN customer c ON st.customerid=c.customerid
INNER JOIN store s ON st.storeid=s.storeid
INNER JOIN region r ON s.regionid=r.regionid;
-- 14 Using the view created in question 13
--   Display ProductID, ProductName, ProductPrice  
--   for products sold in zip code "60600" sorted by ProductID
SELECT productid, productname, productprice 
FROM all_tables
WHERE storezip = '60600' 
ORDER BY productid;
-- 15 Using the view from question 13 
--    display CustomerName and TDate for any customer buying a product "Easy Boot"
SELECT customername, tdate
FROM all_tables 
WHERE productname='Easy Boot';
-- 16 Using the view from question 13
--    display RegionName and total amount of sales in each region as "AmountSpent"
SELECT regionname, SUM(productprice*quantity) AS AmountSpent
FROM all_tables
GROUP BY regionname;
-- 17 Display the product ID and name for products whose 
--    total sales is less than 3 or total transactions is at most 1.
--    Use a UNION. 
SELECT p.productid, p.productname
FROM product p
INNER JOIN includes i ON p.productid=i.productid
GROUP BY productid
HAVING SUM(quantity) < 3
UNION 
SELECT p.productid, productname
FROM product p
INNER JOIN includes i ON p.productid=i.productid
GROUP BY productid
HAVING COUNT(*) <= 1; 
-- 18 Create a view named category_region 
--    over the category, region, store, salestranaction, includes,
--    and product tables that summarizes total quantity sold by region and category.  The view 
--    should have columns:
--    categoryid, categoryname, regionid, regionname, totalsales
CREATE VIEW category_region AS 
SELECT c.categoryid, c.categoryname, r.regionid, r.regionname, SUM(i.quantity) as totalsales
FROM category c 
INNER JOIN product p ON p.categoryid=c.categoryid
INNER JOIN includes i ON p.productid=i.productid
INNER JOIN salestransaction st ON i.tid=st.tid
INNER JOIN store s ON st.storeid=s.storeid
INNER JOIN region r ON s.regionid=r.regionid
GROUP BY c.categoryid, r.regionid;
-- 19 Using the view created in 18, which region has the most sales for 
--    each category.
--    you should get the result
--    categoryname  regionname    totalsales
--    Electronics   Chicagoland   6
--    Climbing      Indiana       17
--    Camping       Tristate      9
--    Footwear      Tristate      20
--    Cycling       Chicagoland   13
SELECT categoryname, regionname, totalsales
FROM category_region outerp
WHERE totalsales = (select MAX(innerp.totalsales) from category_region innerp 
						where innerp.categoryname=outerp.categoryname);
