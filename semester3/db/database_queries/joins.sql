use ZooManagement;

--list each animal it s species and the food it eats
--joins 3 tables
--INNER JOIN
SELECT A.Name,S.Name,F.Name
FROM Animals A 
INNER JOIN
Species S on A.SpeciesID=S.SpeciesID
INNER JOIN 
Food F on A.FoodID=F.FoodID 

--list all Habitats and any Events scheduled for them including habitats with no events 
SELECT H.Name as HabitatName, E.Name as EventName
FROM Habitats H
LEFT JOIN
Events E  on H.HabitatID=E.HabitatID


--list all Visitors who made donations and any shop purchases they made
--visitors with purchases but no donations still appear
SELECT * FROM Visitors
INSERT INTO Visitors(FirstName,LastName,Age)
Values('Richard','The first',33);

Select * from Shop
INSERT INTO Shop(ProductName,Price,Stock,CustomerID)
values('Magnet',3.99 ,400 ,17);

SELECT V.FirstName,D.Amount AS DonationAmount,S.ProductName
FROM Donations D
RIGHT JOIN Visitors V on D.VisitorID = V.VisitorID
RIGHT JOIN Shop S on V.VisitorID = S.CustomerID

--Retrieve a complete list of Staff and StaffHabitat assignments so you can 
--see staff with no assignments and assignments with missing staff
SELECT S.FirstName,SH.HabitatID
FROM Staff S
FULL JOIN
StaffHabitat SH on S.StaffID=SH.StaffID

--For each Staff member, list the Habitat names they are assigned to and 
--count how many animals are in those habitats
SELECT S.FirstName,H.Name AS HabitatName,COUNT(A.AnimalID) AS AnimalCount
FROM Animals A
RIGHT JOIN Species Sp on A.SpeciesID = Sp.SpeciesID
RIGHT JOIN Habitats H on Sp.HabitatID = H.HabitatID
RIGHT JOIN StaffHabitat SH on H.HabitatID = SH.HabitatID
RIGHT JOIN Staff S on SH.StaffID = S.StaffID
GROUP BY S.FirstName, H.Name;

-- joins 2 many to many 
--Show all zoo staff members who are assigned to habitats where animals perform events.
--Include the staff name, habitat name, animal name, event name, and performance duration.
SELECT S.FirstName + ' ' + S.LastName AS StaffName,H.Name AS HabitatName,A.Name AS AnimalName,E.Name AS EventName,P.Duration
FROM Staff AS S
JOIN StaffHabitat AS SH ON S.StaffID = SH.StaffID
JOIN Habitats AS H ON SH.HabitatID = H.HabitatID
JOIN Events AS E ON H.HabitatID = E.HabitatID
JOIN Performs AS P ON E.EventID = P.EventID
JOIN Animals AS A ON P.AnimalID = A.AnimalID
ORDER BY StaffName, HabitatName;
