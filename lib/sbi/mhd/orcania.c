#include "ogs-core.h"
#include "orcania.h"

#include <stdarg.h>

void *o_malloc(size_t size)
{
  if (!size) {
    return NULL;
  } else {
    return malloc(size);
  }
}

void *o_realloc(void * ptr, size_t size)
{
  if (!size) {
    return NULL;
  } else {
    return realloc(ptr, size);
  }
}

void o_free(void * ptr)
{
  if (ptr == NULL) {
    return;
  } else {
    free(ptr);
  }
}

char *msprintf(const char * message, ...)
{
  va_list argp, argp_cpy;
  size_t out_len = 0;
  char * out = NULL;
  if (message != NULL) {
    va_start(argp, message);
    va_copy(argp_cpy, argp); // We make a copy because in some architectures, vsnprintf can modify argp
    out_len = vsnprintf(NULL, 0, message, argp);
    out = o_malloc(out_len+sizeof(char));
    if (out == NULL) {
      va_end(argp);
      va_end(argp_cpy);
      return NULL;
    }
    vsnprintf(out, (out_len+sizeof(char)), message, argp_cpy);
    va_end(argp);
    va_end(argp_cpy);
  }
  return out;
}

char *o_strdup(const char * source)
{
  return (source==NULL?NULL:o_strndup(source, strlen(source)));
}

char *o_strndup(const char * source, size_t len)
{
  char *new_str;

  if (source == NULL) {
    return NULL;
  } else {
    new_str = o_malloc(len + 1);
    if(!new_str) {
      return NULL;
    }

    memcpy(new_str, source, len);
    new_str[len] = '\0';
    return new_str;
  }
}

char *trimwhitespace(char * str)
{
  char * end;

  if (str == NULL) {
    return NULL;
  } else if(*str == 0) {
    return str;
  }

  while(isspace((unsigned char)*str)) str++;

  end = str + ogs_strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) {
    end--;
  }

  *(end+1) = 0;

  return str;
}

char *trimcharacter(char * str, char to_remove)
{
  char * end;

  if (str == NULL) {
    return NULL;
  } else if(*str == 0) {
    return str;
  }

  while(*str == to_remove) str++;

  end = str + ogs_strlen(str) - 1;
  while(end > str && (*end == to_remove)) {
    end--;
  }

  *(end+1) = 0;

  return str;
}
