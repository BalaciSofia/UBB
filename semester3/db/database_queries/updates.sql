use ZooManagement;

--insert that violates integrity
--habitatID 9 does not exist
INSERT INTO Species(Name, Classification, DietType, HabitatID)
VALUES('Snake','Reptile','carnivore',9);

--increase price by 10% for shop products with Stock>100
UPDATE Shop
SET Price=Price*1.1
WHERE Stock > 100;
select * from Shop

--set the quantity of all foods that are dry or their quantity is <1000 to 0
UPDATE Food 
SET QuantityInStock=0
WHERE Name LIKE '%Dry%' OR QuantityInStock BETWEEN 0 and 1000;
select * from Food

--change the role to Senior ZooKeeper to all staff hired before 2020 and current role is a zooKeeper
UPDATE Staff
SET Role='Senior Zookeeper'
WHERE Role='Zookeeper' AND HireDate < '2020-01-01'
select * from Staff