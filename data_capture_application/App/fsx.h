/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jul 02 14:28:56 2004
 */
/* Compiler settings for E:\Dev\Win\Fsxview\fsx.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __fsx_h__
#define __fsx_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICallClient_FWD_DEFINED__
#define __ICallClient_FWD_DEFINED__
typedef interface ICallClient ICallClient;
#endif 	/* __ICallClient_FWD_DEFINED__ */


#ifndef __ICustom_FWD_DEFINED__
#define __ICustom_FWD_DEFINED__
typedef interface ICustom ICustom;
#endif 	/* __ICustom_FWD_DEFINED__ */


#ifndef __IFsxDispatch_FWD_DEFINED__
#define __IFsxDispatch_FWD_DEFINED__
typedef interface IFsxDispatch IFsxDispatch;
#endif 	/* __IFsxDispatch_FWD_DEFINED__ */


#ifndef __FsxCom_FWD_DEFINED__
#define __FsxCom_FWD_DEFINED__

#ifdef __cplusplus
typedef class FsxCom FsxCom;
#else
typedef struct FsxCom FsxCom;
#endif /* __cplusplus */

#endif 	/* __FsxCom_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_fsx_0000 */
/* [local] */ 


enum WINDOWTYPE
    {	REAL_TIME	= 0,
	MOVIE	= REAL_TIME + 1,
	REAL_MOVIE	= MOVIE + 1,
	GRAPH	= REAL_MOVIE + 1,
	TAM_GRAPH	= GRAPH + 1,
	TAM_TABLE	= TAM_GRAPH + 1,
	VIDEO	= TAM_TABLE + 1,
	TAM_EVENT	= VIDEO + 1,
	ALL_WINDOWS	= TAM_EVENT + 1
    };

enum IMAGETYPE
    {	BMP	= 0,
	JPG	= BMP + 1,
	PCX	= JPG + 1,
	TGA	= PCX + 1,
	TIF	= TGA + 1
    };


extern RPC_IF_HANDLE __MIDL_itf_fsx_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_fsx_0000_v0_0_s_ifspec;

#ifndef __ICallClient_INTERFACE_DEFINED__
#define __ICallClient_INTERFACE_DEFINED__

/* interface ICallClient */
/* [helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICallClient;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("388F0262-C61B-11d4-B729-00A0CC56138A")
    ICallClient : public IUnknown
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OnRTDataReady( 
            /* [in] */ int iRow,
            /* [in] */ int iCol,
            /* [size_is][in] */ byte __RPC_FAR *pData) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CurRTTerminated( 
            /* [in] */ int c_SizeWin,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindows) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OnRTBitmapReady( 
            /* [in] */ int bmType,
            /* [in] */ int bmWidth,
            /* [in] */ int bmHeight,
            /* [in] */ int bmWidthBytes,
            /* [in] */ short bmPlanes,
            /* [in] */ short bmBitsPixel,
            /* [size_is][in] */ byte __RPC_FAR *bmBits) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OnCalRTDataReady( 
            /* [in] */ int iRow,
            /* [in] */ int iCol,
            /* [size_is][in] */ float __RPC_FAR *pData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICallClientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICallClient __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICallClient __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICallClient __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnRTDataReady )( 
            ICallClient __RPC_FAR * This,
            /* [in] */ int iRow,
            /* [in] */ int iCol,
            /* [size_is][in] */ byte __RPC_FAR *pData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CurRTTerminated )( 
            ICallClient __RPC_FAR * This,
            /* [in] */ int c_SizeWin,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindows);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnRTBitmapReady )( 
            ICallClient __RPC_FAR * This,
            /* [in] */ int bmType,
            /* [in] */ int bmWidth,
            /* [in] */ int bmHeight,
            /* [in] */ int bmWidthBytes,
            /* [in] */ short bmPlanes,
            /* [in] */ short bmBitsPixel,
            /* [size_is][in] */ byte __RPC_FAR *bmBits);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnCalRTDataReady )( 
            ICallClient __RPC_FAR * This,
            /* [in] */ int iRow,
            /* [in] */ int iCol,
            /* [size_is][in] */ float __RPC_FAR *pData);
        
        END_INTERFACE
    } ICallClientVtbl;

    interface ICallClient
    {
        CONST_VTBL struct ICallClientVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICallClient_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICallClient_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICallClient_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICallClient_OnRTDataReady(This,iRow,iCol,pData)	\
    (This)->lpVtbl -> OnRTDataReady(This,iRow,iCol,pData)

#define ICallClient_CurRTTerminated(This,c_SizeWin,pWindows)	\
    (This)->lpVtbl -> CurRTTerminated(This,c_SizeWin,pWindows)

#define ICallClient_OnRTBitmapReady(This,bmType,bmWidth,bmHeight,bmWidthBytes,bmPlanes,bmBitsPixel,bmBits)	\
    (This)->lpVtbl -> OnRTBitmapReady(This,bmType,bmWidth,bmHeight,bmWidthBytes,bmPlanes,bmBitsPixel,bmBits)

#define ICallClient_OnCalRTDataReady(This,iRow,iCol,pData)	\
    (This)->lpVtbl -> OnCalRTDataReady(This,iRow,iCol,pData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE ICallClient_OnRTDataReady_Proxy( 
    ICallClient __RPC_FAR * This,
    /* [in] */ int iRow,
    /* [in] */ int iCol,
    /* [size_is][in] */ byte __RPC_FAR *pData);


void __RPC_STUB ICallClient_OnRTDataReady_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICallClient_CurRTTerminated_Proxy( 
    ICallClient __RPC_FAR * This,
    /* [in] */ int c_SizeWin,
    /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindows);


void __RPC_STUB ICallClient_CurRTTerminated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICallClient_OnRTBitmapReady_Proxy( 
    ICallClient __RPC_FAR * This,
    /* [in] */ int bmType,
    /* [in] */ int bmWidth,
    /* [in] */ int bmHeight,
    /* [in] */ int bmWidthBytes,
    /* [in] */ short bmPlanes,
    /* [in] */ short bmBitsPixel,
    /* [size_is][in] */ byte __RPC_FAR *bmBits);


void __RPC_STUB ICallClient_OnRTBitmapReady_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICallClient_OnCalRTDataReady_Proxy( 
    ICallClient __RPC_FAR * This,
    /* [in] */ int iRow,
    /* [in] */ int iCol,
    /* [size_is][in] */ float __RPC_FAR *pData);


void __RPC_STUB ICallClient_OnCalRTDataReady_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICallClient_INTERFACE_DEFINED__ */


#ifndef __ICustom_INTERFACE_DEFINED__
#define __ICustom_INTERFACE_DEFINED__

/* interface ICustom */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICustom;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("388F0260-C61B-11d4-B729-00A0CC56138A")
    ICustom : public IUnknown
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetFrameData( 
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [in] */ boolean bEquil,
            /* [in][out] */ int __RPC_FAR *pSizeInOut,
            /* [size_is][out] */ unsigned char __RPC_FAR *pData) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RequestRealTimeData( 
            /* [in] */ ICallClient __RPC_FAR *pCallback,
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [in] */ boolean bEquil) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DeactivateCallback( 
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE StopCallbackTransfer( 
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetOpenedWindowNames( 
            /* [out][in] */ int __RPC_FAR *pSize,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *pWindows,
            /* [out] */ int __RPC_FAR *pWinNumber,
            /* [in] */ enum WINDOWTYPE eWindowType) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetCurrentSizePresssureUnits( 
            /* [in] */ int c_SizeWin,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [out][in] */ int __RPC_FAR *pUnitSize,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *pSizePressUnits) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetWindowMapSize( 
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [out] */ int __RPC_FAR *pRow,
            /* [out] */ int __RPC_FAR *pCol) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetWindowPixelSize( 
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [out] */ float __RPC_FAR *pXSize,
            /* [out] */ float __RPC_FAR *pYSize) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetErrorMessage( 
            /* [in] */ int c_Error,
            /* [out][in] */ int __RPC_FAR *pBuffSize,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *pMessage) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetWindowSnapShotInfo( 
            /* [in] */ int c_SizeWindow,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [in] */ int c_Size2dViewFileName,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *p2dViewFileName,
            /* [in] */ int c_Size2dCtViewFileName,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *p2dCtViewFileName,
            /* [in] */ int c_Size3dViewFileName,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *p3dViewFileName,
            /* [in] */ int c_SizeLegendFileName,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *pLegendFileName,
            /* [out] */ float __RPC_FAR *pArea,
            /* [out] */ float __RPC_FAR *pForce,
            /* [out] */ float __RPC_FAR *pMinPress,
            /* [out] */ float __RPC_FAR *pMaxPress,
            /* [in] */ enum IMAGETYPE eImageType,
            /* [in] */ int c_SizeASCIIFileName,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *pASCIIFileName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RequestRealTimeImage( 
            /* [in] */ ICallClient __RPC_FAR *pCallback,
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RequestCalRealTimeData( 
            /* [in] */ ICallClient __RPC_FAR *pCallback,
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [in] */ boolean bEquil) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetCalFrameData( 
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [in] */ boolean bEquil,
            /* [in][out] */ int __RPC_FAR *pSizeInOut,
            /* [size_is][out] */ float __RPC_FAR *pfData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICustomVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICustom __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICustom __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICustom __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFrameData )( 
            ICustom __RPC_FAR * This,
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [in] */ boolean bEquil,
            /* [in][out] */ int __RPC_FAR *pSizeInOut,
            /* [size_is][out] */ unsigned char __RPC_FAR *pData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestRealTimeData )( 
            ICustom __RPC_FAR * This,
            /* [in] */ ICallClient __RPC_FAR *pCallback,
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [in] */ boolean bEquil);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeactivateCallback )( 
            ICustom __RPC_FAR * This,
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopCallbackTransfer )( 
            ICustom __RPC_FAR * This,
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOpenedWindowNames )( 
            ICustom __RPC_FAR * This,
            /* [out][in] */ int __RPC_FAR *pSize,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *pWindows,
            /* [out] */ int __RPC_FAR *pWinNumber,
            /* [in] */ enum WINDOWTYPE eWindowType);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentSizePresssureUnits )( 
            ICustom __RPC_FAR * This,
            /* [in] */ int c_SizeWin,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [out][in] */ int __RPC_FAR *pUnitSize,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *pSizePressUnits);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWindowMapSize )( 
            ICustom __RPC_FAR * This,
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [out] */ int __RPC_FAR *pRow,
            /* [out] */ int __RPC_FAR *pCol);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWindowPixelSize )( 
            ICustom __RPC_FAR * This,
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [out] */ float __RPC_FAR *pXSize,
            /* [out] */ float __RPC_FAR *pYSize);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorMessage )( 
            ICustom __RPC_FAR * This,
            /* [in] */ int c_Error,
            /* [out][in] */ int __RPC_FAR *pBuffSize,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *pMessage);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWindowSnapShotInfo )( 
            ICustom __RPC_FAR * This,
            /* [in] */ int c_SizeWindow,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [in] */ int c_Size2dViewFileName,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *p2dViewFileName,
            /* [in] */ int c_Size2dCtViewFileName,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *p2dCtViewFileName,
            /* [in] */ int c_Size3dViewFileName,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *p3dViewFileName,
            /* [in] */ int c_SizeLegendFileName,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *pLegendFileName,
            /* [out] */ float __RPC_FAR *pArea,
            /* [out] */ float __RPC_FAR *pForce,
            /* [out] */ float __RPC_FAR *pMinPress,
            /* [out] */ float __RPC_FAR *pMaxPress,
            /* [in] */ enum IMAGETYPE eImageType,
            /* [in] */ int c_SizeASCIIFileName,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *pASCIIFileName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestRealTimeImage )( 
            ICustom __RPC_FAR * This,
            /* [in] */ ICallClient __RPC_FAR *pCallback,
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestCalRealTimeData )( 
            ICustom __RPC_FAR * This,
            /* [in] */ ICallClient __RPC_FAR *pCallback,
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [in] */ boolean bEquil);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCalFrameData )( 
            ICustom __RPC_FAR * This,
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [in] */ boolean bEquil,
            /* [in][out] */ int __RPC_FAR *pSizeInOut,
            /* [size_is][out] */ float __RPC_FAR *pfData);
        
        END_INTERFACE
    } ICustomVtbl;

    interface ICustom
    {
        CONST_VTBL struct ICustomVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICustom_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICustom_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICustom_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICustom_GetFrameData(This,c_Size,pWindow,bEquil,pSizeInOut,pData)	\
    (This)->lpVtbl -> GetFrameData(This,c_Size,pWindow,bEquil,pSizeInOut,pData)

#define ICustom_RequestRealTimeData(This,pCallback,c_Size,pWindow,bEquil)	\
    (This)->lpVtbl -> RequestRealTimeData(This,pCallback,c_Size,pWindow,bEquil)

#define ICustom_DeactivateCallback(This,c_Size,pWindow)	\
    (This)->lpVtbl -> DeactivateCallback(This,c_Size,pWindow)

#define ICustom_StopCallbackTransfer(This,c_Size,pWindow)	\
    (This)->lpVtbl -> StopCallbackTransfer(This,c_Size,pWindow)

#define ICustom_GetOpenedWindowNames(This,pSize,pWindows,pWinNumber,eWindowType)	\
    (This)->lpVtbl -> GetOpenedWindowNames(This,pSize,pWindows,pWinNumber,eWindowType)

#define ICustom_GetCurrentSizePresssureUnits(This,c_SizeWin,pWindow,pUnitSize,pSizePressUnits)	\
    (This)->lpVtbl -> GetCurrentSizePresssureUnits(This,c_SizeWin,pWindow,pUnitSize,pSizePressUnits)

#define ICustom_GetWindowMapSize(This,c_Size,pWindow,pRow,pCol)	\
    (This)->lpVtbl -> GetWindowMapSize(This,c_Size,pWindow,pRow,pCol)

#define ICustom_GetWindowPixelSize(This,c_Size,pWindow,pXSize,pYSize)	\
    (This)->lpVtbl -> GetWindowPixelSize(This,c_Size,pWindow,pXSize,pYSize)

#define ICustom_GetErrorMessage(This,c_Error,pBuffSize,pMessage)	\
    (This)->lpVtbl -> GetErrorMessage(This,c_Error,pBuffSize,pMessage)

#define ICustom_GetWindowSnapShotInfo(This,c_SizeWindow,pWindow,c_Size2dViewFileName,p2dViewFileName,c_Size2dCtViewFileName,p2dCtViewFileName,c_Size3dViewFileName,p3dViewFileName,c_SizeLegendFileName,pLegendFileName,pArea,pForce,pMinPress,pMaxPress,eImageType,c_SizeASCIIFileName,pASCIIFileName)	\
    (This)->lpVtbl -> GetWindowSnapShotInfo(This,c_SizeWindow,pWindow,c_Size2dViewFileName,p2dViewFileName,c_Size2dCtViewFileName,p2dCtViewFileName,c_Size3dViewFileName,p3dViewFileName,c_SizeLegendFileName,pLegendFileName,pArea,pForce,pMinPress,pMaxPress,eImageType,c_SizeASCIIFileName,pASCIIFileName)

#define ICustom_RequestRealTimeImage(This,pCallback,c_Size,pWindow)	\
    (This)->lpVtbl -> RequestRealTimeImage(This,pCallback,c_Size,pWindow)

#define ICustom_RequestCalRealTimeData(This,pCallback,c_Size,pWindow,bEquil)	\
    (This)->lpVtbl -> RequestCalRealTimeData(This,pCallback,c_Size,pWindow,bEquil)

#define ICustom_GetCalFrameData(This,c_Size,pWindow,bEquil,pSizeInOut,pfData)	\
    (This)->lpVtbl -> GetCalFrameData(This,c_Size,pWindow,bEquil,pSizeInOut,pfData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE ICustom_GetFrameData_Proxy( 
    ICustom __RPC_FAR * This,
    /* [in] */ int c_Size,
    /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
    /* [in] */ boolean bEquil,
    /* [in][out] */ int __RPC_FAR *pSizeInOut,
    /* [size_is][out] */ unsigned char __RPC_FAR *pData);


void __RPC_STUB ICustom_GetFrameData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICustom_RequestRealTimeData_Proxy( 
    ICustom __RPC_FAR * This,
    /* [in] */ ICallClient __RPC_FAR *pCallback,
    /* [in] */ int c_Size,
    /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
    /* [in] */ boolean bEquil);


void __RPC_STUB ICustom_RequestRealTimeData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICustom_DeactivateCallback_Proxy( 
    ICustom __RPC_FAR * This,
    /* [in] */ int c_Size,
    /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow);


void __RPC_STUB ICustom_DeactivateCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICustom_StopCallbackTransfer_Proxy( 
    ICustom __RPC_FAR * This,
    /* [in] */ int c_Size,
    /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow);


void __RPC_STUB ICustom_StopCallbackTransfer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICustom_GetOpenedWindowNames_Proxy( 
    ICustom __RPC_FAR * This,
    /* [out][in] */ int __RPC_FAR *pSize,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *pWindows,
    /* [out] */ int __RPC_FAR *pWinNumber,
    /* [in] */ enum WINDOWTYPE eWindowType);


void __RPC_STUB ICustom_GetOpenedWindowNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICustom_GetCurrentSizePresssureUnits_Proxy( 
    ICustom __RPC_FAR * This,
    /* [in] */ int c_SizeWin,
    /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
    /* [out][in] */ int __RPC_FAR *pUnitSize,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *pSizePressUnits);


void __RPC_STUB ICustom_GetCurrentSizePresssureUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICustom_GetWindowMapSize_Proxy( 
    ICustom __RPC_FAR * This,
    /* [in] */ int c_Size,
    /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
    /* [out] */ int __RPC_FAR *pRow,
    /* [out] */ int __RPC_FAR *pCol);


void __RPC_STUB ICustom_GetWindowMapSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICustom_GetWindowPixelSize_Proxy( 
    ICustom __RPC_FAR * This,
    /* [in] */ int c_Size,
    /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
    /* [out] */ float __RPC_FAR *pXSize,
    /* [out] */ float __RPC_FAR *pYSize);


void __RPC_STUB ICustom_GetWindowPixelSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICustom_GetErrorMessage_Proxy( 
    ICustom __RPC_FAR * This,
    /* [in] */ int c_Error,
    /* [out][in] */ int __RPC_FAR *pBuffSize,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *pMessage);


void __RPC_STUB ICustom_GetErrorMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICustom_GetWindowSnapShotInfo_Proxy( 
    ICustom __RPC_FAR * This,
    /* [in] */ int c_SizeWindow,
    /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
    /* [in] */ int c_Size2dViewFileName,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *p2dViewFileName,
    /* [in] */ int c_Size2dCtViewFileName,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *p2dCtViewFileName,
    /* [in] */ int c_Size3dViewFileName,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *p3dViewFileName,
    /* [in] */ int c_SizeLegendFileName,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *pLegendFileName,
    /* [out] */ float __RPC_FAR *pArea,
    /* [out] */ float __RPC_FAR *pForce,
    /* [out] */ float __RPC_FAR *pMinPress,
    /* [out] */ float __RPC_FAR *pMaxPress,
    /* [in] */ enum IMAGETYPE eImageType,
    /* [in] */ int c_SizeASCIIFileName,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *pASCIIFileName);


void __RPC_STUB ICustom_GetWindowSnapShotInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICustom_RequestRealTimeImage_Proxy( 
    ICustom __RPC_FAR * This,
    /* [in] */ ICallClient __RPC_FAR *pCallback,
    /* [in] */ int c_Size,
    /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow);


void __RPC_STUB ICustom_RequestRealTimeImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICustom_RequestCalRealTimeData_Proxy( 
    ICustom __RPC_FAR * This,
    /* [in] */ ICallClient __RPC_FAR *pCallback,
    /* [in] */ int c_Size,
    /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
    /* [in] */ boolean bEquil);


void __RPC_STUB ICustom_RequestCalRealTimeData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICustom_GetCalFrameData_Proxy( 
    ICustom __RPC_FAR * This,
    /* [in] */ int c_Size,
    /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
    /* [in] */ boolean bEquil,
    /* [in][out] */ int __RPC_FAR *pSizeInOut,
    /* [size_is][out] */ float __RPC_FAR *pfData);


void __RPC_STUB ICustom_GetCalFrameData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICustom_INTERFACE_DEFINED__ */


#ifndef __IFsxDispatch_INTERFACE_DEFINED__
#define __IFsxDispatch_INTERFACE_DEFINED__

/* interface IFsxDispatch */
/* [oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFsxDispatch;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("388F0261-C61B-11d4-B729-00A0CC56138A")
    IFsxDispatch : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetFrameData( 
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [in] */ boolean bEquil,
            /* [in][out] */ int __RPC_FAR *pSizeInOut,
            /* [size_is][out] */ unsigned char __RPC_FAR *pData) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetOpenedWindowNames( 
            /* [out][in] */ int __RPC_FAR *pSize,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *pWindows,
            /* [out] */ int __RPC_FAR *pWinNumber,
            /* [in] */ enum WINDOWTYPE eType) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetCurrentSizePresssureUnits( 
            /* [in] */ int c_SizeWin,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [out][in] */ int __RPC_FAR *pUnitSize,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *pSizePressUnits) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFsxDispatchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFsxDispatch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFsxDispatch __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFsxDispatch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IFsxDispatch __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IFsxDispatch __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IFsxDispatch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IFsxDispatch __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFrameData )( 
            IFsxDispatch __RPC_FAR * This,
            /* [in] */ int c_Size,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [in] */ boolean bEquil,
            /* [in][out] */ int __RPC_FAR *pSizeInOut,
            /* [size_is][out] */ unsigned char __RPC_FAR *pData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOpenedWindowNames )( 
            IFsxDispatch __RPC_FAR * This,
            /* [out][in] */ int __RPC_FAR *pSize,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *pWindows,
            /* [out] */ int __RPC_FAR *pWinNumber,
            /* [in] */ enum WINDOWTYPE eType);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentSizePresssureUnits )( 
            IFsxDispatch __RPC_FAR * This,
            /* [in] */ int c_SizeWin,
            /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
            /* [out][in] */ int __RPC_FAR *pUnitSize,
            /* [size_is][string][out] */ unsigned char __RPC_FAR *pSizePressUnits);
        
        END_INTERFACE
    } IFsxDispatchVtbl;

    interface IFsxDispatch
    {
        CONST_VTBL struct IFsxDispatchVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFsxDispatch_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFsxDispatch_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFsxDispatch_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFsxDispatch_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IFsxDispatch_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IFsxDispatch_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IFsxDispatch_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IFsxDispatch_GetFrameData(This,c_Size,pWindow,bEquil,pSizeInOut,pData)	\
    (This)->lpVtbl -> GetFrameData(This,c_Size,pWindow,bEquil,pSizeInOut,pData)

#define IFsxDispatch_GetOpenedWindowNames(This,pSize,pWindows,pWinNumber,eType)	\
    (This)->lpVtbl -> GetOpenedWindowNames(This,pSize,pWindows,pWinNumber,eType)

#define IFsxDispatch_GetCurrentSizePresssureUnits(This,c_SizeWin,pWindow,pUnitSize,pSizePressUnits)	\
    (This)->lpVtbl -> GetCurrentSizePresssureUnits(This,c_SizeWin,pWindow,pUnitSize,pSizePressUnits)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IFsxDispatch_GetFrameData_Proxy( 
    IFsxDispatch __RPC_FAR * This,
    /* [in] */ int c_Size,
    /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
    /* [in] */ boolean bEquil,
    /* [in][out] */ int __RPC_FAR *pSizeInOut,
    /* [size_is][out] */ unsigned char __RPC_FAR *pData);


void __RPC_STUB IFsxDispatch_GetFrameData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IFsxDispatch_GetOpenedWindowNames_Proxy( 
    IFsxDispatch __RPC_FAR * This,
    /* [out][in] */ int __RPC_FAR *pSize,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *pWindows,
    /* [out] */ int __RPC_FAR *pWinNumber,
    /* [in] */ enum WINDOWTYPE eType);


void __RPC_STUB IFsxDispatch_GetOpenedWindowNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IFsxDispatch_GetCurrentSizePresssureUnits_Proxy( 
    IFsxDispatch __RPC_FAR * This,
    /* [in] */ int c_SizeWin,
    /* [size_is][string][in] */ unsigned char __RPC_FAR *pWindow,
    /* [out][in] */ int __RPC_FAR *pUnitSize,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *pSizePressUnits);


void __RPC_STUB IFsxDispatch_GetCurrentSizePresssureUnits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFsxDispatch_INTERFACE_DEFINED__ */



#ifndef __FsxViewLib_LIBRARY_DEFINED__
#define __FsxViewLib_LIBRARY_DEFINED__

/* library FsxViewLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_FsxViewLib;

EXTERN_C const CLSID CLSID_FsxCom;

#ifdef __cplusplus

class DECLSPEC_UUID("388F0265-C61B-11d4-B729-00A0CC56138A")
FsxCom;
#endif
#endif /* __FsxViewLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
