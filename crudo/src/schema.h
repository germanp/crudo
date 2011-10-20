#define SQL_SCHEMA_DEF "CREATE TABLE Package(\
-- Attributes --\
id integer PRIMARY KEY,\
name text UNIQUE,\
description text,\
section text,\
size integer,\
version integer,\
web text,\
maintainer text,\
checksum text);\
\
CREATE TABLE File(\
-- Attributes --\
packageName text REFERENCES Package (name),\
filePath text,\
checksum text);\
\
CREATE INDEX FilePackageNameIndex ON File(packageName);\
\
CREATE TABLE Depend(\
-- Attributes --\
packageParent text,\
comparator text,\
version integer,\
packageRelated text);\
\
CREATE INDEX DependPackageParentIndex ON Depend(packageParent);\
CREATE INDEX DependIndex ON Depend(packageParent);\
\
CREATE TABLE Optional(\
-- Attributes --\
packageParent text,\
comparator text,\
version integer,\
packageRelated text);\
\
CREATE INDEX OptionalPackageParentIndex ON Optional(packageParent);\
CREATE INDEX DependIndex ON Optional(packageParent);\
\
CREATE TABLE Conflict(\
-- Attributes --\
packageParent text,\
comparator text,\
version integer,\
packageRelated text);\
\
CREATE INDEX ConflictPackageParentIndex ON Conflict(packageParent);\
CREATE INDEX ConflictIndex ON Conflict(packageParent);"
