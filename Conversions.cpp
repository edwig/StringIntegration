#include "Conversions.h"

#ifdef _UNICODE
// in UNICODE settings these two functions are placeholders!
std::wstring
StringToWString(const XString& p_string)
{
  return std::wstring(p_string.GetString());
}

XString
WStringToString(const std::wstring& p_string)
{
  return XString(p_string.c_str());
}
#else
// Convert directly between XString and std::wstring
// Thus removing the need for the "USES_CONVERSION" macros
std::wstring
StringToWString(const XString& p_string)
{
  std::wstring result;      // Nothing yet
  UINT codePage = GetACP(); // Default the current codepage
  int    length = -1;       // I think it will be null terminated

  // Getting the length of the buffer, by specifying no output
  length = MultiByteToWideChar(codePage
                               ,MB_PRECOMPOSED
                               ,p_string.GetString()
                               ,-1 // p_string.GetLength()
                               ,NULL
                               ,0);
  if(length)
  {
    // Getting a UTF-16 wide-character buffer
    // +2 chars for a BOM, +2 chars for the closing zeros
    BYTE* buffer = new BYTE[2 * (size_t)length + 4];

    // Doing the 'real' conversion
    length = MultiByteToWideChar(codePage
                                 ,MB_PRECOMPOSED
                                 ,p_string.GetString()
                                 ,-1 // p_string.GetLength()
                                 ,reinterpret_cast<LPWSTR>(buffer)
                                 ,length);
    if(length > 0)
    {
      // Buffer length is twice the number of logical characters
      length *= 2;
      // UTF-16 has two closing zeros
//       buffer[length    ] = 0;
//       buffer[length + 1] = 0;

      result = reinterpret_cast<LPWSTR>(buffer);
    }
    delete[] buffer;
  }
  return result;
}

XString
WStringToString(const std::wstring& p_string)
{
  UINT codePage = GetACP(); // Default is to use the current codepage
  int    length = -1;       // I think it will be null terminated
  XString result;

  // Getting the length of the translation buffer first
  length = ::WideCharToMultiByte(codePage,
                                 0,
                                 p_string.c_str(),
                                 -1, // p_length, 
                                 NULL,
                                 0,
                                 NULL,
                                 NULL);
 // Convert the string if we find something
  if(length > 0)
  {
    length *= 2; // Funny but needed in most cases with 3-byte composite chars
    char* buffer = new char[length];
    if(buffer != NULL)
    {
      DWORD dwFlag = 0; // WC_COMPOSITECHECK | WC_DISCARDNS;
      memset(buffer,0,length * sizeof(char));
      length = ::WideCharToMultiByte(codePage,
                                     dwFlag,
                                     p_string.c_str(),
                                     -1, // p_length, 
                                     reinterpret_cast<LPSTR>(buffer),
                                     length,
                                     NULL,
                                     NULL);
      if(length > 0)
      {
        result = buffer;
      }
      delete[] buffer;
    }
  }
  return result;
}


#endif