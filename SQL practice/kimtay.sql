-- These are p ossible scripts to run on the kimtay database we are using in class

select cust_id, c.first_name
from customer c join sales_rep s on (c.rep_id = s.rep_id) -- joins where c rep = s rep
where credit_limit = 500;

select cust_id, c.first_name, rep_id
from customer c join sales_rep s using (rep_id) -- joins where c rep = s rep
where credit_limit = 500;


select c.first_name, c.last_name, cust_id, i.invoice_date
from customer c join invoices i using (cust_id)
where (i.invoice_date < '18-NOV-21');

--equivalent to above
select first_name, last_name, city from customer where cust_id IN
(
	select cust_id from invoices where (invoice_date < '18-NOV-21')
);


select invoice_num, invoice_date from invoices where exists --exists version of the below
    (
    	Select * from invoice_line where (invoices.invoice_num = invoice_line.invoice_num) AND (item_id = 'KH81')
    );

select invoice_num, invoice_date from invoices where invoice_num IN -- in version of the above
    (
    	Select invoice_num from invoice_line where (invoices.invoice_num = invoice_line.invoice_num) AND (item_id = 'KH81')
    );

select invoices.invoice_num, invoice_date from invoices join invoice_line -- join + on version of above
	on invoices.invoice_num = invoice_line.invoice_num
	where item_id = 'KH81'
