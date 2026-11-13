use ZooManagemnt;

--delete all donations under 30 and before 16.06.2024
DELETE FROM Donations
WHERE Amount < 50 AND DonationDate < '2024-06-16' 
select * from Donations

--delete visitors that did not donate 
select * from Visitors
DELETE FROM Visitors
WHERE VisitorID NOT IN(
SELECT VisitorID
FROM Donations
);
select * from Visitors