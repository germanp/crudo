/**
 * @file   parser.c
 * @author german <german@german-desktop>
 * @date   Wed Sep  7 00:08:44 2011
 * 
 * @brief  All the refered to parse the control files.
 * 
 * @TODO 
 *       - Find a way to make the regex compilation only once.
 */

#include "parser.h"
#include "package.h"
#include "config.h"
#include "error.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Invalid characters for package names and section
const char* INV_PACKAGE_CHARS=" \n\t()[],:;<>";

/** 
 * Parses a debian style control file
 * 
 * @param fp An already open file stream.
 * 
 * @return Returns an allocated Package structure.
 *
 **/

Package* parse(FILE* fp){
  char* buffer = strip_spaces(fp);
  const char* work = buffer; // A copy of buffer (for working on it).
  const char* last_work=buffer;
  regex_t filter;
  regmatch_t match_a[3];
  int field_len, val_len=0; // Will store the length of parsed strings
  char field[200]; char val[1000]; // Will store the parsed strings
  int val_base;
  const char* regex="^[[:space:]]?([[:alnum:]-]+):[[:space:]]*(.*)$";
  
  Package* p=init_package();
  if(regcomp(&filter, regex , REG_EXTENDED|REG_NEWLINE) != 0){
    libc_errorf("Parsing error");
    free_package(&p);
    goto cleanup;
  } else {
    if ( !regexec(&filter,work,3,match_a,0) ) {
      extract_regmatch(field,work,match_a[1],200);
      val_len=match_a[2].rm_eo - match_a[2].rm_so;
      val_base=match_a[2].rm_so;
      work=&work[match_a[0].rm_eo+1]; // Advances the working pointer
      while ( !regexec(&filter,work,3,match_a,0) ) {
	val_len+=match_a[0].rm_so;
	if ( val_len > 1000 ) val_len=1000;
	extract_string(val,last_work,val_base,val_len);
	if ( ! fill_package(p,field,val) ){
	  free_package(&p);
	  goto cleanup;
	}
	extract_regmatch(field,work,match_a[1],200);
	val_len=match_a[2].rm_eo - match_a[2].rm_so;
	val_base=match_a[2].rm_so;
	last_work=work;
	work=&work[match_a[0].rm_eo + 1]; // Advances the working pointer
      }
      val_len+=strlen(work);
      if ( val_len > 1000 ) val_len=1000;
      extract_string(val,last_work,val_base,val_len);
      if ( ! fill_package(p,field,val)  ) {
	free_package(&p);
      }
    }
  }
 cleanup:
  regfree(&filter);
  free(buffer);
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
 * @param val Raw data to be added to the package struct.
 * 
 * @return Returns 1 on sucess or 0 on error.
 * 
 */

int fill_package(Package* p, char* field, char* val){
  val=strstrip (val);
  int bad_char=0;
  if (!strcasecmp(field,"Package")) {
    if ( (bad_char=strcspn(val,INV_PACKAGE_CHARS)) == strlen(val) ){
      p->name=strdup(val);
    } else {
      fprintf(stderr,"Parsing error: '%s' is not a valid package name.",val);
      return 0;
    }
  } else if (!strcasecmp(field,"Description")){
    p->description=strdup(val);
  } else if (!strcasecmp(field,"Homepage")){
    p->web=strdup(val);
  } else if (!strcasecmp(field,"Maintainer")){
    p->maintainer=strdup(val);
  } else if (!strcasecmp(field,"Installed-Size")) {
    p->size=strtol(val,NULL,10);
  } else if (!strcasecmp(field,"Section")) {
    if ( (bad_char=strcspn(val,INV_PACKAGE_CHARS)) == strlen(val) ){
      p->section=strdup(val);
    } else {
      fprintf(stderr,"Parsing error: '%s' is not a valid section name.\n",val);
      return 0;
    }
  } else if (!strcasecmp(field,"Checksum")) {
    p->checksum=strdup(val);    
  } else if (!strcasecmp(field,"Homepage")) {
    p->web=strdup(val);    
  } else if (!strcasecmp(field,"Version")) {
    p->version=parse_version(val);
    if ( !p->version ) {
      error_messagef("While parsing '%s'\n",field);
      return 0;
    }
  } else if (!strcasecmp(field,"Depends")) {
    return parse_relations(&p->depends,val);
  } else if (!strcasecmp(field,"Conflicts")) {
    return parse_relations(&p->conflicts,val);
  } else if (!strcasecmp(field,"Suggests")) {
    return parse_relations(&p->optionals,val);
  }/*else if (!strcasecmp(field,"Recommends")) { */
  /*   p->optionals=parse_relation(val); */
  //}
  return 1;
}
/** 
 * Strip all the repeated spaces (tabs, returns, etc)
 * 
 * @param f Already open file stream
 * 
 * @return It returns an already allocated char*. You must free it.
 */

char* strip_spaces(FILE* f){
  char* buffer=NULL;
  int i=0;
  char letter, last_letter=0;
  while( (letter=fgetc(f)) != EOF ) {
    if ( ! (i%1000) ) {
      buffer=realloc(buffer,(i+1000)*sizeof(char));
    }
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
 * Copies a substring from another string. d ==> dynamic alloc
 * 
 * @param buffer String where it will extract a substring.
 * @param base Number of letters to avoid from the beginning of the string.
 * @param len Length of the string to be extracted.
 * 
 * @return Returns an already allcated string that must be freed.
 */

/* char* d_extract_string(char* str, int base, int len){ */
/*   char* ret_val=malloc(len); */
/*   strncpy(ret_val,&str[base],len); */
/*   ret_val[len]='\0'; */
/*   return ret_val; */
/* } */

/** 
 * Extract a string from a given string, base and length and puts it
 * in @allocated.
 * 
 * @param matched String where locate the extracted string.
 * @param str String where extract from.
 * @param base Number of characters to avoid from the start
 * @param len Number of characters to be copied.
 */

void extract_string(char* matched, const char* str, unsigned int base, unsigned int len){
  strncpy(matched,&str[base],len);
  matched[len]='\0';
}

/** 
 * Extracts a string from a buffer based on a regmatch struct
 * 
 * @param matched Already allocated string where the string will be stored
 * @param str String where extract the string.
 * @param m regmatch struct (libc) with the matched positions.
 * @param max Maximum number of characters to copy.
 */

void extract_regmatch(char matched[], const char* str, regmatch_t m, unsigned int max){
  int len=m.rm_eo-m.rm_so;
  if ( len > max )
    len=max;
  extract_string(matched,str,m.rm_so, len);
}

/** 
 * Processes a string and returns the appropriate unsigned long int.
 *
 * @param ver An String containing the version info.  For example:
 * 2.10.1-8, but also accepts debian style but without characters.
 *
 * @return Returns a long integer where each digit shows the version
 *         that corresponds to the groups separated by . and -
 */
long unsigned int parse_version(const char* ver){
  regex_t filter;
  regmatch_t match_a[5]={0,0,0,0,0}; // array with parenthesis matches
  const char* regex=
    "^[0-9]?:?([0-9]{1,2}).([0-9]{1,2}).([0-9]{1,2})-?([0-9]{0,2})$";
  char majver[3]; char midver[3]; char minver[3]; char rev[3];
  int ret_val=0;

  if ( regcomp(&filter,regex, REG_EXTENDED|REG_NEWLINE) != 0 ) {
    libc_error("Parsing error");
  } else {
    if ( !regexec(&filter,ver,5,match_a,0) ) {
      extract_string(majver,ver,match_a[1].rm_so,
		     match_a[1].rm_eo - match_a[1].rm_so);
      extract_string(midver,ver,match_a[2].rm_so,
		     match_a[2].rm_eo - match_a[2].rm_so);
      extract_string(minver,ver,match_a[3].rm_so,
		     match_a[3].rm_eo - match_a[3].rm_so);
      extract_string(rev,ver,match_a[4].rm_so,
		     match_a[4].rm_eo - match_a[4].rm_so);
      ret_val=
	strtol(majver,0,10)*1000000 + 
	strtol(midver,0,10)*10000 + 
	strtol(minver,0,10)*100 + 
	strtol(rev,0,10);
    } else {
      error_messagef("Parsing error: '%s' is not a valid version.\n",ver);
    }
  }
  return ret_val;
}

/** 
 * Given a string containing one or more relations, returns the
 * appropiate Relation struct.
 * 
 * @param first_rel A pointer where will be the Relation struct (R/W)
 * @param txt_rel String with the corresponding control format.
 * 
 * @return Returns 1 on success and 0 if fail.
 */
 
int parse_relations(Relation** first_rel,const char* txt_rel){
  regex_t filter;
  regmatch_t match_a[4]={0,0,0,0};
  const char* regex=
    "^[[:space:]]*([-_+.[:alnum:]]+)[[:space:]]*[(][[:space:]]*([><=]{1,2})[[:space:]]*([0-9.:-]+)[)][[:space:]]*$";
  if( regcomp(&filter,regex,REG_EXTENDED|REG_NEWLINE) != 0 ){
    libc_error("Parsing error");
    return 0;
  }
  char name[200], txt_ver[20];
  char* splitted;
  int ret_val=1;
  *first_rel=NULL;
  Relation* rel=NULL;
  char* cp_rel=strdup(txt_rel);
  splitted=strtok(cp_rel,",");

  while ( splitted != NULL ) {
    if ( !regexec(&filter,splitted,4,match_a,0) ) {
      if ( *first_rel == NULL ){
	rel=init_relation();
	*first_rel=rel;
      } else {
	rel->next=init_relation();
	rel=rel->next;
      }
      extract_regmatch(name,splitted,match_a[1],200);
      rel->name=strdup(name);

      extract_string(rel->comparator,splitted,match_a[2].rm_so,
		     match_a[2].rm_eo - match_a[2].rm_so);

      extract_regmatch(txt_ver, splitted, match_a[3], 20);
      rel->version=parse_version(txt_ver);
      if ( rel->version == 0 ){
	free_relations(first_rel);
	error_messagef("While parsing '%s'\n",splitted);
	ret_val=0;
	goto cleanup;
      }
    } else{
      char* aux=strstrip(splitted);
      if ( strcspn(aux,INV_PACKAGE_CHARS) == strlen(aux) ){
	if ( *first_rel == NULL ){
	  rel=init_relation();
	  *first_rel=rel;
	} else {
	  rel->next=init_relation();
	  rel=rel->next;
	}
	rel->name=strdup(aux);
	rel->comparator[0]=0;
	rel->version=0;
      } else {
	free_relations(first_rel);
	error_messagef("Parsing error: '%s' is not a valid package name.",aux);
	ret_val=0;
	goto cleanup;
      }
    }
    splitted=strtok(NULL,",");
  }
 cleanup:
  free(cp_rel);
  return ret_val;
}
