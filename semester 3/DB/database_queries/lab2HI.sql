
--GROUP BY
--Group animals by SpeciesID and return the COUNT of animals, MAX age, 
--and AVG age per species — show only species with COUNT >= 2.
SELECT SpeciesID,COUNT(AnimalID) AS AnimalCount,MAX(Age) AS MaxAge,AVG(Age) AS AvgAge
FROM Animals
GROUP BY SpeciesID
HAVING COUNT(AnimalID) >= 2

--Group Donations by VisitorID and return the SUM(Amount) per visitor — show 
--only visitors whose SUM(Amount) is greater than the average donation sum across
--all visitors (use a subquery in HAVING that computes the average). (GROUP BY, HAVING
--with subquery, SUM, AVG)
SELECT VisitorID,SUM(Amount) AS TotalDonations
FROM Donations
GROUP BY VisitorID
HAVING SUM(Amount) > (
SELECT AVG(VisitorTotal)
FROM (
SELECT VisitorID,SUM(Amount) AS VisitorTotal
FROM Donations
GROUP BY VisitorID
) AS Sub
)

--For each Habitat, show the total number of animals and keep only habitats whose total 
--animals exceed the maximum number of animals found in any habitat of climate 'Arid' 
SELECT H.HabitatID,H.Name AS HabitatName,COUNT(A.AnimalID) AS AnimalCount
FROM Habitats H
JOIN Species S ON H.HabitatID = S.HabitatID
JOIN Animals A ON S.SpeciesID = A.SpeciesID
GROUP BY H.HabitatID, H.Name
HAVING COUNT(A.AnimalID) > (
SELECT MAX(AnimalCount)
FROM (
SELECT H2.HabitatID,COUNT(A2.AnimalID) AS AnimalCount
FROM Habitats H2
JOIN Species S2 ON H2.HabitatID = S2.HabitatID
JOIN Animals A2 ON S2.SpeciesID = A2.SpeciesID
WHERE H2.Climate = 'Arid'
GROUP BY H2.HabitatID
) AS AridTotals
)

--Group Shop purchases by ProductName and return DISTINCT ProductName and the total revenue
--(Price * Stock) — show only products whose total revenue BETWEEN two values. 

SELECT DISTINCT ProductName,SUM(Price * Stock) AS TotalRevenue
FROM Shop
GROUP BY ProductName
HAVING SUM(Price * Stock) BETWEEN 1000 AND 5000;


--ANY and ALL

--ANY: Find Animals whose Age is greater than ANY age from a list of animals in SpeciesID = 2.
SELECT A.Name, A.Age
FROM Animals A
WHERE A.Age > ANY(
SELECT A.Age
FROM Animals A
WHERE A.SpeciesID=2
)
--rewrite with in
SELECT A.Name,A.Age
FROM Animals A
WHERE A.AnimalID IN
(
SELECT A1.AnimalID
FROM Animals A1
WHERE A1.Age>
(
SELECT MIN(A2.Age)
FROM Animals A2
WHERE A2.SpeciesID=2
)
)

--Find Staff whose HireDate is earlier than ALL hire dates of staff with role 'Guide'. (ALL)
SELECT S.FirstName,S.HireDate
FROM Staff S
WHERE S.HireDate < ALL
(
SELECT S2.HireDate
FROM Staff S2
WHERE S2.Role='Guide'
)

--rewrite with agr
SELECT S.FirstName
FROM Staff S
WHERE S.HireDate <
(SELECT MIN(S2.HireDate)
FROM Staff S2
WHERE S2.Role='Guide')


--Find Species whose average Animal age is greater than ALL species' average ages.
SELECT S.SpeciesID, S.Name
FROM Species S
JOIN Animals A ON A.SpeciesID = S.SpeciesID
GROUP BY S.SpeciesID, S.Name
HAVING AVG(A.Age) > ALL (
SELECT AVG(A2.Age)
FROM Animals A2
GROUP BY A2.SpeciesID
);
--rewrite with agr
SELECT S.SpeciesID, S.Name
FROM Species S
JOIN Animals A ON A.SpeciesID = S.SpeciesID
GROUP BY S.SpeciesID, S.Name
HAVING AVG(A.Age) > (
SELECT MAX(AvgAge)
FROM (
SELECT AVG(A2.Age) AS AvgAge
FROM Animals A2
GROUP BY A2.SpeciesID
)as Sub
);

--Find Donations whose Amount is greater than ANY amount in a specific set of 
--donation amounts returned by a subquery; rewrite the equivalent using IN / NOT IN. (ANY / IN)
SELECT D1.VisitorID,D1.Amount
FROM Donations D1
WHERE D1.Amount > ANY (
SELECT D2.Amount
FROM Donations D2
WHERE D2.VisitorID = 5  
);

--rewrite with in
SELECT D1.VisitorID,D1.Amount
FROM Donations D1
WHERE D1.Amount IN (
SELECT D2.Amount
FROM Donations D2
WHERE D2.VisitorID = 5 AND D2.Amount < D1.Amount
);

--extra
--Show the top 5 most expensive Shop products ordered by Price DESC 
--(use TOP and ORDER BY). (TOP + ORDER BY)
SELECT TOP 5 *
FROM Shop
ORDER BY Price DESC;


--List Animals ordered by Age DESC, then Name ASC. (ORDER BY
SELECT *
FROM Animals
ORDER BY Age DESC, Name ASC

--Show TOP 3 species by number of animals (use TOP and GROUP BY). (TOP + GROUP BY)
SELECT TOP 3 S.SpeciesID, S.Name, COUNT(A.AnimalID) AS AnimalCount
FROM Species S
JOIN Animals A ON S.SpeciesID = A.SpeciesID
GROUP BY S.SpeciesID, S.Name
ORDER BY COUNT(A.AnimalID) DESC


--Return TOP 1 visitor by total donation amount. (TOP + aggregation)
SELECT TOP 1 V.VisitorID, V.FirstName, V.LastName, SUM(D.Amount) AS TotalDonations
FROM Visitors V
JOIN Donations D ON V.VisitorID = D.VisitorID
GROUP BY V.VisitorID, V.FirstName, V.LastName
ORDER BY SUM(D.Amount) DESC
