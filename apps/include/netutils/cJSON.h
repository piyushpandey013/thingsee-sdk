/****************************************************************************
 * apps/netutils/json/cJSON.c
 *
 * This file is a part of NuttX:
 *
 *   Copyright (C) 2011 Gregory Nutt. All rights reserved.
 *   Ported by: Darcy Gong
 *
 * And derives from the cJSON Project which has an MIT license:
 *
 *   Copyright (c) 2009 Dave Gamble
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 ****************************************************************************/

#ifndef __APPS_INCLUDE_NETUTILS_JSON_H
#define __APPS_INCLUDE_NETUTILS_JSON_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define cJSON_False  0
#define cJSON_True   1
#define cJSON_NULL   2
#define cJSON_Number 3
#define cJSON_String 4
#define cJSON_Array  5
#define cJSON_Object 6

#define cJSON_IsReference 256

#define cJSON_AddNullToObject(object,name) \
  cJSON_AddItemToObject(object, name, cJSON_CreateNull())
#define cJSON_AddTrueToObject(object,name) \
  cJSON_AddItemToObject(object, name, cJSON_CreateTrue())cd
#define cJSON_AddFalseToObject(object,name) \
  cJSON_AddItemToObject(object, name, cJSON_CreateFalse())
#define cJSON_AddNumberToObject(object,name,n) \
  cJSON_AddItemToObject(object, name, cJSON_CreateNumber(n))
#define cJSON_AddStringToObject(object,name,s) \
  cJSON_AddItemToObject(object, name, cJSON_CreateString(s))

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* The cJSON structure: */

typedef struct cJSON
{
  /* next/prev allow you to walk array/object chains. Alternatively, use
   * GetArraySize/GetArrayItem/GetObjectItem
   */

  struct cJSON *next,*prev;

  /* An array or object item will have a child pointer pointing to a chain
   * of the items in the array/object.
   */

  struct cJSON *child;

  int type;               /* The type of the item, as above. */
  char *valuestring;      /* The item's string, if type==cJSON_String */
  int valueint;           /* The item's number, if type==cJSON_Number */
  double valuedouble;     /* The item's number, if type==cJSON_Number */

  /* The item's name string, if this item is the child of, or is in the list
   * of subitems of an object.
   */

  char *string;
} cJSON;

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/* Supply a block of JSON, and this returns a cJSON object you can
 * interrogate. Call cJSON_Delete when finished.
 */

cJSON *cJSON_Parse(const char *value);

/* Supply a stream of JSON, and this returns a cJSON object you can
 * interrogate. Call cJSON_Delete when finished.
 */

cJSON *cJSON_Parse_Stream(char (*getc_fn)(void *priv), void *priv);

/* Render a cJSON entity to text for transfer/storage. Free the char* when
 * finished.
 */

char *cJSON_Print(cJSON *item);

/* Render a cJSON entity to text for transfer/storage without any
 * formatting. Free the char* when finished.
 */

char *cJSON_PrintUnformatted(cJSON *item);

/* Render a cJSON entity to text for transfer/storage with or without
 * formatting.
 */

void cJSON_Print_Stream(cJSON *item, bool formatted,
                        void (*putc_fn)(char c, void *priv), void *putc_priv);

/* Render a cJSON item/entity/structure to buffer. */

size_t cJSON_Print_Buf(cJSON *item, bool formatted, char *buf, size_t buflen);

/* Delete a cJSON entity and all subentities. */

void cJSON_Delete(cJSON *c);

/* Returns the number of items in an array (or object). */

int cJSON_GetArraySize(cJSON *array);

/* Retrieve item number "item" from array "array". Returns NULL if
 * unsuccessful.
 */

cJSON *cJSON_GetArrayItem(cJSON *array, int item);

/* Get item "string" from object. Case insensitive. */

cJSON *cJSON_GetObjectItem(cJSON *object, const char *string);

/* For analysing failed parses. This returns a pointer to the parse error.
 * You'll probably need to look a few chars back to make sense of it.
 * Defined when cJSON_Parse() returns 0. 0 when cJSON_Parse() succeeds.
 */

const char *cJSON_GetErrorPtr(void);

/* These calls create a cJSON item of the appropriate type. */

cJSON *cJSON_CreateNull(void);
cJSON *cJSON_CreateTrue(void);
cJSON *cJSON_CreateFalse(void);
cJSON *cJSON_CreateBool(int b);
cJSON *cJSON_CreateNumber(double num);
cJSON *cJSON_CreateString(const char *string);
cJSON *cJSON_CreateArray(void);
cJSON *cJSON_CreateObject(void);
cJSON *cJSON_New_Item(void);

/* These utilities create an Array of count items. */

cJSON *cJSON_CreateIntArray(const int *numbers, int count);
cJSON *cJSON_CreateFloatArray(const float *numbers, int count);
cJSON *cJSON_CreateDoubleArray(const double *numbers, int count);
cJSON *cJSON_CreateStringArray(const char **strings, int count);

/* Append item to the specified array/object. */

void cJSON_AddItemToArray(cJSON *array, cJSON *item);
void cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);

/* Append reference to item to the specified array/object. Use this when you
 * want to add an existing cJSON to a new cJSON, but don't want to corrupt
 * your existing cJSON.
 */

void cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item);
void cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item);

/* Remove/Detatch items from Arrays/Objects. */

cJSON *cJSON_DetachItemFromArray(cJSON *array, int which);
void cJSON_DeleteItemFromArray(cJSON *array, int which);
cJSON *cJSON_DetachItemFromObject(cJSON *object, const char *string);
void cJSON_DeleteItemFromObject(cJSON *object, const char *string);

/* Update array items. */

void cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem);
void cJSON_ReplaceItemInObject(cJSON *object, const char *string, cJSON *newitem);

#ifdef __cplusplus
}
#endif

#endif /* __APPS_INCLUDE_NETUTILS_JSON_H */
