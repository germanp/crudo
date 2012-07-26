#include "database.h"
#include "schema.h"
#include "sqlite3.h"
#include <stdio.h>
#include <string.h>

static sqlite3* db; // Database pointer local to this file

/** 
 * Singletton like function. It will return a sqlite3 connection
 * pointer that first must be open and finally closed.
 * 
 * @return 
 */

sqlite3* get_database(){
  return db;
}

/** 
 * Open an indicated database file. It uses a internal static variable
 * that must be closed with close_database()
 * 
 * @param file_path String indicating the file path
 * 
 * @return Returns a pointer to sqlite3 object. NULL if fails
 */

int open_database(const char* file_path){
  return sqlite3_open_v2(file_path,&db,SQLITE_OPEN_READWRITE,NULL);
}

/** 
 * Closes the 'internal' database connection
 * 
 */

void close_database(){
  sqlite3_close(db);
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
  int ret_val=sqlite3_open_v2(file_path,&db,SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE,NULL);
  
  if ( ret_val  == SQLITE_OK ) {
    ret_val=sqlite3_exec(db,SQL_SCHEMA_DEF,0,0,0);
    /* // Debugging version of the last command */
    /* // -- */
    /* char* error; */
    /* ret_val=sqlite3_exec(db,SQL_SCHEMA_DEF,0,0,&error); */
    /* fprintf(stderr,"%s\n",error); */
    /* // -- */
  }
  sqlite3_close(db);
  return ret_val;
}

/** 
 * Adds a package to the database
 * 
 * @param p Package struct with all the package data
 * 
 * precond: opened database.
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
  //sqlite3* db=get_database();
  int ret_val=sqlite3_exec(db,sql_buf,0,0,0);
  sqlite3_free(sql_buf);
  
  return ret_val;
}

/** 
 * Add one or more relations to the database
 * 
 * @param parent_package Package id to which is added the relation
 * @param type Type of relation (d,o,c) (Depend, Optional, Conflict)
 * @param r List of relations to be added.
 * 
 * precond: opened database.
 * @return Returns SQLITE_DONE if ok, or another sqlite error. 

 // NOT IMPLEMENTED //
 If it fails, relation points to the relation that failed.
 /////////////////////
 */

int add_relations(int parent_package, char type, Relation* r){
  //Relation* r=*relation;
  if ( !r ) 
    return SQLITE_OK;
  sqlite3_stmt* pstmt;
  const char* sql="INSERT INTO Relation VALUES(?,?,?,?,?);";
  int ret_val;
  sqlite3_prepare_v2(db,sql,strlen(sql)+1,&pstmt,NULL);
  sqlite3_bind_int(pstmt,1,parent_package);
  sqlite3_bind_text(pstmt,2,&type,1,SQLITE_STATIC);
  while ( r ) {
    sqlite3_bind_text(pstmt,3,r->comparator,strlen(r->comparator)+1,SQLITE_STATIC);
    sqlite3_bind_int(pstmt,4,r->version);
    sqlite3_bind_text(pstmt,5,r->name,strlen(r->name)+1,SQLITE_STATIC);
    ret_val=sqlite3_step(pstmt);
    if ( SQLITE_DONE != ret_val )
      r=NULL;
    else {
      sqlite3_reset(pstmt);
      r=r->next;
    }
  }
  sqlite3_finalize(pstmt);
  return ret_val;
}

/**
 * Runs a sql query and returns the prepared statemnt.
 *
 * @param sql SQL string with the query.
 *
 * precond: needs an opened database.
 * postcond: the returned statement must be freed(with sqlite3_finalize()).
 *
 * @return Returns the result of step
 */

int run_query(sqlite3_stmt** pstmt,const char* sql){
  int ret_val=sqlite3_prepare_v2(db,sql,-1,pstmt,0);
  if ( SQLITE_OK == ret_val )
    return sqlite3_step(*pstmt);
  return ret_val;
}

int run_queryf(sqlite3_stmt** pstmt,const char* format, ...){
  va_list args;
  va_start(args,format);
  char* sql=sqlite3_vmprintf(format,args);
  va_end(args);
  int ret_val=sqlite3_prepare_v2(db,sql,-1,pstmt,0);
  sqlite3_free(sql);
  if ( SQLITE_OK == ret_val )
    return sqlite3_step(*pstmt);
  return ret_val;
}

/**
 * Runs a sql query and returns the prepared statemnt.
 *
 * @param sql SQL string with the query.
 *
 * precond: needs an opened database.
 *
 * @return Returns true or false.
 */

int execute_sql(const char* sql){
  sqlite3_stmt* pstmt;
  if ( SQLITE_OK == sqlite3_prepare_v2(db,sql,-1,&pstmt,0) ) {
    int ret=sqlite3_step(pstmt);
    sqlite3_finalize(pstmt);
    if ( SQLITE_DONE == ret || SQLITE_ROW == ret )
      return 1;
  }
  return 0;
}

/**
 * Obtains a package from given a name.
 *
 * @param name String indicating the exact name of the package.
 *
 * precond: needs a open database.
 * postcond: you must free the sqlite statement.
 * @return Returns an allocated Package with the package data. Returns
 * 0 if package was not found.
 */

Package* find_package(const char* name){
  char* sql_buf=sqlite3_mprintf("SELECT * FROM Package WHERE name IS %Q;",name);
  sqlite3_stmt* pstmt;
  Package* p=(NULL);
  if ( SQLITE_ROW == run_query(&pstmt,sql_buf) ){

    p=init_package();

    p->name=strdup(sqlite3_column_text(pstmt,1));
    p->description=strdup(sqlite3_column_text(pstmt,2));
    p->section=strdup(sqlite3_column_text(pstmt,3));
    p->size=sqlite3_column_int64(pstmt,4);
    p->version=sqlite3_column_int64(pstmt,5);
    p->web=strdup(sqlite3_column_text(pstmt,6));
    p->maintainer=strdup(sqlite3_column_text(pstmt,7));
    p->checksum=strdup(sqlite3_column_text(pstmt,8));

    sqlite3_finalize(pstmt);
  }
  sqlite3_free(sql_buf);
  return p;
}

/**
 * Deletes an specified package.
 *
 * @param name Exact name of the package.
 *
 * precond: database must be open.
 * return Returns True if a package was delete or false if not
 *
 */

int delete_package(const char* name){
  char* sql_buf=sqlite3_mprintf("DELETE FROM Package WHERE name = %Q;",name);
  execute_sql(sql_buf);
  sqlite3_free(sql_buf);
  return sqlite3_changes(db);
}

/**
 * Given a pattern name of packages returns a little brief about the
 * packages that matches it.  precond: database must be open.
 *
 * @param argz      Argz char style that will hold the packages info.
 * @param argz_len  Length of argz list.
 * @param name      String name of searched packages. It can be a glob
 *                  unix style pattern.
 *
 * precond: database must be open.
 * return  Returns SQLITE_DONE if no packages found, SQLITE_ROW if
 *         packages was found. It is the same that returns sqlite3_step()
 *
 */

int list_packages(char** argz, size_t* argz_len, const char* name){
  sqlite3_stmt* pstmt;
   
  int step_ret=run_queryf(&pstmt,"SELECT name,description,version,web FROM Package WHERE lower(name) GLOB lower(%Q);",name);
  int aux=step_ret;
  char buffer[13];
  unsigned long int version;
  while ( SQLITE_ROW == step_ret ){
    argz_add(argz,argz_len,sqlite3_column_text(pstmt,0));
    argz_add(argz,argz_len,sqlite3_column_text(pstmt,1));
    version=sqlite3_column_int64(pstmt,2);
    sprintf(buffer,"%d.%d.%d-%d",
	    (int)version/1000000,
	    (int)version%1000000/10000,
	    (int)version%10000/100,
	    (int)version%100
	    );
    argz_add(argz,argz_len,buffer);
    argz_add(argz,argz_len,sqlite3_column_text(pstmt,3));
    step_ret=sqlite3_step(pstmt);
  }
  return aux;
}
