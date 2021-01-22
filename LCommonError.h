#ifndef LCOMMONERROR_H
#define LCOMMONERROR_H

namespace LStatus {

    //! Error info mapping
    struct ErrorInfo {
        int             iErrorCode;
        const QString   strDescription;
    };

    //! Enumeration of the error code
    enum ErrorCode {
        EC_NO_ERROR = 0,

        // Section for comm ports
        EC_PORT_CONFIG,
        EC_PORT_OPEN_FAIL,

        // End of error definitions
        EC_UNKNOWN
    };

    static ErrorInfo s_aErrorInfoTable[] = {
        { EC_NO_ERROR          , "OK"                                   },
        // Some stuff
        { EC_PORT_CONFIG       , "Invalid port configuration"           },
        { EC_PORT_CONFIG       , "Invalid port configuration"           },
        // Some other stuff
        { EC_UNKNOWN           , ""                                     }
    };

    static int s_szErrorInfoTable = sizeof(s_aErrorInfoTable) / sizeof(ErrorInfo);

    //! Get the error description from input error code
    static const QString &getErrorInfo(int iErrorCode)
    {
        // Implement it better later
        for (int i = 0; i < s_szErrorInfoTable; ++i) {
            if (s_aErrorInfoTable[i].iErrorCode == iErrorCode) {
                return s_aErrorInfoTable[i].strDescription;
            }
        }

        return s_aErrorInfoTable[EC_UNKNOWN].strDescription;
    }
}



#endif // LCOMMONERROR_H
