/**
 * 
 * Orcania library
 * 
 * Different functions for different purposes but that can be shared between
 * other projects
 * 
 * orcania.c: main functions definitions
 * 
 * Copyright 2015-2018 Nicolas Mora <mail@babelouest.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation;
 * version 2.1 of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU GENERAL PUBLIC LICENSE for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include "orcania.h"

#ifdef _MSC_VER
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif

/**
 * 
 * Orcania library
 * 
 * Different functions for different purposes but that can be shared between
 * other projects
 * 
 */

/**
 * char * msprintf(const char * message, ...)
 * Implementation of sprintf that return a malloc'd char * with the string construction
 * because life is too short to use 3 lines instead of 1
 * but don't forget to free the returned value after use!
 */
char * msprintf(const char * message, ...) {
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

/**
 * o_strdup
 * a modified strdup function that don't crash when source is NULL, instead return NULL
 * Returned value must be free'd after use
 */
char * o_strdup(const char * source) {
  return (source==NULL?NULL:o_strndup(source, strlen(source)));
}

/**
 * o_strndup
 * a modified strndup function that don't crash when source is NULL, instead return NULL
 * Returned value must be free'd after use
 */
char * o_strndup(const char * source, size_t len) {
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

/**
 * o_strcmp
 * a modified strcmp function that don't crash when p1 is NULL or p2 us NULL
 */
int o_strcmp(const char * p1, const char * p2) {
  if (p1 == NULL && p2 == NULL) {
    return 0;
  } else if (p1 != NULL && p2 == NULL) {
    return -1;
  } else if (p1 == NULL) {
    return 1;
  } else {
    return strcmp(p1, p2);
  }
}

/**
 * o_strncmp
 * a modified strncmp function that don't crash when p1 is NULL or p2 us NULL
 */
int o_strncmp(const char * p1, const char * p2, size_t n) {
  if ((p1 == NULL && p2 == NULL) || n <= 0) {
    return 0;
  } else if (p1 != NULL && p2 == NULL) {
    return -1;
  } else if (p1 == NULL) {
    return 1;
  } else {
    return strncmp(p1, p2, n);
  }
}

/**
 * o_strcasecmp
 * a modified strcasecmp function that don't crash when p1 is NULL or p2 us NULL
 */
int o_strcasecmp(const char * p1, const char * p2) {
  if (p1 == NULL && p2 == NULL) {
    return 0;
  } else if (p1 != NULL && p2 == NULL) {
    return -1;
  } else if (p1 == NULL && p2 != NULL) {
    return 1;
  } else {
    return strcasecmp(p1, p2);
  }
}

/**
 * o_strncasecmp
 * a modified strncasecmp function that don't crash when p1 is NULL or p2 us NULL
 */
int o_strncasecmp(const char * p1, const char * p2, size_t n) {
  if ((p1 == NULL && p2 == NULL) || n <= 0) {
    return 0;
  } else if (p1 != NULL && p2 == NULL) {
    return -1;
  } else if (p1 == NULL && p2 != NULL) {
    return 1;
  } else {
    return strncasecmp(p1, p2, n);
  }
}

/**
 * o_strchr
 * a modified strchr function that don't crash when haystack is NULL
 */
char * o_strchr(const char * haystack, int c) {
  if (haystack == NULL) {
    return NULL;
  } else {
    return strchr(haystack, c);
  }
}

/**
 * o_strlen
 * a modified version of strlen that don't crash when s is NULL
 */
size_t o_strlen(const char * s) {
  if (s == NULL) {
    return 0;
  } else {
    return strlen(s);
  }
}

/**
 * Remove string of beginning and ending whitespaces
 */
char * trimwhitespace(char * str) {
  char * end;

  if (str == NULL) {
    return NULL;
  } else if(*str == 0) {
    return str;
  }

  while(isspace((unsigned char)*str)) str++;

  end = str + o_strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) {
    end--;
  }

  *(end+1) = 0;

  return str;
}

/**
 * Remove string of beginning and ending given character
 */
char * trimcharacter(char * str, char to_remove) {
  char * end;

  if (str == NULL) {
    return NULL;
  } else if(*str == 0) {
    return str;
  }

  while(*str == to_remove) str++;

  end = str + o_strlen(str) - 1;
  while(end > str && (*end == to_remove)) {
    end--;
  }

  *(end+1) = 0;

  return str;
}
