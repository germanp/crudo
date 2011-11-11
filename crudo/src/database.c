#include "database.h"
#include "sqlite3.h"

sqlite3* get_database(){
  static sqlite3* db;
  return db;
}

int init_database(const char* file_path){
  sqlite3* db=get_database();
  if ( sqlite3_open(file_path,&db) == SQLITE_OK ) {
    sqlite3_exec(db,SQL_SCHEMA_DEF,0,0,0);wa
  } else{
    return 0;
  }
}
