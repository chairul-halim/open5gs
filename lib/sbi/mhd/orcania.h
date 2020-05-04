#ifndef __ORCANIA_H__
#define __ORCANIA_H__

#ifdef __cplusplus
extern "C"
{
#endif

void *o_malloc(size_t size);
void *o_realloc(void * ptr, size_t size);
void o_free(void * ptr);

char *o_strdup(const char * source);
char *o_strndup(const char * source, size_t len);

char *trimwhitespace(char * str);
char *trimcharacter(char * str, char to_remove);
char *msprintf(const char * message, ...);

#ifdef __cplusplus
}
#endif

#endif // __ORCANIA_H__
