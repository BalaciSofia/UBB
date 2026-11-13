CREATE TABLE [Tables] (
	TableID int IDENTITY (1, 1) NOT NULL PRIMARY KEY,
	Name nvarchar (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
)
GO

CREATE TABLE TestRuns (
	TestRunID int IDENTITY (1, 1) NOT NULL PRIMARY KEY ,
	[Description] nvarchar (2000) COLLATE SQL_Latin1_General_CP1_CI_AS NULL ,
	StartAt datetime NULL ,
	EndAt datetime NULL 
)
GO


CREATE TABLE [Views] (
	ViewID int IDENTITY (1, 1) NOT NULL PRIMARY KEY,
	Name nvarchar (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
)
GO

CREATE TABLE TestRunViews (
	TestRunID int NOT NULL,
	ViewID int NOT NULL,
	StartAt datetime NOT NULL ,
	EndAt datetime NOT NULL,
	FOREIGN KEY (TestRunID) REFERENCES TestRuns(TestRunId),
	FOREIGN KEY (ViewID) REFERENCES [Views](ViewID),
	PRIMARY KEY (TestRunID,ViewID)
)
GO



CREATE TABLE TestRunTables (
	TestRunID int NOT NULL ,
	TableID int NOT NULL ,
	StartAt datetime NOT NULL ,
	EndAt datetime NOT NULL ,
	FOREIGN KEY (TestRunID) REFERENCES TestRuns(TestRunID),
	FOREIGN KEY (TableID) REFERENCES [Tables](TableID),
	PRIMARY KEY(TestRunID, TableID)
) 
GO

CREATE TABLE Tests (
	TestID int IDENTITY (1, 1) NOT NULL PRIMARY KEY,
	Name nvarchar (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
)
GO

CREATE TABLE TestTables (
	TestID int NOT NULL ,
	TableID int NOT NULL ,
	NoOfRows int NOT NULL ,
	Position int NOT NULL,
	FOREIGN KEY (TableID) REFERENCES [Tables](TableID),
	FOREIGN KEY (TestID) REFERENCES Tests(TestID),
	PRIMARY KEY (TestID, TableID)
)
GO

CREATE TABLE TestViews (
	TestID int NOT NULL,
	ViewID int NOT NULL,
	FOREIGN KEY (TestID) REFERENCES Tests(TestID),
	FOREIGN KEY (ViewID) REFERENCES [Views](ViewID),
	PRIMARY KEY(TestID,ViewID)
) 
GO

INSERT INTO [Tables] (Name)
values
('Food'),
('Animals'),
('StaffHabitat');

CREATE VIEW View_Food AS
	SELECT FoodID, Name, Type, QuantityInStock
	FROM Food;
go

CREATE VIEW View_Animals_PerSpecies AS
SELECT S.Name AS SpeciesName, COUNT(*) AS AnimalCount
FROM Animals A
INNER JOIN Species S ON A.SpeciesID = S.SpeciesID
GROUP BY S.Name;

CREATE VIEW View_Staff as
	select S.FirstName as Employee, S.Role, SH.AssignedDate, H.Name as Habitat
	from Staff S
	inner join StaffHabitat SH on S.StaffID=SH.StaffID
	inner join Habitats H on SH.HabitatID=H.HabitatID
go

select * from View_Food
select * from View_Animals_PerSpecies
select * from View_Staff


INSERT INTO [Views] (Name)
VALUES
('View_Food'),
('View_Animals_PerSpecies'),
('View_Staff');


INSERT INTO Tests (Name)
VALUES
('delete_from_table'),
('insert_into_table'),
('select_from_views');

select * from Tests

INSERT INTO TestViews (TestID, ViewID)
SELECT 3, ViewID FROM [Views];

INSERT INTO TestTables (TestID, TableID, NoOfRows, Position)
VALUES
(1, 3, 1000, 1),  -- StaffHabitat
(1, 2, 1000, 2),  -- Animals
(1, 1, 1000, 3),  -- Food
(2, 1, 1000, 1),  -- Food
(2, 2, 1000, 2),  -- Animals
(2, 3, 1000, 3);  -- StaffHabitat


