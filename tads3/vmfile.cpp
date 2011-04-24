#ifdef RCSID
static char RCSid[] =
"$Header: d:/cvsroot/tads/tads3/VMFILE.CPP,v 1.2 1999/05/17 02:52:28 MJRoberts Exp $";
#endif

/* 
 *   Copyright (c) 1998, 2002 Michael J. Roberts.  All Rights Reserved.
 *   
 *   Please see the accompanying license file, LICENSE.TXT, for information
 *   on using and copying this software.  
 */
/*
Name
  vmfile.cpp - VM file implementation
Function
  
Notes
  
Modified
  10/28/98 MJRoberts  - Creation
*/

#include "t3std.h"
#include "vmfile.h"
#include "vmerr.h"


/*
 *   delete the file object 
 */
CVmFile::~CVmFile()
{
    /* if we still have an underlying OS file, close it */
    if (fp_ != 0)
        osfcls(fp_);
}

/*
 *   open for reading 
 */
void CVmFile::open_read(const char *fname, os_filetype_t typ)
{
    /* try opening the underlying OS file for binary reading */
    fp_ = osfoprb(fname, typ);

    /* if that failed, throw an error */
    if (fp_ == 0)
        err_throw(VMERR_FILE_NOT_FOUND);
}

/*
 *   open for writing 
 */
void CVmFile::open_write(const char *fname, os_filetype_t typ)
{
    /* try opening the underlying OS file for binary writing */
    fp_ = osfopwb(fname, typ);

    /* if that failed, throw an error */
    if (fp_ == 0)
        err_throw(VMERR_CREATE_FILE);
}

/* ------------------------------------------------------------------------ */
/*
 *   Read a line into an allocated buffer 
 */
char *CVmStream::read_line_alo()
{
    char *ret = 0;
    size_t retlen = 0;
    
    /* keep going until we satisfy the request */
    for (;;)
    {
        /* read a chunk; if at EOF, we're done */
        char buf[1024];
        if (read_line(buf, sizeof(buf)) == 0)
            break;

        /* get the length of this chunk */
        size_t len = strlen(buf);

        /* allocate or expand the result buffer to accommodate the new text */
        if (ret == 0)
            ret = (char *)t3malloc(len + 1);
        else
            ret = (char *)t3realloc(ret, retlen + len + 1);

        /* fail if out of memory */
        if (ret == 0)
            return 0;

        /* add the new chunk to the result (including the null) */
        memcpy(ret + retlen, buf, len + 1);
        retlen += len;

        /* if the buffer ends with a newline, we're done */
        if (retlen != 0 && ret[retlen-1] == '\n')
            break;
    }

    /* return our buffer */
    return ret;
}
