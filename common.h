#ifndef COMMON_H
#define COMMON_H

// O ifdef abaixo verifica o sistema operacional, para 
// incluir a biblioteca corretamente
#ifdef __unix__         
    #include <unistd.h>

#elif defined(_WIN32) || defined(WIN32) 

   #define OS_Windows

   #include <windows.h>

#endif

//Incluindo Bibliotecas padrão:
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#endif