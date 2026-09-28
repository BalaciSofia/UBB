USE mockZooManagement;

--A1
--fix:SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
BEGIN TRANSACTION;
SELECT StaffID, FirstName, LastName, Role
FROM Staff
WHERE Role = 'Maid';

--B
BEGIN TRANSACTION;
    INSERT INTO Staff (FirstName, LastName, Role, HireDate)
    VALUES ('Ghost', 'User', 'Maid', '2026-01-01');
COMMIT TRANSACTION;

--A2
SELECT StaffID, FirstName, LastName, Role
FROM Staff
WHERE Role = 'Maid';
COMMIT TRANSACTION;

SELECT * FROM Habitats;
SELECT * FROM Staff;
SELECT * FROM StaffHabitat;

