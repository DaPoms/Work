Create table captain(
    captainID char(6),
    firstName varchar2(20),
    lastName varchar2(20),
    Constraint captain_PK primary key(captainID)
);

Create table shipment(
shipmentID char(7),
origin varchar2(20),
destination varchar2(20),
shipmentDate Date,
arrivalDate Date,
shipnumber Number(3,0),
captainID char(6),
Constraint shipment_pk primary key(shipmentID),
Constraint shipment_fk foreign key(captainID)
    references captain(captainID) --must tell where we reference foreign key
);



Create table item(
    itemNo Number(4,0), -- 0 specifies int not decimal
    item_description varchar2(30),
    item_type char(2),
    unit_weight Number(6,0),
    Constraint item_pk primary key(itemNo)
);

Create table shipmentLine(
    shipmentID char(7),
    itemNo number (4,0),
    quantity number(5,0),
    Constraint shipmentLine_pk primary key(shipmentID, itemNo),
    Constraint shipmentLine_fk1 foreign key(shipmentID) -- foreign key must be referenced one by one
        references shipment(shipmentID),
    Constraint shpmentLine_fk2 foreign key(itemNo)
        references item(itemNo)
);


Insert into shipment values('1111111', 'china', 'cool', '20-JAN-2024', '21-JAN-2024', 3, "aaaaaaa");
Insert into item values(5, '20', 'YO', 5);
Insert into shipmentline values('1111111', 5, 100);
Select * from SHIPMENTLINE;
