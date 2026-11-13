use ZooManagement
select * from Species
select * from Animals
select * from Food 
--ta Species aid=speciesid a2=speciescode(unique)
--tb Food bid=foodid b2=quantity
--tc Animals cid=animalid aid=speciesid bid=foodid

DELETE FROM Animals;
DELETE FROM Species;
DELETE FROM Food;

DBCC CHECKIDENT ('Animals', RESEED, 0);
DBCC CHECKIDENT ('Species', RESEED, 0);
DBCC CHECKIDENT ('Food', RESEED, 0);
GO

WITH Numbers AS (
    SELECT TOP (10000)
        ROW_NUMBER() OVER (ORDER BY (SELECT NULL)) AS n
    FROM sys.objects a
    CROSS JOIN sys.objects b
)
INSERT INTO Food (Name, Type, QuantityInStock)
SELECT
    CONCAT('Food_', n),
    CASE WHEN n % 100 = 0 THEN 'Meat' ELSE 'Plant' END,
    100 + n
FROM Numbers;
GO

WITH Numbers AS (
    SELECT TOP (10000)
        ROW_NUMBER() OVER (ORDER BY (SELECT NULL)) AS n
    FROM sys.objects a
    CROSS JOIN sys.objects b
)
INSERT INTO Species (SpeciesCode, Name, Classification, DietType, HabitatID)
SELECT
    100000 + n,
    CONCAT('Species_', n),
    'Mammal',
    CASE WHEN n % 100 = 0 THEN 'Carnivore' ELSE 'Herbivore' END,
    ((n - 1) % 6) + 1
FROM Numbers;
GO

INSERT INTO Animals (Name, Age, Gender, SpeciesID, FoodID)
SELECT
    CONCAT('Animal_', s.SpeciesID),
    (s.SpeciesID % 20) + 1,
    CASE WHEN s.SpeciesID % 2 = 0 THEN 'M' ELSE 'F' END,
    s.SpeciesID,
    f.FoodID
FROM Species s
JOIN Food f
    ON f.FoodID = s.SpeciesID;
GO


INSERT INTO Habitats (Name, Climate)
VALUES
('Savannah', 'Dry'),
('Forest', 'Temperate'),
('Arctic', 'Cold'),
('Mountains', 'Cold'),
('Swamp', 'Humid'),
('Grassland', 'Temperate');


--clustered index scan
SELECT *
FROM Species;

--clustered index seek
SELECT *
FROM Species
WHERE SpeciesID = 3;

--non clustered indx scan
SELECT SpeciesCode
FROM Species;

--non clustered idx seek
SELECT SpeciesCode
FROM Species
WHERE SpeciesCode = 1005;

--non clust idx seek ->key lookup(clustered)
SELECT Name, Classification
FROM Species
WHERE SpeciesCode = 1005;




------b------
DROP INDEX IX_Food_Type ON Food;
--cl idx scan
SELECT *
FROM Food
WHERE QuantityInStock=1050;
--     ||
--     \/
--improvement 
CREATE NONCLUSTERED INDEX IX_Food_Quantity
ON Food(QuantityInStock);
--     ||
--     \/
--non cl idx seek key lookup
SELECT *
FROM Food
WHERE QuantityInStock=1050;

-----c-------
go

--view
drop view vw_AnimalsWithDetails

CREATE VIEW vw_AnimalsWithDetails
AS
SELECT
    a.Name AS AnimalName,
    f.Name AS FoodName
FROM Animals a
JOIN Food f ON a.FoodID = f.FoodID;

drop index IX_Food on Food
drop index IX_Animals on Animals

SELECT *
FROM vw_AnimalsWithDetails
WHERE FoodName = 'Food_100';

CREATE NONCLUSTERED INDEX IX_Food
ON Food(Name)

Create nonclustered index IX_Animals
on Animals(Foodid)
include (Name)
