#include "sqlite3.h"
#include "package.h"
#include "../config.h"

int open_database(const char* file_path);

sqlite3* get_database();

void close_database();

int init_database(const char* file_path);

int add_package(Package* p);

int add_relations(int parent_package, char type, Relation* r);

int find_id_package(const char* name);

int run_query(sqlite3_stmt** pstmt,const char* sql);

Package* find_package(const char* name);

int delete_package(const char* name);

