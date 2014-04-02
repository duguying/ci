/*
* Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
* Copyright (C) DIGITEO - 2010 - Allan CORNET
* 
* This file must be used under the terms of the CeCILL.
* This source file is licensed as described in the file COPYING, which
* you should have received as part of this distribution.  The terms
* are also available at    
* http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
*
*/
/*--------------------------------------------------------------------------*/
#ifndef __FORK_WINDOWS_H__
#define __FORK_WINDOWS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* define boolean type */
#ifdef BOOL
#undef BOOL
#endif

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif


#ifndef  _MSC_VER
typedef enum
{
    FALSE = 0,
    TRUE = 1
} BOOL;

#else
/* Please notice that BOOL is defined in <windef.h> */
/* BUT windef.h includes all others windows include */
/* it is better to redefine as */
typedef int BOOL;
#define FALSE 0
#define TRUE 1

#endif
/* converts BOOL to bool */
#define BOOLtobool(w)     ((w != FALSE) ? true : false)

/* converts bool to BOOL */
#define booltoBOOL(w)     ((w == true) ? TRUE : FALSE)

/* http://technet.microsoft.com/en-us/library/bb497007.aspx */
/* http://undocumented.ntinternals.net/ */

/**
* simulate fork on Windows 
*/
int fork(void);

/**
* check if symbols to simulate fork are present 
* and load these symbols
*/
BOOL haveLoadedFunctionsForFork(void);

#ifdef __cplusplus
}
#endif 

#endif /* __FORK_WINDOWS_H__ */
/*--------------------------------------------------------------------------*/ 
