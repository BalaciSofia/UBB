USE mockZooManagement;

--A1
--fix:SET DEADLOCK_PRIORITY HIGH;
--or lock them in the same order
BEGIN TRANSACTION;
    UPDATE Staff SET Role = 'Director' WHERE StaffID = 7;

--B1
BEGIN TRANSACTION;
    UPDATE Habitats SET AreaSize = 600.00 WHERE HabitatID = 9;

--A2
UPDATE Habitats SET AreaSize = 700.00 WHERE HabitatID = 9;

--B2
UPDATE Staff SET Role = 'Keeper' WHERE StaffID = 7;

--A3
COMMIT TRANSACTION;

--
select * from Habitats
select * from Staff