#include <sqlite3.h>
#include "package.h"

sqlite3** get_database();

int init_database(const char* file_path);

int add_package(Package* p);

int add_relations(const char* parent_package, char type, Relation* r);

int find_id_package(const char* name);

int delete_package(int id);
