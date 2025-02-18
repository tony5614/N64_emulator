#pragma once

typedef unsigned char       U8;
typedef unsigned short      U16;
typedef unsigned int        U32;
typedef unsigned long long  U64;


#define ASSERT(ERR_MSG, X)      if(!(X))\
                               {\
                                   volatile int _hang = true;\
                                   printf("%s\n",ERR_MSG);\
                                    while(_hang);\
                               }

