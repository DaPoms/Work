-- HW problem 1
WITH invoice_IL AS
(
SELECT *
FROM invoices
JOIN invoice_line
USING (invoice_num)
)
SELECT 
    invoice_num, 
    invoice_date, 
    cust_ID,
    first_name,
    last_name,
    item_id,
    quantity
    --sum(quantity)
FROM customer 
JOIN invoice_IL  
USING (cust_id) 
WHERE invoice_date = '15-NOV-21';

--HW problem 2
WITH invoice_IL AS
(
SELECT * 
FROM item JOIN
(
    SELECT *
    FROM invoices
    JOIN invoice_line
    USING (invoice_num)
)
USING (item_ID)
)
SELECT 
    invoice_num, 
    invoice_date, 
    item_id,
    description,
    category
FROM customer 
JOIN invoice_IL  
USING (cust_id) 
WHERE invoice_date = '18-NOV-21';


--HW problem 3
select
	item_id,
	description,
    price,
	category
FROM item
WHERE price >= (SELECT AVG(price) from item);
