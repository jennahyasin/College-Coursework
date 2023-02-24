-- hw6.sql
-- Jennah Yasin
-- 1  Mapping of production to warehouse tables and columns
--
--  Active Transformations:
-- seminar_customer, contact, seminar tables were removed/dropped
-- hsd.CUSTOMER.LastName + hsd.CUSTOMER.FirstName -> hsddw.customer.customername
-- hsd.CUSTOMER.EmailAddress -> hsddw.customer.emaildomain
-- drop password
-- street address dropped
-- phone phoneareacode
-- product table:
-- drop unit price and quanityonhand
-- invoice table was dropped and columns were split up into these tables: 
-- hsd.invoice.invoicedate -> hsdww.timeline.date
-- hsd.invoice.customerid -> hsdww.product_sales.customerid
-- LINE_ITEM table dropped but columns were split into these tables:
-- hsd.line_item.productnumber -> hsdww.product_sales.productnumber
-- hsd.line_item.unitprice -> hsdww.product_sales.unitprice
-- hsd.line_item.quantity -> hsdww.product_sales.quantity
-- hsd.line_item.total -> hsdww.product_sales.total
-- hsd.INVOICE.InvoiceDate -> hsddw.months.monthtext, hsddw.months.quarterid,
-- hsddw.months.quartertext

-- 2 Load data for table SALES_FOR_RFM  
INSERT INTO hsddw.sales_for_rfm 
	(TimeId, CustomerId, InvoiceNumber, PreTaxTotalSales)

SELECT t.timeid, c.customerid, i.invoicenumber, i.subtotal

FROM hsddw.timeline t, hsddw.customer c, hsd.invoice i

WHERE i.customerid = c.customerid AND i.invoicedate = t.date;

-- 3  create view of total dollar amount of each product for each year 
CREATE VIEW TotalPrice AS
	SELECT c.CustomerId, c.CustomerName, c.City, p.ProductNumber, p.ProductName,
		t.Year,t.QuarterText, SUM(ps.total) AS TotalPrice
	FROM customer c, product_sales ps, product p, timeline t
	WHERE c.CustomerId = ps.CustomerID 
		AND p.ProductNumber = ps.ProductNumber AND t.TimeId = ps.TimeID
	GROUP BY c.CustomerId, c.CustomerName, c.City, p.ProductNumber, p.ProductName,
			t.QuarterText, t.Year
	ORDER BY c.CustomerName, t.Year, t.QuarterText;
-- 4  populate the product_sales table with the new payment_id column.
INSERT INTO hsddw.product_sales
   (TimeId, CustomerId, productnumber, quantity, unitprice, total, payment_type_id)
   
   SELECT t.timeid, i.customerid, l.productnumber, SUM(l.quantity),
      MIN(l.unitprice), SUM(l.total), p.payment_type_id
      
   FROM hsddw.timeline t, hsd.invoice i, hsd.line_item l, payment_type p
   
   WHERE i.invoicenumber = l.invoicenumber 
	AND i.invoicedate = t.date AND p.payment_type = i.paymenttype
    
   GROUP BY t.timeid, i.customerid, l.productnumber, p.payment_type_id;