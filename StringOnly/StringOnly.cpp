// StringOnly.cpp : Testing without MFC and CString
//
#include <stdio.h>
#include <tchar.h>
#include "SMX_String.h"

int main()
{
    String before("Example");
    String after("@Holland");

    String second = before + after;
    String third  = second.Left(4);

    printf("%s: %s\n",(char*)third,(char*)second);             // SMX
    printf("%s: %s\n",third.c_str(),second.c_str());           // The std::string way of doing it
    printf("%s: %s\n",third.GetString(),second.GetString());   // The MFC way of doing it.
  //printf("%s: %s\n",third,second);   WILL NEVER WORK! IT's NOT CString!!

    return 0;
}
