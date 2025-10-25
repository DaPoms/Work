DROP table student;
DROP table license;
DROP table code;
DROP table ticket;

CREATE table student(
    studentID char(5),
    lName varchar2(20),
    fName varchar2(20),
    phoneNumber char(8), --requires format: 123-4567
    CONSTRAINT captain_PK primary key(studentID)
);

CREATE table license(
    licenseNumber char(7), -- Requires this format: 'XYZ 123'
    licenseState char(2),
    studentID char(5),
    CONSTRAINT license_PK primary key(licenseNumber),
    CONSTRAINT license_FK foreign key(studentID) REFERENCES student(studentID)
);

CREATE table code(
    codeNumber number(1,0), --I assumed that the code was only 1 digit (as all the examples entities are 1 digit)
    fine number(7,0), -- this is just a guess that the max fine is 7 digits
    CONSTRAINT code_PK primary key(codeNumber)
);

CREATE table ticket(
    ticketNumber char(5)
);
