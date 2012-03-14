#include "database.h"
#include "schema.h"
#include "sqlite3.h"
#include <stdio.h>
#include <string.h>

/** 
 * Singletton like function. It will return a sqlite3 connection
 * pointer that first must be open and finally closed.
 * 
 * @return 
 */

sqlite3** get_database(){
  static sqlite3* db;
  return &db;
}

/** 
 * Open an indicated database file. It uses a internal static variable
 * that must be closed with close_database()
 * 
 * @param file_path String indicating the file pat
 * 
 * @return Returns a pointer to sqlite3 object. NULL if fails
 */

sqlite3* open_database(const char* file_path){
  sqlite3** db=get_database();
  if ( sqlite3_open_v2(file_path,db,SQLITE_OPEN_READWRITE,NULL) == SQLITE_OK ){
    return *db;
  } else {
    return NULL;
  }
}

/** 
 * Closes the 'internal' database connection
 * 
 */

void close_database(){
  sqlite3_close(*get_database());
}

/** 
 * Initializes the sqlite3 database with the predefined schema.
 *
 * PreCond: The file must not exists.
 * 
 * @param file_path String indicating the file path to create
 * 
 * @return When sucess 0 (SQLITE_OK)
 *         When fails, an sqlite error code.
 */

int init_database(const char* file_path){
  sqlite3* db;
  if ( sqlite3_open(file_path,&db) == SQLITE_OK ) {
    int ret_val=sqlite3_exec(db,SQL_SCHEMA_DEF,0,0,0);
    /* // Debugging version of the last command */
    /* // -- */
    /* char* error; */
    /* int ret_val=sqlite3_exec(db,SQL_SCHEMA_DEF,0,0,&error); */
    /* if ( error ) */
    /*   puts(error); */
    // --
    sqlite3_close(db);
    return ret_val;
  } else{
    sqlite3_close(db);
    return 0;
  }
}

/** 
 * Adds a package to the database
 * 
 * @param p Package struct with all the package data
 * 
 * @return Returns 0 on Success or an sqlite error code.
 */

int add_package(Package* p){
  char* sql_buf=
    sqlite3_mprintf("INSERT INTO Package VALUES(NULL,%Q,%Q,%Q,%i,%i,%Q,%Q,%Q);",
		    p->name,
		    p->description,
		    p->section,
		    p->size,
		    p->version,
		    p->web,
		    p->maintainer,
		    p->checksum
		    );
  sqlite3* db=*get_database();
  int ret_val=sqlite3_exec(db,sql_buf,0,0,0);
  sqlite3_free(sql_buf);
  return ret_val;
}

/** 
 * Add one or more relations to the database
 * 
 * @param parent_package Package to which is added the relation
 * @param type Type of relation (d,o,c) (Depend, Optional, Conflict)
 * @param r Relations to be added
 * 
 * @return Returns SQLITE_DONE if ok, or another sqlite error. If it
 * fails, relation points to the relation that failed.
 */

int add_relations(const char* parent_package, char type, Relation** relation){
  if ( !r ) 
    return SQLITE_OK;
  Relation* r=*relation;
  sqlite3* db=*get_database();
  sqlite3_stmt* pstmt;
  const char* sql="INSERT INTO Relation VALUES(?,?,?,?,?);";
  int ret_val;
  sqlite3_prepare_v2(db,sql,strlen(sql)+1,&pstmt,NULL);
  sqlite3_bind_text(pstmt,1,parent_package,strlen(parent_package)+1,SQLITE_STATIC);
  sqlite3_bind_text(pstmt,2,&type,1,SQLITE_STATIC);
  while ( r ) {
    sqlite3_bind_text(pstmt,3,r->comparator,strlen(r->comparator)+1,SQLITE_STATIC);
    sqlite3_bind_int(pstmt,4,r->version);
    sqlite3_bind_text(pstmt,5,r->name,strlen(r->name)+1,SQLITE_STATIC);
    ret_val=sqlite3_step(pstmt);
    if ( ret_val != SQLITE_DONE )
      r=NULL;
    else
      r=r->next;
  }
  sqlite3_finalize(pstmt);
  return ret_val;
}

Package* get_package(const char* name){
  sqlite3* db=*get_database();
}
