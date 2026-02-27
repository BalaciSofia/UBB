use ZooManagement


drop Procedure RunDeletePhase
drop procedure RunInsertPhase
drop procedure RunSelectPhase
drop procedure RunFullTest

go
CREATE PROCEDURE RunDeletePhase
    @TestID INT
AS
BEGIN
    DECLARE 
        @TableName NVARCHAR(100),
        @SQL NVARCHAR(MAX);

    DECLARE table_cursor CURSOR FOR
        SELECT t.[Name]
        FROM [Tables] t
        INNER JOIN TestTables tt ON t.TableID = tt.TableID
        WHERE tt.TestID = @TestID
        ORDER BY tt.Position ASC; 

    OPEN table_cursor;
    FETCH NEXT FROM table_cursor INTO @TableName;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        SET @SQL = 'DELETE FROM ' + QUOTENAME(@TableName) + ';';
        EXEC(@SQL);

        FETCH NEXT FROM table_cursor INTO @TableName;
    END
    CLOSE table_cursor;
    DEALLOCATE table_cursor;
END
GO


----------------------------------------------------------------------------------------------------------------------

CREATE PROCEDURE RunInsertPhase
    @TestID INT,
    @TestRunID INT
AS
BEGIN
    DECLARE 
        @TableName NVARCHAR(100),
        @TableID INT,
        @NoOfRows INT,
        @StartTime DATETIME,
        @EndTime DATETIME,
        @i INT,
        @SQL NVARCHAR(MAX);

    DECLARE table_cursor CURSOR FOR
        SELECT t.Name, t.TableID, tt.NoOfRows
        FROM [Tables] t
        INNER JOIN TestTables tt ON t.TableID = tt.TableID
        WHERE tt.TestID = @TestID
        ORDER BY tt.Position ASC; 

    OPEN table_cursor;
    FETCH NEXT FROM table_cursor INTO @TableName, @TableID, @NoOfRows;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        SET @StartTime = GETDATE();   
        --table food
        IF @TableName = 'Food'
        BEGIN
            SET @i = 1;
            WHILE @i <= @NoOfRows
            BEGIN
                INSERT INTO Food (Name, Type, QuantityInStock)
                VALUES ('Food' + CAST(@i AS NVARCHAR), 'Type', 100);

                SET @i += 1;
            END
        END
        --table animals
        ELSE IF @TableName = 'Animals'
        BEGIN
            DECLARE @FoodID INT = (SELECT MIN(FoodID) FROM Food);
            DECLARE @SpeciesID INT = (SELECT MIN(SpeciesID) FROM Species);

            SET @i = 1;
            WHILE @i <= @NoOfRows
            BEGIN
                INSERT INTO Animals (Name, Age, Gender, SpeciesID, FoodID)
                VALUES ('Animal' + CAST(@i AS NVARCHAR), 5, 'F', @SpeciesID, @FoodID);

                SET @i += 1;
            END
        END
        --table staffhabitat
        ELSE IF @TableName = 'StaffHabitat'
        BEGIN
            DECLARE @StaffID INT = (SELECT MIN(StaffID) FROM Staff);
            DECLARE @HabitatID INT = (SELECT MIN(HabitatID) FROM Habitats);

            SET @i = 1;
            WHILE @i <= @NoOfRows
            BEGIN
                INSERT INTO StaffHabitat (StaffID, HabitatID, AssignedDate)
                VALUES (@StaffID, @HabitatID, GETDATE());

                SET @i += 1;
            END
        END
        SET @EndTime = GETDATE();
        INSERT INTO TestRunTables (TestRunID, TableID, StartAt, EndAt)
        VALUES (@TestRunID, @TableID, @StartTime, @EndTime);

        FETCH NEXT FROM table_cursor INTO @TableName, @TableID, @NoOfRows;
    END
    CLOSE table_cursor;
    DEALLOCATE table_cursor;
END
GO


-----------------------------------------------------------------------------------------------

CREATE PROCEDURE RunSelectPhase
    @TestID INT,
    @TestRunID INT
AS
BEGIN
    DECLARE 
        @ViewName NVARCHAR(100),
        @ViewID INT,
        @StartTime DATETIME,
        @EndTime DATETIME,
        @SQL NVARCHAR(MAX);

    DECLARE view_cursor CURSOR FOR
        SELECT v.Name, v.ViewID
        FROM [Views] v
        INNER JOIN TestViews tv ON v.ViewID = tv.ViewID
        WHERE tv.TestID = @TestID;

    OPEN view_cursor;
    FETCH NEXT FROM view_cursor INTO @ViewName, @ViewID;

    WHILE @@FETCH_STATUS = 0
    BEGIN
        SET @StartTime = GETDATE();

        SET @SQL = 'SELECT * FROM ' + QUOTENAME(@ViewName);
        EXEC (@SQL);

        SET @EndTime = GETDATE();

        INSERT INTO TestRunViews (TestRunID, ViewID, StartAt, EndAt)
        VALUES (@TestRunID, @ViewID, @StartTime, @EndTime);

        FETCH NEXT FROM view_cursor INTO @ViewName, @ViewID;
    END

    CLOSE view_cursor;
    DEALLOCATE view_cursor;
END
GO

----------------------------------------------------------------------------------------

CREATE PROCEDURE RunFullTest
AS
BEGIN
    DECLARE 
        @DeleteTestID INT,
        @InsertTestID INT,
        @SelectTestID INT,
        @TestRunID INT,
        @StartTest DATETIME,
        @EndTest DATETIME,
        @Description NVARCHAR(2000);

    --get test id by name
    SELECT @DeleteTestID = TestID 
    FROM Tests 
    WHERE Name = 'delete_from_table';

    SELECT @InsertTestID = TestID 
    FROM Tests 
    WHERE Name = 'insert_into_table';

    SELECT @SelectTestID = TestID 
    FROM Tests 
    WHERE Name = 'select_from_views';

    SET @Description = 'Full test: delete + insert + select';

    SET @StartTest = GETDATE();
    INSERT INTO TestRuns (Description, StartAt, EndAt)
    VALUES (@Description, @StartTest, NULL);

    SET @TestRunID = SCOPE_IDENTITY();

    EXEC RunDeletePhase @TestID = @DeleteTestID;

    EXEC RunInsertPhase 
        @TestID = @InsertTestID, 
        @TestRunID = @TestRunID;

    EXEC RunSelectPhase 
        @TestID = @SelectTestID, 
        @TestRunID = @TestRunID;

    SET @EndTest = GETDATE();

    UPDATE TestRuns
    SET EndAt = @EndTest
    WHERE TestRunID = @TestRunID;
END
GO

EXEC RunFullTest;

SELECT * FROM TestRuns;
SELECT * FROM TestRunTables;
SELECT * FROM TestRunViews;
