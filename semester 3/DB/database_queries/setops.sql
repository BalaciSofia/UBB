use ZooManagement;

--UNION--
--list all animals and shop product names that include 'Snow' or 'Safari'
SELECT A.Name
FROM Animals A
WHERE A.Name LIKE '%Snow%' or A.Name LIKE'%Safari%'
UNION 
SELECT S.ProductName
FROM Shop S
WHERE S.ProductName LIKE '%Snow%' or S.ProductName LIKE '%Safari%'

--list visitors first name who either purchased from the Shop OR made a Donation
SELECT V.FirstName
FROM Visitors V, Shop S
WHERE V.VisitorID=S.CustomerID
UNION
SELECT V.FirstName
FROM Visitors V,Donations D
WHERE V.VisitorID=D.VisitorID


--INTERSECTION--
--list visitors that apear in shop and in donations
SELECT V.FirstName
FROM Visitors V,Shop S
WHERE V.VisitorID = S.CustomerID
INTERSECT
SELECT V.FirstName
FROM Visitors V,Donations D
WHERE V.VisitorID = D.VisitorID

--list names present in both Species and Animals
SELECT S.Name
FROM Species S
WHERE S.Name IN
(SELECT A.Name
FROM Animals A)


--EXCEPT--
--list visitors that bought form the shop but did not donate
SELECT V.FirstName
FROM Visitors V,Shop S
WHERE V.VisitorID = S.CustomerID
EXCEPT
SELECT V.FirstName
FROM Visitors V,Donations D
WHERE V.VisitorID = D.VisitorID

--list habitats that don t have any events or are interactive with the zookepers
Select H.Name
FROM Habitats H
WHERE H.HabitatID NOT IN
(SELECT E.HabitatID
FROM Events E
WHERE E.Description NOT LIKE '%zookeepers%')