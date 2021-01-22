#ifndef LTMCTLWRAPPER_H
#define LTMCTLWRAPPER_H

#include <QLibrary>

typedef int (__stdcall TmcInitialize)( int wire, char* adr, int* id );
typedef int (__stdcall TmcSend)( int id, char* msg ) ;;
typedef int (__stdcall TmcSendByLength)( int id, char* msg, int len );
typedef int (__stdcall TmcReceive)( int id, char* buff, int blen, int* rlen );
typedef int (__stdcall TmcReceiveBlockHeader)( int id, int* len ) ;
typedef int (__stdcall TmcReceiveBlockData)( int id, char* buff, int blen, int* rlen, int* end ) ;

class LTmctlWrapper
{
public:
    LTmctlWrapper();

    TmcInitialize*          initialize;
    TmcSend*                send;
    TmcSendByLength*        sendByLength;
    TmcReceive*             receive;
    TmcReceiveBlockHeader*  receiveBlockHeader;
    TmcReceiveBlockData*    receiveBlockData;

private:
    QLibrary m_library;
};

#endif // LTMCTLWRAPPER_H
