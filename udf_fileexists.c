#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

my_bool udf_fileexists_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 1)
  {
    strcpy(message, "udf_fileexists() requires one string argument");
    return 1;
  }

  if (args->arg_type[0] != STRING_RESULT)
  {
    strcpy(message, "udf_fileexists() the argument has to be a string");
    return 1;
  }

  return 0;
}

long long *udf_fileexists(UDF_INIT *initid, UDF_ARGS *args, char *result, 
                      unsigned long *res_length, char *null_value, char *error)
{
  struct stat sb;

  if (stat(args->args[0], &sb) == -1) {
	return 0; // file doesn't exist
  }

  return 1; // file exists
}

