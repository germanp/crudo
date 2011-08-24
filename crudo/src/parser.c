#include "parser.h"
#include "package.h"
#include "config.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

/** 
 * Parses a debian style control file
 * 
 * @param file Path to the file
 * 
 * @return Filled and allocated Package structure.
 *
 * TODO: Free Package* p on error. 
 */

Package* parse(const char* file){
  FILE *fp = fopen(file, "r");
  char* buffer = strip_spaces(fp);
  char* work = buffer; // Work buffer
  char* last_work=buffer;
  Package* p=malloc(sizeof(Package));
  regex_t filter;
  regmatch_t match_array[3];
  int field_len, val_len=0; // Stores the length of parsed strings
  char* field; char* val; // Stores the strings parsed
  int val_base;
  const char* regex="^[[:space:]]?([[:alnum:]-]+):[[:space:]]*(.*)$";
  int error;

  if(regcomp(&filter, regex , REG_EXTENDED|REG_NEWLINE) != 0){
    fprintf(stderr,"%s: Critical error, the memory is exhausted.\n",PACKAGE_NAME);
    p=0;
  } else {
    if ( !regexec(&filter,work,3,match_array,0) ) {
      field_len=match_array[1].rm_eo-match_array[1].rm_so;
      free(field);
      field=extract_string(work,match_array[1].rm_so, field_len);
      val_len=match_array[2].rm_eo-match_array[2].rm_so;
      val_base=match_array[2].rm_so;
      work=&work[match_array[0].rm_eo+1]; // Advances the working pointer
      while ( !regexec(&filter,work,3,match_array,0) ) {
	val_len+=match_array[0].rm_so;
	free(val);
	val=extract_string(last_work,val_base,val_len);
	if ( fill_package(p,field,val) )
	  return 0;
	field_len=match_array[1].rm_eo-match_array[1].rm_so;
	free(field);
	field=extract_string(work,match_array[1].rm_so,field_len);
	val_len=match_array[2].rm_eo-match_array[2].rm_so;
	val_base=match_array[2].rm_so;
	last_work=work;
	work=&work[match_array[0].rm_eo+1]; // Advances the working pointer
      }
      val_len+=strlen(work);
      free(val);
      val=extract_string(last_work,val_base,val_len);
      if ( fill_package(p,field,val) )
	return 0;
    }
  }
  fclose(fp);
  return p;
}
/** 
 * Finds a newline in a string.
 * 
 * @param buffer String to be searched.
 * 
 * @return Returns the position where newline was found.
 */
int newline_offset(char* buffer){
  int i;
  for (i = 0; buffer[i]!='\0' && buffer[i]!='\n'; ++i);
  return i;
}

/** 
 * Given a package and a field, value pair fill the package struct
 * with the data. Always make the corresponding validation.
 * 
 * @param p Package struct to be filled
 * @param field The field nae that correspond to the data to be populated
 * @param val Raw dato to be added to the package struct.
 * 
 * @return Returns 1 on exit and 0 if it fails.
 * 
 */
int fill_package(Package* p,char* field, char* val){
  val=strstrip (val);
  int val_len=strlen(val);
  int bad_char=0;
  if (!strcasecmp(field,"Package")) {
    if ( (bad_char=strcspn(val," \n\t()[].,:;<>")) == val_len ){
      p->name=strdup(val);
    }
  }else if (!strcasecmp(val,"Description")){
    p->description=strdup(val);
  }else if (!strcasecmp(val,"Homepage")){
    p->web=strdup(val);
  }else if (!strcasecmp(field,"Section")) {
    if ( (bad_char=strcspn(val," \n\t()[].,:<>")) == val_len ){
      p->section=strdup(val);
    } else {
      fprintf(stderr,
	      "%s: Error when parsing '%s', character '%c' is not permitted.\n",
	      PACKAGE_NAME,val,val[bad_char]);
    }
  }else if (!strcasecmp(field,"Version")) {
    p->version=parse_version(val);
  /* }else if (!strcasecmp(field,"Depends")) { */
  /*   p->depends=parse_relation(val); */
  /* }else if (!strcasecmp(field,"Conflicts")) { */
  /*   p->conflicts=parse_relation(val); */
  /* }else if (!strcasecmp(field,"Suggests")) { */
  /*   p->optionals=parse_relation(val); */
  /* }else if (!strcasecmp(field,"Recommends")) { */
  /*   p->optionals=parse_relation(val); */
  }
  return ;
}
/** 
 * Strip all the repeated spaces (tabs, returns, etc)
 * 
 * @param f Already open file stream
 * 
 * @return It returns an already allocated char*. You must free it.
 */

char* strip_spaces(FILE* f){
  char* buffer=malloc(1024);
  int letter, i=0, last_letter=0;
  while( (letter=fgetc(f)) != EOF ) {
    if (isspace(letter)) {
      if ( letter == last_letter ){
	last_letter=letter;
	continue;
      }
    }
    last_letter=letter;
    buffer[i]=letter;
    i++;
    // Super dynamic allocation.
    if (!(i%1024)) buffer=(char*)realloc(buffer,(i+1024)*sizeof(char));
  }
  buffer[i]='\0';
  return buffer;
}
 
/**
 * strstrip - Removes leading and trailing whitespace from @s.
 * @s: The string to be stripped.
 *
 * Note that the first trailing whitespace is replaced with a %NUL-terminator
 * in the given string @s. Returns a pointer to the first non-whitespace
 * character in @s.
 */

/*******************************/
/* Borrowed from linux sources */
/*******************************/
char* strstrip(char *s) {
  size_t size;
  char* end;
  size = strlen(s);
  if (!size) return s;
  end = s + size - 1;
  while (end >= s && isspace(*end)) end--;
  *(end + 1) = '\0';
  while (*s && isspace(*s)) s++;
  return s;
}

/** 
 * Copies a substring from another string.
 * 
 * @param buffer String where it will extract a substring.
 * @param base Number of letters to avoid from the beginning of the string.
 * @param len Length of the string to be extracted.
 * 
 * @return Returns an already allocated string that must be freed.
 */

char* extract_string(char* str, int base, int len){
  char* ret_val=malloc(len);
  strncpy(ret_val,&str[base],len);
  ret_val[len]='\0';
  return ret_val;
}

/** 
 * Processes a string and returns the appropriate unsigned long int.
 * 
 * @param ver An String containing the version info.
 * For example: 2.10.1-8, but also accepts debian style but without characters.
 * 
 * @return Returns a long integer.
 */
long unsigned int parse_version(char* ver){
  regex_t filter;
  regmatch_t match_array[5]={0,0,0,0,0};
  const char* regex=
    "^[0-9]?:?([0-9]{0,2}).([0-9]{1,2}).([0-9]{1,2})-?([0-9]{0,2})$";
  char* majver; char* midver; char* minver; char* rev;
  int ret_val=0;

  if ( regcomp(&filter,regex, REG_EXTENDED|REG_NEWLINE) != 0 ) {
    fprintf(stderr,"%s: Critical error, the memory is exhausted.\n",PACKAGE_NAME);
  } else {
    if ( !regexec(&filter,ver,5,match_array,0) ) {
      majver=extract_string(ver,match_array[1].rm_so,match_array[1].rm_eo-match_array[1].rm_so);
      midver=extract_string(ver,match_array[2].rm_so,match_array[2].rm_eo-match_array[2].rm_so);
      minver=extract_string(ver,match_array[3].rm_so,match_array[3].rm_eo-match_array[3].rm_so);
      rev=extract_string(ver,match_array[4].rm_so,match_array[4].rm_eo-match_array[4].rm_so);
      ret_val=
	strtol(majver,0,10)*1000000+
	strtol(midver,0,10)*10000+
	strtol(minver,0,10)*100+
	strtol(rev,0,10);
    } 
    return ret_val;
  }
}
 
Relation* parse_relation(char* rel){
  regex_t filter;
  regmatch_t match_array[5]={0,0,0,0,0};
  const char* regex=
    "^([:alpha:])$";
  return NULL;
}
