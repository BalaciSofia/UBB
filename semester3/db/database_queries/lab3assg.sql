-------------------------------------------
CREATE PROCEDURE ExpandStaffLastName
AS
BEGIN
    ALTER TABLE Staff
    ALTER COLUMN LastName VARCHAR(200);
END;
Go

CREATE PROCEDURE ShrinkStaffLastName
AS
BEGIN
    ALTER TABLE Staff
    ALTER COLUMN LastName VARCHAR(100);
END;
go
---------------------------------------------

CREATE PROCEDURE AddColumnPhoneNumb
AS
BEGIN
    ALTER TABLE Staff
    ADD PhoneNumber VARCHAR(20) NULL;
END;
go

CREATE PROCEDURE RemoveColumnPhoneNumb
AS
BEGIN
    ALTER TABLE Staff
    DROP COLUMN PhoneNumber;
END;
go

----------------------------------------------

CREATE PROCEDURE AddDefaultPhoneNumb
AS
BEGIN
    ALTER TABLE Staff
    ADD CONSTRAINT df_staff_phone DEFAULT 'Unknown' FOR PhoneNumber;
END;
go

CREATE PROCEDURE RemoveDefaultPhoneNumb
AS
BEGIN
    ALTER TABLE Staff
    DROP CONSTRAINT df_staff_phone;
END;
go

-------------------------------------------------

CREATE PROCEDURE AddPK
AS
BEGIN
    ALTER TABLE TempPKTable
    ADD CONSTRAINT pk_temp PRIMARY KEY (ID);
END;
go

CREATE PROCEDURE RemovePK
AS
BEGIN
    BEGIN
        ALTER TABLE TempPKTable
        DROP CONSTRAINT pk_temp;
    END
END;
go


---------------------------------------------------

CREATE PROCEDURE AddUniqueConstraint
AS
BEGIN
    ALTER TABLE Staff
    ADD CONSTRAINT uq_staff_first UNIQUE (FirstName);
END;
go

CREATE PROCEDURE RemoveUniqueConstraint
AS
BEGIN
    ALTER TABLE Staff
    DROP CONSTRAINT uq_staff_first;
END;
go
-----------------------------------------------------

CREATE PROCEDURE AddFK
AS
BEGIN
    ALTER TABLE StaffHabitat
    ADD CONSTRAINT fk_staffhab_hab FOREIGN KEY (HabitatID)
    REFERENCES Habitats(HabitatID);
END;
go

CREATE PROCEDURE RemoveFK
AS
BEGIN
    ALTER TABLE StaffHabitat
    DROP CONSTRAINT fk_staffhab_hab;
END;
go

-------------------------------------------------------

CREATE PROCEDURE CreateNewTable
AS
BEGIN
    CREATE TABLE NewTable(
        ID INT PRIMARY KEY,
    );
END;
go

CREATE PROCEDURE DropNewTable
AS
BEGIN
    DROP TABLE NewTable;
END;
go


CREATE PROCEDURE MainVersion
    @targetVersion INT
AS
BEGIN
    DECLARE @current INT;
    SELECT @current = versionNo FROM VersionHandler;

    IF @targetVersion < 0 OR @targetVersion > 7
    BEGIN
        PRINT 'ERROR: Version does not exist.';
        RETURN;
    END;

    IF @current = @targetVersion
    BEGIN
        PRINT 'Database already at requested version.';
        RETURN;
    END;
    IF @current < @targetVersion
    BEGIN
        WHILE @current < @targetVersion
        BEGIN
            SET @current = @current + 1;

            IF @current = 1 EXEC ExpandStaffLastName;
            ELSE IF @current = 2 EXEC AddColumnPhoneNumb;
            ELSE IF @current = 3 EXEC AddDefaultPhoneNumb;
            ELSE IF @current = 4 EXEC AddPK;
            ELSE IF @current = 5 EXEC AddUniqueConstraint;
            ELSE IF @current = 6 EXEC AddFK;
            ELSE IF @current = 7 EXEC CreateNewTable;

            UPDATE VersionHandler SET versionNo = @current;

        END
    END
    ELSE
    BEGIN
        WHILE @current > @targetVersion
        BEGIN

            IF @current = 1 EXEC ShrinkStaffLastName;
            ELSE IF @current = 2 EXEC RemoveColumnPhoneNumb;
            ELSE IF @current = 3 EXEC RemoveDefaultPhoneNumb;
            ELSE IF @current = 4 EXEC RemovePK;
            ELSE IF @current = 5 EXEC RemoveUniqueConstraint;
            ELSE IF @current = 6 EXEC RemoveFK;
            ELSE IF @current = 7 EXEC DropNewTable;

            SET @current = @current - 1;

            UPDATE VersionHandler SET versionNo = @current;

        END
    END
END;
go


exec MainVersion 0
select * from VersionHandler;
select * from Staff
select * from TempPKTable

select * from NewTable
