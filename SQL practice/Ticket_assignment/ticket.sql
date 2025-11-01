DROP table license; --FreeSQL requires manual deletion of tables (liveSQL has a button to do it)
DROP table ticket;
DROP table student;
DROP table code;


CREATE table student(
    studentID number(5,0),
    lName varchar2(20),
    fName varchar2(20),
    phoneNumber char(8), --requires format: 123-4567
    CONSTRAINT captain_PK primary key(studentID)
);

CREATE table license(
    licenseNumber char(7), -- Requires this format: 'XYZ 123'
    licenseState char(2),
    studentID number(5,0),
    CONSTRAINT license_PK primary key(licenseNumber),
    CONSTRAINT license_FK foreign key(studentID) REFERENCES student(studentID)
);

CREATE table code(
    codeNumber number(1,0), --I assumed that the code was only 1 digit (as all the examples entities are 1 digit)
    fine number(7,0), -- this is just a guess that the max fine is 7 digits
    CONSTRAINT code_PK primary key(codeNumber)
);

CREATE table ticket(
    ticketNumber number(5,0),
    ticketDate char(8), -- NOTE: I decided to use char instead of date a date includes hours, which was throwing the date off
    studentID number(5,0),
    codeNumber number(1,0),
    CONSTRAINT ticket_PK primary key(ticketNumber),
    CONSTRAINT ticket_FK1 foreign key(studentID) REFERENCES student(studentID),
    CONSTRAINT ticket_FK2 foreign key(codeNumber) REFERENCES code(codeNumber)
);

INSERT into student values(38249, 'Brown', 'Thomas', '111-7804');
INSERT into student values(82453, 'Green', 'Sally', '391-1689');

INSERT into license values('BRY 123', 'FL', 38249);
INSERT into license values('TRE 141', 'AL', 82453);

INSERT into code values(1, 15);
INSERT into code values(2, 25);
INSERT into code values(3, 100);

INSERT into ticket values(15634, '10/17/12', 38249, 2); --brown's tickets
INSERT into ticket values(16017, '11/13/12', 38249, 1);
INSERT into ticket values(14987, '10/05/12', 82453, 3); -- Green's tickets
INSERT into ticket values(16293, '11/18/12', 82453, 1);
INSERT into ticket values(17892, '12/13/12', 82453, 2);

SELECT * FROM student;
SELECT * FROM license;
SELECT * FROM code;
SELECT * FROM ticket;
