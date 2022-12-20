/*
 * Include the provided hashtable library.
 */
#include "hashtable.h"

/*
 * Include the header file.
 */
#include "philspel.h"

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * this hashtable stores the dictionary.
 */
HashTable *dictionary;

/*
 * the MAIN routine.  You can safely print debugging information
 * to standard error (stderr) and it will be ignored in the grading
 * process, in the same way which this does.
 */
int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Specify a dictionary\n");
    return 0;
  }
  /*
   * Allocate a hash table to store the dictionary
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(2255, &stringHash, &stringEquals);
  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");

  fprintf(stderr, "Processing stdin\n");
  processInput();

  /* main in C should always return 0 as a way of telling
     whatever program invoked this that everything went OK
     */
  return 0;
}

/*
 * You need to define this function. void *s can be safely casted
 * to a char * (null terminated string) which is done for you here for
 * convenience.
 */
unsigned int stringHash(void *s) {
  char *string = (char *)s;
  int h = 0;
  size_t len = strlen(string);
        if (h == 0 && len > 0) {
          //  char val[len];
          //  strcpy(val, string);
            for (int i = 0; i < len; i++) {
                h = 31 * h + string[i];
            }
        }
        return h;
}

/*
 * You need to define this function.  It should return a nonzero
 * value if the two strings are identical (case sensitive comparison)
 * and 0 otherwise.
 */
int stringEquals(void *s1, void *s2) {
  char *string1 = (char *)s1;
  char *string2 = (char *)s2;
  return !strcmp(string1,string2);
}


unsigned int misspelled(char* string){
//  fprintf(stderr, "%s\n",(char*) findData(dictionary, "this"));
  char allbutfirst[strlen(string)+1];
  strcpy(allbutfirst, string);
  for(int i =1; i<strlen(string);i++){
    allbutfirst[i] = tolower(allbutfirst[i]);
  }
  char all[strlen(string+1)];
  strcpy(all,allbutfirst);

  all[0] = tolower(all[0]);
  if((char*) findData(dictionary,string) != NULL){
    return 0;
  } else if((char*) findData(dictionary, allbutfirst) != NULL){
    return 0;
  }else if((char*) findData(dictionary, all) != NULL){
    return 0;
  }else{
    return 1;
  }
}


/*
 * this function should read in every word in the dictionary and
 * store it in the dictionary.  You should first open the file specified,
 * then read the words one at a time and insert them into the dictionary.
 * Once the file is read in completely, exit.  You will need to allocate
 * (using malloc()) space for each word.  As described in the specs, you
 * can initially assume that no word is longer than 60 characters.  However,
 * for the final 20% of your grade, you cannot assumed that words have a bounded
 * length.  You can NOT assume that the specified file exists.  If the file does
 * NOT exist, you should print some message to standard error and call exit(0)
 * to cleanly exit the program.
 *
 * Since the format is one word at a time, with returns in between,
 * you can safely use fscanf() to read in the strings until you want to handle
 * arbitrarily long dictionary chacaters.
 */
void readDictionary(char *filename) {
  FILE *f = fopen(filename, "r");
  if(f == NULL){
    fprintf(stderr, "FILE DOES NOT EXIST :(");
    exit(0);
  } else{
    int ch;
    int size = 0;
    int mal_strlen = 60;
    int mal = mal_strlen+1;
    char *word = (char*) (malloc(mal));
    while((ch=fgetc(f)) != EOF){
      char c = (char) ch;
       if(isalpha(c)){
        if(size >= mal_strlen){
          mal_strlen *= 2;
          mal = mal_strlen+1;
          word = (char*) realloc(word, mal);
        }
        word[size] = c;
        size++;
      }else if(size>0){
        word[size] = '\0';
        insertData(dictionary, (void*) word, (void*) word);
        size = 0;
        mal_strlen = 60;
        mal = mal_strlen +1;
        word = (char*) malloc(mal);
      }
    }
    if(size > 0){
      word[size] = '\0';
      insertData(dictionary,(void*) word,(void*) word);
    }
    fclose(f);
  }
}

/*
 * This should process standard input and copy it to standard output
 * as specified in specs.  EG, if a standard dictionary was used
 * and the string "this is a taest of  this-proGram" was given to
 * standard input, the output to standard output (stdout) should be
 * "this is a teast [sic] of  this-proGram".  All words should be checked
 * against the dictionary as they are input, again with all but the first
 * letter converted to lowercase, and finally with all letters converted
 * to lowercase.  Only if all 3 cases are not in the dictionary should it
 * be reported as not being found, by appending " [sic]" after the
 * error.
 *
 * Since we care about preserving whitespace, and pass on all non alphabet
 * characters untouched, and with all non alphabet characters acting as
 * word breaks, scanf() is probably insufficent (since it only considers
 * whitespace as breaking strings), so you will probably have
 * to get characters from standard input one at a time.
 *
 * As stated in the specs, you can initially assume that no word is longer than
 * 60 characters, but you may have strings of non-alphabetic characters (eg,
 * numbers, punctuation) which are longer than 60 characters. For the final 20%
 * of your grade, you can no longer assume words have a bounded length.
 */
void processInput() {
int ch;
int counter = 0;

char err[7] = {' ', '[','s','i','c',']', '\0'};

int size = 0;
int mal_strlen = 60;
int mal = mal_strlen+1;
char *word = (char*) (malloc(mal));

while((ch=fgetc(stdin)) != EOF){
  counter++;
  if(ch<=127 && ch >=0){
  char c = (char) ch;
  if(isalpha(c)){
    if(size >= mal_strlen){
      mal_strlen *= 2;
      mal = mal_strlen+1;
      word = (char*) realloc(word, mal);
    }
    word[size] = c;
    word[size+1] = '\0';
    size++;
  } else{
    if(size>0){
      fprintf(stdout, "%s", word);
      if(misspelled(word)){
        fprintf(stdout, "%s", err );
      }
      free(word);
      size = 0;
      mal_strlen = 60;
      mal = mal_strlen +1;
      word = (char*) malloc(mal);
    }
    fprintf(stdout, "%c", c );
    }
  }else{
    fprintf(stdout, "%c", ch );
  }
}
if(!counter){
  fprintf(stderr, "NO INPUT :(");
  exit(0);
}
if(size > 0){
  fprintf(stdout, "%s", word);
  if(misspelled(word)){
    fprintf(stdout, "%s",err );
  }
}
free(word);
}
