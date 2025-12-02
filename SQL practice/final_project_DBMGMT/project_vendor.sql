CREATE table region(
    region_ID number(8,0),
    regionName varchar2(20),
    CONSTRAINT region_PK primary key(region_ID)
);

CREATE table country(
    country_ID number(8,0),
    region_ID number(8,0) NOT NULL, -- every country must have a region
    country_Name varchar2(20),
    CONSTRAINT country_PK primary key(country_ID),
    CONSTRAINT country_FK1 foreign key(region_ID) REFERENCES region(region_ID)
);

CREATE table employee(
    emp_ID number(8,0),
    emp_firstName varchar2(20),
    emp_lastName varchar2(20),
    CONSTRAINT employee_PK primary key(emp_ID)
);

CREATE table countryManager(
    CM_Emp_ID number(8,0),
    country_ID number(8,0) NOT NULL, -- every countryManager must have a country they manage
    CONSTRAINT countryManager_PK primary key (CM_Emp_ID),
    CONSTRAINT countryManager_FK1 foreign key (CM_Emp_ID) REFERENCES employee(emp_ID),
    CONSTRAINT countryManager_FK2 foreign key (country_ID) REFERENCES country(country_ID)
);

CREATE table developmentManager(
	DM_Emp_ID number(8,0),
    CM_Supervisor_ID number(8,0) NOT NULL, -- Every development manager must have a supervisor
    CONSTRAINT developmentManager_PK primary key (DM_Emp_ID),
    CONSTRAINT developmentManager_FK1 foreign key (DM_Emp_ID) REFERENCES employee(emp_ID),
    CONSTRAINT developmentManager_FK2 foreign key (CM_Supervisor_ID) REFERENCES countryManager(CM_Emp_ID)
);

CREATE table developer(
    D_Emp_ID number(8,0),
    DM_Supervisor_ID number(8,0), -- Every developer must have a supervisor
    CONSTRAINT developer_PK primary key (D_Emp_ID),
    CONSTRAINT developer_FK1 foreign key (D_Emp_ID) REFERENCES employee(emp_ID),
    CONSTRAINT developer_FK2 foreign key (DM_Supervisor_ID) REFERENCES developmentManager(DM_Emp_ID)
);
CREATE table seniorDeveloper(
    SD_Emp_ID number(8,0),
    CONSTRAINT seniorDeveloper_PK primary key (SD_Emp_ID),
    CONSTRAINT seniorDeveloper_FK1 foreign key (SD_Emp_ID) REFERENCES developer(D_Emp_ID)
);
CREATE table juniorDeveloper(
    JD_Emp_ID number(8,0),
    SD_Mentor_ID number(8,0) NOT NULL, -- Every junior dev must have a mentor
    CONSTRAINT juniorDeveloper_PK primary key (JD_Emp_ID),
    CONSTRAINT juniorDeveloper_FK1 foreign key (JD_Emp_ID) REFERENCES developer(D_Emp_ID),
    CONSTRAINT juniorDeveloper_FK2 foreign key (SD_Mentor_ID) REFERENCES seniorDeveloper(SD_Emp_ID)
);

CREATE table wizardDeveloper(
    WD_Emp_ID number(8,0),
    CONSTRAINT wizardDeveloper_PK primary key (WD_Emp_ID),
    CONSTRAINT wizardDeveloper_FK1 foreign key (WD_Emp_ID) REFERENCES developer(D_Emp_ID)
);

CREATE table team(
	team_ID number(8,0),
    SD_Lead_Emp_ID number(8,0) NOT NULL, --Team must have lead
    SD_Deputy_Emp_ID number(8,0) NOT NULL, -- Team must have deputy
    team_Name varchar2(40),
    team_Start_Date date,
    team_End_Date date,
    CONSTRAINT team_PK primary key(team_ID),
    CONSTRAINT team_FK1 foreign key(SD_Lead_Emp_ID) REFERENCES seniorDeveloper(SD_Emp_ID),
    CONSTRAINT team_FK2 foreign key(SD_Deputy_Emp_ID) REFERENCES seniorDeveloper(SD_Emp_ID)
);

CREATE table membership(
    D_Emp_ID number(8,0), --don't need to explicitly state NOT NULL as primary keys are inately set as NOT NULL 
    team_ID number(8,0),
    joined date,
    left date,
    CONSTRAINT membership_PK primary key (D_Emp_ID, team_ID),
    CONSTRAINT membership_FK1 foreign key (D_Emp_ID) REFERENCES developer(D_Emp_ID),
    CONSTRAINT membership_FK2 foreign key (team_ID) REFERENCES team(team_ID)
);

CREATE table project(
    proj_ID number(8,0),
    team_ID number(8,0) NOT NULL, -- A project must have a team
    proj_Start_Date date,
    proj_End_Date date,
    CONSTRAINT project_PK primary key (proj_ID),
    CONSTRAINT project_FK foreign key (team_ID) REFERENCES team(team_ID) 
);

CREATE table assignment(
    D_Emp_ID number(8,0),
    proj_ID number(8,0),
    score number(5,0),
    hours number(5,0),
    rate number(5,0),
    CONSTRAINT assignment_PK primary key (D_Emp_ID, proj_ID),
    CONSTRAINT assignment_FK1 foreign key (D_Emp_ID) REFERENCES developer(D_Emp_ID),
    CONSTRAINT assignment_FK2 foreign key (proj_ID) REFERENCES project(proj_ID)
);
