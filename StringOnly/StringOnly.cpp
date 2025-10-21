// StringOnly.cpp : Testing without MFC and CString
//
#include "XString.h"

int main()
{
    XString before(_T("Example"));
    XString after(_T("@Holland"));

    XString second = before + after;
    XString third  = second.Left(4);

    _tprintf(_T("%s: %s\n"),(TCHAR*)third,(TCHAR*)second);            // SMX
    _tprintf(_T("%s: %s\n"),third.c_str(),second.c_str());           // The std::string way of doing it
    _tprintf(_T("%s: %s\n"),third.GetString(),second.GetString());   // The MFC way of doing it.
  //printf("%s: %s\n",third,second);   WILL NEVER WORK! IT's NOT CString!!

    return 0;
}
