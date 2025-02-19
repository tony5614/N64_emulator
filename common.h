#pragma once

typedef unsigned char       U8;  //byte
typedef unsigned short      U16; //halfword
typedef unsigned int        U32; //word
typedef unsigned long long  U64; //double word

#define ASSERT(ERR_MSG, X)      if(!(X))\
                               {\
                                   volatile int _hang = true;\
                                   printf("%s\n",ERR_MSG);\
                                    while(_hang);\
                               }

