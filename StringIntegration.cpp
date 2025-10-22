// StringIntegration.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "resource.h"
#include "XString.h"

int TestMethods()
{
  int errors = 0;

  CString testMFC(_T("TestString for MFC/STD/SMX"));
  XString testSMX(_T("TestString for MFC/STD/SMX"));


  // TEST 1: AllocSysString()
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 01: AllocSysString()                  : "));
  BSTR btt1 = testMFC.AllocSysString();
  BSTR btt2 = testSMX.AllocSysString();

  if(wcscmp(btt1,btt2))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));
  SysFreeString(btt1);
  SysFreeString(btt2);

  // TEST 2: Append 1
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 02: Append(string)                    : "));
  testMFC.Append(_T(" Extra"));
  testSMX.Append(_T(" Extra"));
  if(testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 3: Append 2
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 03: Append(string,length)             : "));
  testMFC.Append(_T("Fourteen"),4);
  testSMX.Append(_T("Fourteen"),4);
  if(testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 4: AppendChar()
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 04: AppendChar(char)                  : "));
  testMFC.AppendChar(_T('A'));
  testSMX.AppendChar(_T('A'));
  if(testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 5: AppendFormat / AppendFormatV
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 05: AppendFormat(V)(string)           : "));
  testMFC.AppendFormat(_T(" app [%d] : "),456);
  testSMX.AppendFormat(_T(" app [%d] : "),456);
  if(testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 6: Load String
  bool bres1 = testMFC.LoadString(IDS_FORINSTANCE);
  bool bres2 = testSMX.LoadString(IDS_FORINSTANCE);
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 06: LoadString([inst,]RES[,language]) : "));
  if(testMFC != CString(testSMX.c_str()) || !bres1 || !bres2)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 7: Collate
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 07: Collate(string)                   : "));
  int res1 = testMFC.Collate(_T("Test"));
  int res2 = testSMX.Collate(_T("Test"));
  if(res1 != res2)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 8: CollateNoCase
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 08: CollateNoCase(string)             : "));
  res1 = testMFC.CollateNoCase(_T("TEST"));
  res2 = testSMX.CollateNoCase(_T("TEST"));
  if(res1 != res2)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 9: Compare
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 09: Compare(string)                   : "));
  res1 = testMFC.Compare(_T("Test"));
  res2 = testSMX.compare(_T("Test"));
  if(res1 != res2)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 10: CompareNoCase
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 10: CompareNoCase(string)             : "));
  res1 = testMFC.CompareNoCase(_T("XXXX"));
  res2 = testSMX.CompareNoCase(_T("XXXX"));
  if(res1 != res2)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  //   TEST 11: Construct
  //
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 11: Constructors                      : OK\n"));

  // TEST 12: Delete
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 12: Delete(begin,length)              : "));
  testMFC.Delete(5,6);
  testSMX.Delete(5,6);
  if(testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 13: Empty
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 13: Empty()                           : "));
  testMFC.Empty();
  testSMX.Empty();
  if(!testMFC.IsEmpty() || testSMX.length())
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 14: Find string
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 14: Find(string,start)                : "));
  testMFC = "This is an eight 8 or a 9";
  testSMX.Append(testMFC);
  res1 = testMFC.Find(_T("eight"),4);
  res2 = testSMX.Find(_T("eight"),4);
  if(res1 != res2)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 15: Find string
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 15: Find(char,start)                  : "));
  res1 = testMFC.Find(_T('8'),res1);
  res2 = testSMX.Find(_T('8'),res2);
  if(res1 != res2)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 16: FindOneOf
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 16: FindOneOf(string)                 : "));
  res1 = testMFC.FindOneOf(_T("o9"));
  res2 = testSMX.FindOneOf(_T("o9"));
  if(res1 != res2)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 17: Format(string,list)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 17: Format(format,string)             : "));
  testMFC.Format(_T("This string is an example of a %s resource string"),_T("test"));
  testSMX.Format(_T("This string is an example of a %s resource string"),_T("test"));
  if(testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 18: Format(ID,list)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 18: Format(ID,list)                   : "));
  testMFC.Format(IDS_FORINSTANCE,_T("test"));
  testSMX.Format(IDS_FORINSTANCE,_T("test"));
  if(testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 19: FormatMessage / FormatMessageV
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 19: FormatMessage(V)(string,...)      : "));
  testMFC.FormatMessage(_T("%1!d! of %2!d! writers agree: Soccer is %3%!"),3,4,_T("Best"));
  testSMX.FormatMessage(_T("%1!d! of %2!d! writers agree: Soccer is %3%!"),3,4,_T("Best"));
  if(testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 20: FormatMessage/FormatMessageV with string ID
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 19: FormatMessage(V)(ID,...)          : "));
  testMFC.FormatMessage(IDS_FORMMESSAGE,3,4,_T("Best"));
  testSMX.FormatMessage(IDS_FORMMESSAGE,3,4,_T("Best"));
  if(testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 21: GetEnvironmentVariable
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 21: GetEnvironmentVariable(string)    : "));
  bres1 = testMFC.GetEnvironmentVariable(_T("TMP"));
  bres2 = testSMX.GetEnvironmentVariable(_T("TMP"));
  if(testMFC != CString(testSMX.c_str()) || !bres1 || !bres2)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 22: GetLength
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 22: GetLength()                       : "));
  res1 = testMFC.GetLength();
  res2 = testSMX.GetLength();
  if(res1 != res2)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 23: GetAt(n)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 23: GetAt(index)                      : "));
  TCHAR ch1 = testMFC.GetAt(3);
  TCHAR ch2 = testSMX.GetAt(3);
  if(ch1 != ch2)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 24: GetAllocLength
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 24: GetAllocLength()                  : "));
  res1 = testMFC.GetAllocLength();
  res2 = testSMX.GetAllocLength();
  if(res1 < testMFC.GetLength() || res2 < testSMX.GetLength())
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 25: Shrinking the string
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 25: FreeExtra()                       : "));
  testMFC.FreeExtra();
  testSMX.FreeExtra();
  if(abs((int)(testSMX.GetLength() - testSMX.GetAllocLength()) )> 16)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 26: GetBufferSetLength()
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 26: MFC::GetBufferSetLength(length)   : "));
  const TCHAR* buf1 = testMFC.GetBufferSetLength(300);
  testMFC.ReleaseBuffer();
  res1 = testMFC.GetAllocLength();
  if(res1 != 300)
  {
    _tprintf(_T("ERROR MFC\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 26: SMX::GetBufferSetLength(length)   : "));
  LPCTSTR buf2 = testSMX.GetBufferSetLength(300);
  testSMX.ReleaseBuffer();
  res2 = testSMX.GetAllocLength();
  if(res2 > (int)testSMX.size() + 16)
  {
    _tprintf(_T("ERROR SMX\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 27: ReleaseBufferSetLength()
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 27: MFC::ReleaseBufferSetLength(len)  : "));
  buf1 = testMFC.GetBufferSetLength(300);
  testMFC.ReleaseBufferSetLength(200);
  res1 = testMFC.GetLength();
  if(res1 != 200)
  {
    _tprintf(_T("ERROR MFC\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 27: SMX::ReleaseBufferSetLength(len)  : "));
  buf2 = testSMX.GetBufferSetLength(300);
  testSMX.ReleaseBufferSetLength(200);
  res2 = testSMX.GetLength();
  if(res2 != 200)
  {
    _tprintf(_T("ERROR SMX\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 28: GetString();
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 28: GetString()                       : "));
  buf1 = testMFC.GetString();
  buf2 = testSMX.GetString();
  if(_tcscmp(buf1,buf2))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 29: Insert(index,string)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 29: Insert(index,string)              : "));
  res1 = testMFC.Insert(4,_T("\\wow\\"));
  res2 = testSMX.Insert(4,_T("\\wow\\"));
  if(res1 != res2 || testMFC.Compare(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 30: Insert(index,char)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 30: Insert(index,char)                : "));
  res1 = testMFC.Insert(20,_T('X'));
  res2 = testSMX.Insert(20,_T('X'));
  if(res1 != res2 || testMFC.Compare(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 31: IsEmpty()
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 31: IsEmpty()                         : "));
  bool filled1 = testMFC.IsEmpty();
  bool filled2 = testSMX.IsEmpty();
  testMFC.Empty();
  testSMX.Empty();
  bool empty1 = testMFC.IsEmpty();
  bool empty2 = testMFC.IsEmpty();
  if(filled1 == true || filled2 == true || empty1 == false || empty2 == false)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 32: Left()
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 32: Left(size)                        : "));
  res1 = testMFC.LoadString(IDS_FORMMESSAGE);
  res2 = testSMX.LoadString(IDS_FORMMESSAGE);
  CString substr1 = testMFC.Left(12);
  XString substr2 = testSMX.Left(12);
  if(substr1 != CString(substr2.c_str()) || !res1 || !res2)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

//   // TEST 33: LockBuffer();
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 33: LockBuffer()                      : --\n"));
  //   buf1 = testMFC.LockBuffer();
//   buf2 = testSMX.LockBuffer();
//   if(strcmp(buf1,buf2))
//   {
//     _tprintf(_T("ERROR: LockBuffer()\n"));
//     ++errors;
//   }
//   testMFC.UnlockBuffer();
//   testSMX.UnlockBuffer();

  // TEST 34: MakeLower
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 34: MakeLower()                       : "));
  testMFC.MakeLower();
  testSMX.MakeLower();
  if(testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 35:: MakeReverse
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 35: MakeReverse()                     : "));
  testMFC.MakeReverse();
  testSMX.MakeReverse();
  if(testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 36: MakeUpper
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 36: MakeUpper()                       : "));
  testMFC.MakeUpper();
  testSMX.MakeUpper();
  if(testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 37: Mid(index)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 37: Mid(pos)                          : "));
  substr1 = testMFC.Mid(3);
  substr2 = testSMX.Mid(3);
  if(substr1 != CString(substr2.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 38: Mid(index,length)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 38: Mid(pos,length)                   : "));
  substr1 = testMFC.Mid(3,10);
  substr2 = testSMX.Mid(3,10);
  if(substr1 != CString(substr2.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 39: Preallocate
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 39: Preallocate(length)               : "));
  testMFC.Preallocate(500);
  testSMX.Preallocate(500);
  res1 = testMFC.GetAllocLength();
  res2 = testMFC.GetAllocLength();
  if(res1 != res2)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 40: Remove(char)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 40: Remove(char)                      : "));
  res1 = testMFC.Remove('!');
  res2 = testSMX.Remove('!');
  if(res1 != res2 || testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 41: Replace(char,char)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 41: Replace(char,char)                : "));
  res1 = testMFC.Replace('O','X');
  res2 = testSMX.Replace('O','X');
  if(res1 != res2 || testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 42: Replace(string,string)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 42: Replace(string,string)            : "));
  res1 = testMFC.Replace(_T("RE"),_T("qq"));
  res2 = testSMX.Replace(_T("RE"),_T("qq"));
  if(res1 != res2 || testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 43: ReverseFind(char)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 43: ReverseFind(char)                 : "));
  res1 = testMFC.ReverseFind('q');
  res2 = testSMX.ReverseFind('q');
  if(res1 != res2)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 44: Right(length)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 44: Right(length)                     : "));
  substr1 = testMFC.Right(6);
  substr2 = testSMX.Right(6);
  if(substr1 != CString(substr2.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 45: SetAt(pos,char)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 45: SetAt(pos,char)                   : "));
  testMFC.SetAt(3,'8');
  testSMX.SetAt(3,'8');
  if(testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 46: SetAt(pos,char) after string: Must throw
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 46: SetAt(pos,char) throw overflow    : "));
  bool caught1 = false;
  bool caught2 = false;
  try
  {
    testMFC.SetAt(700,_T('8'));
  }
  catch(COleException& ex)
  {
    TCHAR buffer[_MAX_PATH + 1];
    ex.GetErrorMessage(buffer,_MAX_PATH);
    _tprintf(buffer);
    caught1 = true;
  }
  catch(...)
  {
    caught1 = true;
    _tprintf(_T("OK\n"));
  }

  try
  {
    testSMX.SetAt(700,_T('8'));
  }
  catch(std::exception& ex)
  {
#ifdef UNICODE
    stdstring error = CA2W(ex.what());
#else
    stdstring error = ex.what();
#endif
    _tprintf(_T("ERROR: %s "),error.c_str());
    caught2 = true;
  }
  if(caught1 == false || caught2 == false)
  {
    _tprintf(_T("ERROR !!\n"));
    ++errors;
  }
  else _tprintf(_T("               : OK\n"));

  // TEST 47: SetString
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 47: SetString                         : "));
  testMFC.SetString(_T("TESTING EVERYTHING"),12);
  testSMX.SetString(_T("TESTING EVERYTHING"),12);
  if(testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 48: SetSysString(BSTR)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 48: SetSysString(BSTR)                : "));
  btt1 = testMFC.AllocSysString();
  btt2 = testSMX.AllocSysString();
  substr1.SetSysString(&btt1);
  substr2.SetSysString(&btt2);
  if(substr1 != CString(substr2.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 49: SpanExcluding
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 49: SpanExcluding(string)             : "));
  substr1 = testMFC.SpanExcluding(_T("IXY"));
  substr2 = testSMX.SpanExcluding(_T("IXY"));
  if(substr1 != CString(substr2.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 50: SpanIncluding
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 50: SpanIncluding(string)             : "));
  substr1 = testMFC.SpanIncluding(_T("TES"));
  substr2 = testSMX.SpanIncluding(_T("TES"));
  if(substr1 != CString(substr2.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 51: StringLength(string)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 51: StringLength(string)              : "));
  res1 = testMFC.StringLength(_T("Very much longer string than before"));
  res2 = testSMX.StringLength(_T("Very much longer string than before"));
  if(res1 != res2)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 52: Tokenize(string,curpos)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 52: Tokenize(string,curpos)           : "));
  int curpos1 = 0;
  int curpos2 = 0;
  testMFC.SetString(_T("%First Second#Third"));
  testSMX.SetString(_T("%First Second#Third"));
  substr1 = testMFC.Tokenize(_T("% #"),curpos1);
  substr2 = testSMX.Tokenize(_T("% #"),curpos2);
  while(!substr1.IsEmpty() && !substr2.IsEmpty())
  {
    if(substr1 != CString(substr2.c_str()))
    {
      _tprintf(_T("ERROR\n"));
      ++errors;
      break;
    }

    substr1 = testMFC.Tokenize(_T("% #"),curpos1);
    substr2 = testSMX.Tokenize(_T("% #"),curpos2);
  }
  if(substr1.IsEmpty() && substr2.IsEmpty())
  {
    _tprintf(_T("OK\n"));
  }
  else
  {
    _tprintf(_T("ERROR\n"));
  }

  // TEST 53: Trim([char])
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 53: Trim([char])                      : "));
  testMFC.SetString(_T("   CBAABC middle part of the string BBCCAA   "));
  testSMX.SetString(_T("   CBAABC middle part of the string BBCCAA   "));
  substr1 = testMFC.Trim();
  substr2 = testSMX.Trim();
  if(substr1 != CString(substr2.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 54: Trim(string)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 54: Trim(string)                      : "));
  substr1 = testMFC.Trim(_T("ABC"));
  substr2 = testSMX.Trim(_T("ABC"));
  if(substr1 != CString(substr2.c_str()))
  {
    _tprintf(_T("ERROR: Trim(string)\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 55: Truncate(length)
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 55: Truncate(length)                  : "));
  testMFC.Truncate(11);
  testSMX.Truncate(11);
  if(testMFC != CString(testSMX.c_str()))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // Result of all tests
  return errors;
}

int TestOperators()
{
  int errors = 0;

  //     Operator plus
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 01: OPERATOR: +                       : "));
  XString one(_T("One"));
  XString two(_T("Two"));
  XString result = one + two;
  if(result != _T("OneTwo"))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  //     Operator larger than or equal
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 02: OPERATOR: >=                      : "));
  XString between(_T("PPP"));
  if(one >= between)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  //     Operator smaller than or equal
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 03: OPERATOR: <=                      : "));
  if(two <= between)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  //     Operator array access through an index
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 04: OPERATOR: []                      : "));
  if (one[(size_t)1] != _T('n') || two[(size_t)2] != _T('o'))
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));


  return errors;
}

int CrossIntegration()
{
  int errors = 0;

  // TEST 100: Construct
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 100: CTOR CString from String         : "));

  XString test1(_T("This is a teststring: éèëê curaçao."));
  CString test2(test1);
  if (test2.Compare(_T("This is a teststring: éèëê curaçao.")) != 0)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 101: Construct
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 101: CString from String with =       : "));

  test1 = _T("This is a teststring: éèëê curaçao.");
  test2 = test1;
  if (test2.Compare(_T("This is a teststring: éèëê curaçao.")) != 0)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 103: Construct
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 103: CTOR String from CString         : "));

  CString test3(_T("This is a teststring: éèëê curaçao."));
  XString test4(test1);
  if(test4.Compare(_T("This is a teststring: éèëê curaçao.")) != 0)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));

  // TEST 104: Construct
  //     "------------------------------------------ : --"
  _tprintf(_T("TEST 104: String from CString with =       : "));

  test3 = "This is a teststring: éèëê curaçao.";
  test4 = test3.GetString();
  if (test4.Compare(_T("This is a teststring: éèëê curaçao.")) != 0)
  {
    _tprintf(_T("ERROR\n"));
    ++errors;
  }
  else _tprintf(_T("OK\n"));
  return errors;
}

int TestStrings()
{
  int errors = 0;

  errors += TestMethods();
  errors += TestOperators();
  errors += CrossIntegration();

  return errors;
}

int main()
{
  int nRetCode = 0;

  HMODULE hModule = ::GetModuleHandle(nullptr);

  if (hModule != nullptr)
  {
    // initialize MFC and print and error on failure
    if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
    {
      _tprintf(_T("Fatal Error: MFC initialization failed\n"));
      nRetCode = 1;
    }
    else
    {
      _tprintf(_T("STRING INTEGRATION std::string AND MFC::CString\n"));
      _tprintf(_T("===============================================\n"));
      nRetCode = TestStrings();
      _tprintf(_T("TOTAL number of errors: %d\n"),nRetCode);
    }
  }
  else
  {
    // TODO: change error code to suit your needs
    _tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
    nRetCode = 1;
  }
  return nRetCode;
}
