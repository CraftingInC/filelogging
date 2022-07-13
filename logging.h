
/* log("INFO : Hello there !"); */

#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>   // FILE   fprintf()  fopen()  fclose()  vfprintf()
#include <stdarg.h>  // va_start    va_end
#include <time.h>    // time()  localtime()  strftime()  tzset()

void _log(const char *fmt, ...);

#define log(...) _log(__VA_ARGS__)

#endif // LOGGING_H

void _log(const char *fmt, ...)
{
  char datestr[51];
  va_list ap;
  time_t t;
  t = time(NULL);
  tzset();

  char* filename = malloc(sizeof(char) * 19);
  strftime(datestr, sizeof(datestr) - 1, "%m-%d-%Y", localtime(&t));
  strcpy(filename, "log-");
  strcat(filename, datestr);
  strcat(filename, ".txt");
  FILE *file = fopen(filename, "a+");
  free(filename);

  strftime(datestr, sizeof(datestr) - 1, "%b/%d/%Y %H:%M", localtime(&t));
  fprintf(file, "%s - ", datestr);

  va_start(ap, fmt);
  vfprintf(file, fmt, ap);
  va_end(ap);

  fprintf(file, "\n");
  fclose(file);
}

