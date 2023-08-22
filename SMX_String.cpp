//////////////////////////////////////////////////////////////////////////
//
// SMX_String
//
// Std Mfc eXtension (SMX)String is a string derived from std::string
// But does just about everything that MFC CString also does
// The string is derived from std::string with CString methods
// SMX = std::string with MFC eXtensions
//
// Copyright (c) 2016-2017 ir. W.E. Huisman MSC
//
// Permission is hereby granted, free of charge, to any person obtaining a 
// copy of this software and associated documentation files(the "Software"), 
// to deal in the Software without restriction, including without limitation 
// the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and /or sell copies of the Software, and to permit persons to whom the 
// Software is furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included 
// in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
// PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
// THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//////////////////////////////////////////////////////////////////////////

#include "SMX_String.h"
#include <atlbase.h>
#include <WinNls.h>

namespace std
{
  
// Base CTOR
SMX_String::SMX_String()
{
}

// CTOR from character pointer
SMX_String::SMX_String(const TCHAR* p_string)
           :tstring(p_string)
{
}

#ifndef UNICODE
// CTOR from unsigned char
SMX_String::SMX_String(const _TUCHAR* p_string)
{
  append((const TCHAR*)p_string);
}
#endif

// CTOR from a number of characters
SMX_String::SMX_String(TCHAR p_char,int p_count)
{
  append(p_count,p_char);
}

// CTOR from other string
SMX_String::SMX_String(const SMX_String& p_string)
{
  append(p_string.c_str());
}

// CTOR from std::string
SMX_String::SMX_String(const std::tstring& p_string)
           :tstring(p_string)
{
}

BSTR 
SMX_String::AllocSysString()
{
#ifdef UNICODE
  BSTR bstrResult = ::SysAllocString(c_str());
#else
  USES_CONVERSION;
  wstring str(A2CW(this->c_str()));
  BSTR bstrResult = ::SysAllocString(str.c_str());
#endif

  if(bstrResult == NULL)
  {
    throw std::bad_alloc();
  }
  return(bstrResult);
}

// Append a string, or n chars from a string
//
void 
SMX_String::Append(LPCTSTR p_string,int p_length)
{
  tstring str(p_string);
  append(str.substr(0,p_length));
}

// Append a formatted string
void 
SMX_String::AppendFormat(LPCTSTR p_format,...)
{
  va_list argList;
  va_start(argList,p_format);

  AppendFormatV(p_format,argList);

  va_end(argList);
}

void 
SMX_String::AppendFormat(UINT p_strID,...)
{
  va_list argList;
  va_start(argList,p_strID);

  AppendFormatV(p_strID,argList);

  va_end(argList);
}

void 
SMX_String::AppendFormatV(LPCTSTR p_format,va_list p_list)
{
  // Getting a buffer of the correct length
  int len = _vsctprintf(p_format,p_list) + 1;
  TCHAR* buffer = new TCHAR[len];
  // Formatting the parameters
  _vstprintf_s(buffer,len,p_format,p_list);
  // Adding to the string
  append(buffer);

  delete[] buffer;
}

void 
SMX_String::AppendFormatV(UINT p_strID,va_list p_list)
{
  // Getting the string
  SMX_String str;
  if(str.LoadString(p_strID))
  {
    // Getting a buffer of the correct length
    int len = _vsctprintf(str.c_str(),p_list) + 1;
    TCHAR* buffer = new TCHAR[len];
    // Formatting the parameters
    _vstprintf_s(buffer,len,str.c_str(),p_list);
    // Adding to the string
    append(buffer);

    delete[] buffer;
  }
}

// Delete, returning new length
int 
SMX_String::Delete(int p_index,int p_count)
{
  erase(p_index,p_count);
  return (int) length();
}

// Format a string
void 
SMX_String::Format(LPCTSTR p_format,...)
{
  va_list argList;
  va_start(argList,p_format);

  FormatV(p_format,argList);

  va_end(argList);
}

void 
SMX_String::Format(UINT p_strID,...)
{
  va_list argList;
  va_start(argList,p_strID);

  FormatV(p_strID,argList);

  va_end(argList);
}

void
SMX_String::Format(SMX_String p_format,...)
{
  va_list argList;
  va_start(argList,p_format);

  FormatV(p_format.c_str(),argList);

  va_end(argList);
}

// Format a variable list
void 
SMX_String::FormatV(LPCTSTR p_format,va_list p_list)
{
  // Getting a buffer of the correct length
  int len = _vsctprintf(p_format,p_list) + 1;
  TCHAR* buffer = new TCHAR[len];
  // Formatting the parameters
  _vstprintf_s(buffer,len,p_format,p_list);
  // Adding to the string
  *this = buffer;

  delete[] buffer;
}

void 
SMX_String::FormatV(UINT p_strID,va_list p_list)
{
  // Getting the string
  SMX_String str;
  if(str.LoadString(p_strID))
  {
    // Getting a buffer of the correct length
    int len = _vsctprintf(str.c_str(),p_list) + 1;
    TCHAR* buffer = new TCHAR[len];
    // Formatting the parameters
    _vstprintf_s(buffer,len,str.c_str(),p_list);
    // Adding to the string
    *this = buffer;

    delete[] buffer;
  }
}

// Format a message by system format instead of printf
void 
SMX_String::FormatMessage(LPCTSTR p_format,...)
{
  va_list argList;
  va_start(argList,p_format);

  FormatMessageV(p_format,&argList);

  va_end(argList);
}

void 
SMX_String::FormatMessage(UINT p_strID,...)
{
  va_list argList;
  va_start(argList,p_strID);

  FormatMessageV(p_strID,&argList);

  va_end(argList);
}

void 
SMX_String::FormatMessageV(LPCTSTR p_format,va_list* p_list)
{
  // format message into temporary buffer pszTemp
  CHeapPtr<TCHAR,CLocalAllocator> pszTemp;

  // FormatMessage returns zero in case of failure or the number of characters
  // if it is success, but we may actually get 0 as a number of characters.
  // So to avoid this situation use SetLastError and GetLastErorr to determine
  // whether the function FormatMessage has failed.
  DWORD dwLastError = ::GetLastError();
  ::SetLastError(0);

  DWORD dwResult = ::FormatMessage(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER
                                  ,p_format,0,0,reinterpret_cast<LPTSTR>(&pszTemp),0,p_list);

  if((dwResult == 0) && (::GetLastError() != 0))
  {
    throw std::bad_alloc();
  }
  ::SetLastError(dwLastError);

  *this = (LPCTSTR)pszTemp;
}

void 
SMX_String::FormatMessageV(UINT p_strID,va_list* p_list)
{
  SMX_String format;
  
  if(format.LoadString(p_strID))
  {
    // format message into temporary buffer pszTemp
    CHeapPtr<TCHAR,CLocalAllocator> pszTemp;
    DWORD dwLastError = ::GetLastError();
    ::SetLastError(0);

    DWORD dwResult = ::FormatMessage(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER
                                     ,format.c_str(),0,0,reinterpret_cast<LPTSTR>(&pszTemp),0,p_list);

    if((dwResult == 0) && (::GetLastError() != 0))
    {
      throw std::bad_alloc();
    }
    ::SetLastError(dwLastError);

    *this = (LPCTSTR)pszTemp;
  }
}

// Getting buffer of at least p_length + 1 size
PTSTR 
SMX_String::GetBufferSetLength(int p_length)
{
  reserve(p_length);
  return (PTSTR)c_str();
}

// Getting a shell environment variable
BOOL 
SMX_String::GetEnvironmentVariable(LPCTSTR p_variable)
{
  BOOL  result = FALSE;
  ULONG length = ::GetEnvironmentVariable(p_variable,nullptr,0);

  if(length == 0)
  {
    Empty();
  }
  else
  {
    TCHAR* pszBuffer = new TCHAR[length + 1];
    ::GetEnvironmentVariable(p_variable,(LPTSTR)pszBuffer,length);
    *this = pszBuffer;
    delete [] pszBuffer;
    result = TRUE;
  }
  return result;
}

// Insert char or string
int 
SMX_String::Insert(int p_index,LPCTSTR p_string)
{
  insert(p_index,p_string);
  return (int)length();
}

int 
SMX_String::Insert(int p_index,TCHAR p_char)
{
  insert(p_index,1,p_char);
  return (int)length();
}

// Taking the left side of the string
SMX_String 
SMX_String::Left(int p_length) const
{
  if(p_length < 0)
  {
    p_length = 0;
  }
  return (substr(0,p_length));
}

// Load a string from the resources
BOOL 
SMX_String::LoadString(UINT p_strID)
{
  const ATLSTRINGRESOURCEIMAGE* resource = nullptr;
  HINSTANCE instance = _AtlBaseModule.GetHInstanceAt(0);

  for(int ind = 1; instance != nullptr && resource == nullptr; instance = _AtlBaseModule.GetHInstanceAt(ind++))
  {
    resource = AtlGetStringResourceImage(instance,p_strID,0);
    if(resource)
    {
      return LoadString(instance,p_strID,0);
    }
  }
  return FALSE;
}

BOOL 
SMX_String::LoadString(HINSTANCE p_inst,UINT p_strID,WORD p_languageID)
{
  const ATLSTRINGRESOURCEIMAGE* image = AtlGetStringResourceImage(p_inst,p_strID,p_languageID);
  if(image == nullptr)
  {
    return(FALSE);
  }
  int logicSize = image->nLength + 1;
  WCHAR* temp = new WCHAR[logicSize + 1];
  int  realSize = logicSize * 2;
  memcpy_s(temp,realSize,(void*)image->achString,realSize);
  temp[logicSize - 1] = (WCHAR)NULL;
#ifdef UNICODE
  *this = temp;
#else
  USES_CONVERSION;
  *this = (LPSTR) CW2A(temp);
#endif

  delete [] temp;
  return(TRUE);
}

// Lock the buffer returning the string
// Does not exactly what CString does!!
PCTSTR 
SMX_String::LockBuffer()
{
  // Lock();
  return c_str();
}

void 
SMX_String::MakeLower()
{
  for(size_t ind = 0;ind < length();++ind)
  {
    if(isalpha(at(ind)))
    {
      replace(ind,1,1,(TCHAR)tolower(at(ind)));
    }
  }
}

void 
SMX_String::MakeUpper()
{
  for(size_t ind = 0;ind < length(); ++ind)
  {
    if(isalpha(at(ind)))
    {
      replace(ind,1,1,(TCHAR)toupper(at(ind)));
    }
  }
}

// Releasing the buffer again
void 
SMX_String::ReleaseBuffer(int p_newLength /*=-1*/)
{
  if(p_newLength < 0)
  {
    shrink_to_fit();
  }
  else
  {
    resize(p_newLength,0);
  }
}

void 
SMX_String::ReleaseBufferSetLength(int p_newLength)
{
  if(p_newLength < 0 || p_newLength > (int)capacity())
  {
    throw std::bad_array_new_length();
  }
  else
  {
    resize(p_newLength,0);
  }
}

// Remove all occurrences of char
int 
SMX_String::Remove(TCHAR p_char)
{
  int count = 0;
  size_t pos = 0;
  while(pos < size())
  {
    if(at(pos) == p_char)
    {
      erase(pos,1);
      ++count;
    }
    else
    {
      ++pos;
    }
  }
  return count;
}

// Replace a string or a character

int SMX_String::Replace(PCTSTR p_old,PCTSTR p_new)
{
  int    count  = 0;
  size_t length = _tcslen(p_old);
  size_t pos    = find(p_old);

  while(pos != tstring::npos)
  {
    replace(pos,length,p_new);
    pos = find(p_old);
    ++count;
  }
  return count;
}

int 
SMX_String::Replace(TCHAR p_old,TCHAR p_new)
{
  int count = 0;
  size_t pos = find(p_old);

  while(pos != tstring::npos)
  {
    replace(pos,1,1,p_new);
    pos = find(p_old);
    ++count;
  }
  return count;
}

// Get substring from the right 
SMX_String
SMX_String::Right(int p_length) const
{
  int sz = (int) size();
  if(p_length > sz)
  {
    p_length = sz;
  }
  return (substr(sz - p_length,p_length));
}

// Set char at a position
void 
SMX_String::SetAt(int p_index,TCHAR p_char)
{
  int sz = (int) size();
  if(p_index < 0 || p_index > sz)
  {
    throw std::bad_array_new_length();
  }
  if(p_index == sz)
  {
    push_back(p_char);
  }
  else
  {
    replace(p_index,1,1,p_char);
  }
}

// SetString interface
void 
SMX_String::SetString(PCTSTR p_string)
{
  if(p_string == nullptr)
  {
    throw std::exception("Null pointer string");
  }
  DWORD_PTR str   = (DWORD_PTR) p_string;
  DWORD_PTR begin = (DWORD_PTR) c_str();
  DWORD_PTR end   = (DWORD_PTR) c_str() + size();
  if(begin <= str && str <= end)
  {
    // It was a substring of the existing string
    erase(0,str - begin);
  }
  else
  {
    // Completely different string
    *this = p_string;
  }
}

void 
SMX_String::SetString(PCTSTR p_string,int p_length)
{
  if(p_string == nullptr)
  {
    throw std::exception("Null pointer string");
  }
  std::tstring str(p_string);
  if(p_length < (int)str.size())
  {
    str.resize(p_length);
  }
  SetString(str.c_str());
}

// Set string from a COM BSTR
// Does something different than CString, because it does NOT 
// reduce the amount of string space, but copies the BSTR to the String
BSTR 
SMX_String::SetSysString(BSTR* p_string)
{
#ifdef UNICODE
  int nLen = _tcslen(*p_string);
  BOOL bSuccess = ::SysReAllocStringLen(p_string,NULL,nLen);
  if(bSuccess)
  {
    _tcsncpy_s(*p_string,nLen,c_str(),nLen);
  }
#else
  int nLen = ::MultiByteToWideChar(CP_ACP,0,c_str(),(DWORD)size(),NULL,NULL);
  BOOL bSuccess = ::SysReAllocStringLen(p_string,NULL,nLen);
  if(bSuccess)
  {
    ::MultiByteToWideChar(CP_ACP,0,c_str(),(DWORD)size(),*p_string,nLen);
  }
#endif
  else
  {
    throw bad_alloc();
  }
  return(*p_string);
}

// Leftmost string not in argument
SMX_String 
SMX_String::SpanExcluding(PCTSTR p_string)
{
  if(p_string == nullptr)
  {
    throw std::exception("Null pointer string");
  }
  return Left((int)_tcscspn(c_str(),p_string));
}

// Leftmost string in argument
SMX_String 
SMX_String::SpanIncluding(PCTSTR p_string)
{
  if(p_string == nullptr)
  {
    throw std::exception("Null pointer string");
  }
  return Left((int)_tcsspn(c_str(),p_string));
}

// Length of the string
int 
SMX_String::StringLength(PCTSTR p_string)
{
  if(p_string == nullptr)
  {
    return 0;
  }
  return (int)_tcslen(p_string);
}

// Return tokenized strings
SMX_String 
SMX_String::Tokenize(PCTSTR p_tokens,int& p_curpos) const
{
  if(p_curpos < 0)
  {
    throw std::bad_alloc();
  }
  if((p_tokens == nullptr) || (*p_tokens == 0))
  {
    if(p_curpos < GetLength())
    {
      return (c_str() + p_curpos);
    }
  }
  else
  {
    PCTSTR pszPlace = c_str() + p_curpos;
    PCTSTR pszEnd   = c_str() + size();
    if(pszPlace < pszEnd)
    {
      int nIncluding = (int)_tcsspn(pszPlace,p_tokens);

      if((pszPlace + nIncluding) < pszEnd)
      {
        pszPlace += nIncluding;
        int nExcluding = (int)_tcscspn(pszPlace,p_tokens);

        int iFrom  = p_curpos + nIncluding;
        int nUntil = nExcluding;
        p_curpos   = iFrom + nUntil + 1;

        return(Mid(iFrom,nUntil));
      }
    }
  }
  // return empty string, done tokenizing
  p_curpos = -1;

  return SMX_String(_T(""));
}

SMX_String& 
SMX_String::TrimLeft(TCHAR p_char)
{
  int count = 0;
  PCTSTR str = c_str();
  while(*str && *str == p_char)
  {
    ++str;
    ++count;
  }

  erase(0,count);
  return *this;
}

SMX_String& 
SMX_String::TrimLeft(PCTSTR p_string)
{
  // if we're not trimming anything, we're not doing any work
  if((p_string == nullptr) || (*p_string == 0))
  {
    return(*this);
  }

  PCTSTR psz = c_str();
  while((*psz != 0) && (_tcsrchr(p_string,*psz) != NULL)) ++psz;

  if(psz != c_str())
  {
    // fix up data and length
    int iFirst = int(psz - c_str());
    erase(0,iFirst);
  }
  return(*this);
}

SMX_String& SMX_String::TrimRight(TCHAR p_char)
{
  if(!empty())
  {
    size_t pos = size() - 1;
    while(pos != tstring::npos)
    {
      if(at(pos) != p_char)
      {
        ++pos;
        break;
      }
      --pos;
    }
    erase(pos);
  }
  return *this;
}

SMX_String& 
SMX_String::TrimRight(PCTSTR p_string)
{
  // if we're not trimming anything, we're not doing any work
  if((p_string == nullptr) || (*p_string == 0))
  {
    return(*this);
  }

  // Start at the ending of the string
  size_t pos = size() - 1;
  while(pos != tstring::npos)
  {
    if(_tcschr(p_string,at(pos)) != nullptr)
    {
      --pos;
    }
    else
    {
      ++pos;
      break;
    }
  }

  if(pos >= 0)
  {
    // truncate at left-most matching character
    erase(pos,tstring::npos);
  }
  return(*this);
}

//////////////////////////////////////////////////////////////////////////
//
// OPERATORS
//
//////////////////////////////////////////////////////////////////////////

SMX_String::operator TCHAR*() const
{
  return (TCHAR*)c_str();
}

SMX_String::operator const TCHAR*() const
{
  return c_str();
}

SMX_String
SMX_String::operator+(SMX_String& p_extra) const
{
  SMX_String total(c_str());
  total.append(p_extra);
  return total;
}

SMX_String
SMX_String::operator+=(SMX_String& p_extra)
{
  append(p_extra.c_str());
  return *this;
}

SMX_String
SMX_String::operator+=(std::tstring& p_string)
{
  append(p_string);
  return *this;
}

SMX_String
SMX_String::operator+=(const TCHAR* p_extra)
{
  append(p_extra);
  return *this;
}

SMX_String
SMX_String::operator=(const SMX_String& p_extra)
{
  assign(p_extra);
  return *this;
}

SMX_String
SMX_String::operator+=(const TCHAR p_char)
{
  append(1,p_char);
  return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Conversion methods
//
//////////////////////////////////////////////////////////////////////////

int
SMX_String::AsInt()
{
  return _ttoi(c_str());
}

long
SMX_String::AsLong()
{
  return _ttol(c_str());
}

unsigned
SMX_String::AsUnsigned()
{
  return (unsigned)_ttoi(c_str());
}

INT64
SMX_String::AsInt64()
{
  return _ttoi64(c_str());
}

UINT64
SMX_String::AsUint64()
{
  return (unsigned)_ttoi64(c_str());
}

void
SMX_String::SetNumber(int p_number,int p_radix /*= 10*/)
{
  TCHAR buffer[14];
  _itot_s(p_number,buffer,14,p_radix);
  *this = buffer;
}

void
SMX_String::SetNumber(unsigned p_number)
{
  *this = std::to_tstring(p_number);
}

void
SMX_String::SetNumber(INT64 p_number)
{
  *this = std::to_tstring(p_number);
}

void
SMX_String::SetNumber(UINT64 p_number)
{
  *this = std::to_tstring(p_number);
}

//////////////////////////////////////////////////////////////////////////
//
// StringData counterparts
//
//////////////////////////////////////////////////////////////////////////

// void String::AddRef()
// {
//   _InterlockedIncrement(&m_references);
// }
// 
// void String::Release()
// {
//   if(_InterlockedDecrement(&m_references) <= 0)
//   {
//     delete this;
//   }
// }
// 
// void String::Lock()
// {
//   // Locked buffers can't be shared
//   --m_references;
//   if(m_references == 0)
//   {
//     m_references = -1;
//   }
// 
// }
// 
// void String::Unlock()
// {
//   if(IsLocked())
//   {
//     ++m_references;
//     if(m_references == 0)
//     {
//       m_references = 1;
//     }
//   }
// }

}