--  Continuus file information --- %full_filespec: createdemoSS7.sql~3:sql:1 %
use master
go
-- create the database demo on MOE
create database demo
on
  ( name=demo,
    filename="E:\demo.mdf",
    size=4,
    maxsize=100,
    filegrowth=1)
log on
  ( name="demo_log",
    filename="H:\demo.ldf",
    size=400)
go
-- create filegroup ( tablespace ) for data
alter database demo
add filegroup pin00     
go
-- add files to filegroup
alter database demo
add file
  ( name=FG1,
    filename="G:\demo1.ndf",
    size=2000MB),
  ( name=FG2,
    filename="G:\demo2.ndf",
    size=2000MB)
to filegroup pin00
go
-- create filegroup ( tablespace ) for indexes
alter database demo
add filegroup pinx00     
go
-- add files to filegroup
alter database demo
add file
  ( name=FG3,
    filename="F:\demo3.ndf",
    size=2000MB),
  ( name=FG4,
    filename="F:\demo4.ndf",
    size=2000MB)
to filegroup pinx00
go
-- create user pin and grant all permissions to it
EXEC sp_addlogin 'pin', 'pin', 'demo'
go
use demo
EXEC sp_grantdbaccess 'pin'
go
grant all to pin
go
