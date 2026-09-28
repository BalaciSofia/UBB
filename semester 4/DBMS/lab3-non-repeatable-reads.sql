USE mockZooManagement;
--A1
--fix:SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
BEGIN TRANSACTION;
SELECT StaffID, FirstName, LastName, Role
FROM Staff
WHERE StaffID = 7;

--B
BEGIN TRANSACTION;
    UPDATE Staff
    SET Role = 'Maid'
    WHERE StaffID = 7;
COMMIT TRANSACTION;

--A2
SELECT StaffID, FirstName, LastName, Role
FROM Staff
WHERE StaffID = 7;
COMMIT TRANSACTION;


select * from Habitats
select * from Staff