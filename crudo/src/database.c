
static const char* create_sql_stmt=
  "CREATE TABLE Package(
-- Attributes --
    id integer integer primary key,
    name text unique,
    description text,
    section text,
    size integer,
    version integer,
    web text,
    maintainer text,
    checksum text);

CREATE TABLE Depend(
-- Attributes --
	packageParent text
	   REFERENCES Package ( name )
	     ON UPDATE CASCADE
	     ON DELETE CASCADE ,
	comparator text,
	version integer,
	name text);

CREATE TABLE Optional(
-- Attributes --
	packageId integer REFERENCES Package ( name )
	     ON UPDATE CASCADE
	     ON DELETE CASCADE,
	comparator text,
	version integer,
	 integer);

CREATE TABLE Conflict(
-- Attributes --
	name text REFERENCES Package ( name )
	     ON UPDATE CASCADE
	     ON DELETE CASCADE,
	comparator text,
	version integer,
	packageId integer);

CREATE TABLE File(
-- Attributes --
	packageName integer REFERENCES Package ( name )
	     ON UPDATE CASCADE
	     ON DELETE CASCADE,
	filePath text,
	checksum text
);";
