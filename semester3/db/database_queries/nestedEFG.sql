use ZooManagement;

--IN
--Find all Animals whose SpeciesID is IN the set of species that live 
--in the same habitat as the “Rainforest Dome”.
SELECT A.Name
FROM Animals A
WHERE A.SpeciesID IN
(SELECT S.SpeciesID
FROM Species S
RIGHT JOIN
Habitats H on H.HabitatID=S.HabitatID
Where H.Name='Rainforest Dome')

--Find all Staff who are assigned to any Habitat whose HabitatID is IN the set 
--returned by a subquery that itself filters Habitats by area > (SELECT AVG(AreaSize)
--FROM Habitats WHERE Climate = 'Humid')
SELECT Sh.StaffID
FROM StaffHabitat Sh
WHERE Sh.HabitatID IN 
(
SELECT H.HabitatID
FROM Habitats H
WHERE H.AreaSize > 
(SELECT AVG(AreaSize)
FROM Habitats
WHERE Climate = 'Humid')
)

--EXISTS
--List Habitats for which EXISTS at least one Species that is a 'carnivore'.
SELECT H.Name
FROM Habitats H
WHERE EXISTS 
(SELECT 1
FROM Species S
WHERE S.HabitatID = H.HabitatID AND S.DietType = 'carnivore'
)

--Select Visitors for whom EXISTS a Donation with an Amount >= ALL donations
--made in the same month (use EXISTS with a correlated subquery). (EXISTS with correlation)

SELECT DISTINCT V.FirstName, V.LastName
FROM Visitors V
WHERE EXISTS 
(
SELECT 1
FROM Donations D1
WHERE D1.VisitorID = V.VisitorID
AND D1.Amount >= ALL 
(
SELECT D2.Amount
FROM Donations D2
WHERE MONTH(D2.DonationDate) = MONTH(D1.DonationDate)
)
)

--FROM
--From a derived table that returns SpeciesID and the count of Animals per species, 
--select species with more than 2 animals.

SELECT S.SpeciesID, S.AnimalCount
FROM 
(
SELECT SpeciesID, COUNT(AnimalID) AS AnimalCount
FROM Animals
GROUP BY SpeciesID
) AS S
WHERE S.AnimalCount > 2

--Build a derived table of monthly donation totals (subquery in FROM) and then select
--months where the total exceeds the average monthly donation across all months.

SELECT D.MonthNum, D.MonthTotal
FROM (
SELECT MONTH(DonationDate) AS MonthNum,SUM(Amount) AS MonthTotal
FROM Donations
GROUP BY MONTH(DonationDate)
) AS D
WHERE D.MonthTotal > 
(
SELECT AVG(MonthTotal)
FROM (
SELECT MONTH(DonationDate) AS MonthNum,SUM(Amount) AS MonthTotal
FROM Donations
GROUP BY MONTH(DonationDate)
) AS MonthlyTotals
)


