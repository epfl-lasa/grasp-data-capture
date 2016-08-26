/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jul 02 14:28:56 2004
 */
/* Compiler settings for E:\Dev\Win\Fsxview\fsx.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_ICallClient = {0x388F0262,0xC61B,0x11d4,{0xB7,0x29,0x00,0xA0,0xCC,0x56,0x13,0x8A}};


const IID IID_ICustom = {0x388F0260,0xC61B,0x11d4,{0xB7,0x29,0x00,0xA0,0xCC,0x56,0x13,0x8A}};


const IID IID_IFsxDispatch = {0x388F0261,0xC61B,0x11d4,{0xB7,0x29,0x00,0xA0,0xCC,0x56,0x13,0x8A}};


const IID LIBID_FsxViewLib = {0x388F0264,0xC61B,0x11d4,{0xB7,0x29,0x00,0xA0,0xCC,0x56,0x13,0x8A}};


const CLSID CLSID_FsxCom = {0x388F0265,0xC61B,0x11d4,{0xB7,0x29,0x00,0xA0,0xCC,0x56,0x13,0x8A}};


#ifdef __cplusplus
}
#endif

