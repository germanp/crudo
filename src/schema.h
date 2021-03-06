#define SQL_SCHEMA_DEF "CREATE TABLE Package(\n\
-- Attributes --\n\
id integer PRIMARY KEY,\n\
name text UNIQUE NOT NULL COLLATE NOCASE,\n\
description TEXT,\n\
section TEXT,\n\
size INTEGER,\n\
version INTEGER,\n\
web TEXT,\n\
mantainer TEXT,\n\
checksum TEXT);\n\
\
CREATE TABLE File(\n\
-- Attributes --\n\
packageId INTEGER REFERENCES Package (id),\n\
filePath TEXT,\n\
checksum TEXT);\n\
\n\
CREATE TABLE Relation(\n\
-- Attributes --\n\
parentPackage INTEGER NOT NULL,\n\
type TEXT NOT NULL CHECK(type IN('d','o','c')),\n\
comparator TEXT,\n\
version INTEGER,\n\
relatedPackage TEXT);\n\
\n\
CREATE UNIQUE INDEX UniqueRelation ON Relation(parentPackage,relatedPackage);\n\
CREATE INDEX RelationPackageParentIndex ON Relation(parentPackage);\n\
CREATE INDEX RelationIndex ON Relation(parentPackage);\n\
\n"
