// StringIntegration.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "StringIntegration.h"
#include "resource.h"
#include "SMX_String.h"

// The one and only application object

using namespace std;

int TestMethods()
{
  int errors = 0;

  CString testMFC("TestString for MFC/STD/SMX");
   String testSMX("TestString for MFC/STD/SMX");


  // TEST 1: AllocSysString()
  //     "------------------------------------------ : --"
  printf("TEST 01: AllocSysString()                  : ");
  BSTR btt1 = testMFC.AllocSysString();
  BSTR btt2 = testSMX.AllocSysString();

  if(wcscmp(btt1,btt2))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");
  SysFreeString(btt1);
  SysFreeString(btt2);

  // TEST 2: Append 1
  //     "------------------------------------------ : --"
  printf("TEST 02: Append(string)                    : ");
  testMFC.Append(" Extra");
  testSMX.Append(" Extra");
  if(testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 3: Append 2
  //     "------------------------------------------ : --"
  printf("TEST 03: Append(string,length)             : ");
  testMFC.Append("Fourteen",4);
  testSMX.Append("Fourteen",4);
  if(testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 4: AppendChar()
  //     "------------------------------------------ : --"
  printf("TEST 04: AppendChar(char)                  : ");
  testMFC.AppendChar('A');
  testSMX.AppendChar('A');
  if(testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 5: AppendFormat / AppendFormatV
  //     "------------------------------------------ : --"
  printf("TEST 05: AppendFormat(V)(string)           : ");
  testMFC.AppendFormat(" app [%d] : ",456);
  testSMX.AppendFormat(" app [%d] : ",456);
  if(testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 6: Load String
  bool bres1 = testMFC.LoadString(IDS_FORINSTANCE);
  bool bres2 = testSMX.LoadString(IDS_FORINSTANCE);
  //     "------------------------------------------ : --"
  printf("TEST 06: LoadString([inst,]RES[,language]) : ");
  if(testMFC != CString(testSMX.c_str()) || !bres1 || !bres2)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 7: Collate
  //     "------------------------------------------ : --"
  printf("TEST 07: Collate(string)                   : ");
  int res1 = testMFC.Collate("Test");
  int res2 = testSMX.Collate("Test");
  if(res1 != res2)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 8: CollateNoCase
  //     "------------------------------------------ : --"
  printf("TEST 08: CollateNoCase(string)             : ");
  res1 = testMFC.CollateNoCase("TEST");
  res2 = testSMX.CollateNoCase("TEST");
  if(res1 != res2)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 9: Compare
  //     "------------------------------------------ : --"
  printf("TEST 09: Compare(string)                   : ");
  res1 = testMFC.Compare("Test");
  res2 = testSMX.compare("Test");
  if(res1 != res2)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 10: CompareNoCase
  //     "------------------------------------------ : --"
  printf("TEST 10: CompareNoCase(string)             : ");
  res1 = testMFC.CompareNoCase("XXXX");
  res2 = testSMX.CompareNoCase("XXXX");
  if(res1 != res2)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  //   TEST 11: Construct
  //
  //     "------------------------------------------ : --"
  printf("TEST 11: Constructors                      : OK\n");

  // TEST 12: Delete
  //     "------------------------------------------ : --"
  printf("TEST 12: Delete(begin,length)              : ");
  testMFC.Delete(5,6);
  testSMX.Delete(5,6);
  if(testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 13: Empty
  //     "------------------------------------------ : --"
  printf("TEST 13: Empty()                           : ");
  testMFC.Empty();
  testSMX.Empty();
  if(!testMFC.IsEmpty() || testSMX.length())
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 14: Find string
  //     "------------------------------------------ : --"
  printf("TEST 14: Find(string,start)                : ");
  testMFC = "This is an eight 8 or a 9";
  testSMX.Append(testMFC);
  res1 = testMFC.Find("eight",4);
  res2 = testSMX.Find("eight",4);
  if(res1 != res2)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 15: Find string
  //     "------------------------------------------ : --"
  printf("TEST 15: Find(char,start)                  : ");
  res1 = testMFC.Find('8',res1);
  res2 = testSMX.Find('8',res2);
  if(res1 != res2)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 16: FindOneOf
  //     "------------------------------------------ : --"
  printf("TEST 16: FindOneOf(string)                 : ");
  res1 = testMFC.FindOneOf("o9");
  res2 = testSMX.FindOneOf("o9");
  if(res1 != res2)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 17: Format(string,list)
  //     "------------------------------------------ : --"
  printf("TEST 17: Format(format,string)             : ");
  testMFC.Format("This string is an example of a %s resource string","test");
  testSMX.Format("This string is an example of a %s resource string","test");
  if(testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 18: Format(ID,list)
  //     "------------------------------------------ : --"
  printf("TEST 18: Format(ID,list)                   : ");
  testMFC.Format(IDS_FORINSTANCE,"test");
  testSMX.Format(IDS_FORINSTANCE,"test");
  if(testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 19: FormatMessage / FormatMessageV
  //     "------------------------------------------ : --"
  printf("TEST 19: FormatMessage(V)(string,...)      : ");
  testMFC.FormatMessage("%1!d! of %2!d! writers agree: Soccer is %3%!",3,4,"Best");
  testSMX.FormatMessage("%1!d! of %2!d! writers agree: Soccer is %3%!",3,4,"Best");
  if(testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 20: FormatMessage/FormatMessageV with string ID
  //     "------------------------------------------ : --"
  printf("TEST 19: FormatMessage(V)(ID,...)          : ");
  testMFC.FormatMessage(IDS_FORMMESSAGE,3,4,"Best");
  testSMX.FormatMessage(IDS_FORMMESSAGE,3,4,"Best");
  if(testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 21: GetEnvironmentVariable
  //     "------------------------------------------ : --"
  printf("TEST 21: GetEnvironmentVariable(string)    : ");
  bres1 = testMFC.GetEnvironmentVariable("TMP");
  bres2 = testSMX.GetEnvironmentVariable("TMP");
  if(testMFC != CString(testSMX.c_str()) || !bres1 || !bres2)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 22: GetLength
  //     "------------------------------------------ : --"
  printf("TEST 22: GetLength()                       : ");
  res1 = testMFC.GetLength();
  res2 = testSMX.GetLength();
  if(res1 != res2)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 23: GetAt(n)
  //     "------------------------------------------ : --"
  printf("TEST 23: GetAt(index)                      : ");
  char ch1 = testMFC.GetAt(3);
  char ch2 = testSMX.GetAt(3);
  if(ch1 != ch2)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 24: GetAllocLength
  //     "------------------------------------------ : --"
  printf("TEST 24: GetAllocLength()                  : ");
  res1 = testMFC.GetAllocLength();
  res2 = testSMX.GetAllocLength();
  if(res1 < testMFC.GetLength() || res2 < testSMX.GetLength())
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 25: Shrinking the string
  //     "------------------------------------------ : --"
  printf("TEST 25: FreeExtra()                       : ");
  testMFC.FreeExtra();
  testSMX.FreeExtra();
  if(abs((int)(testSMX.GetLength() - testSMX.GetAllocLength()) )> 16)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 26: GetBufferSetLength()
  //     "------------------------------------------ : --"
  printf("TEST 26: MFC::GetBufferSetLength(length)   : ");
  const char* buf1 = testMFC.GetBufferSetLength(300);
  testMFC.ReleaseBuffer();
  res1 = testMFC.GetAllocLength();
  if(res1 != 300)
  {
    printf("ERROR MFC\n");
    ++errors;
  }
  else printf("OK\n");

  //     "------------------------------------------ : --"
  printf("TEST 26: SMX::GetBufferSetLength(length)   : ");
  const char* buf2 = testSMX.GetBufferSetLength(300);
  testSMX.ReleaseBuffer();
  res2 = testSMX.GetAllocLength();
  if(res2 > (int)testSMX.size() + 16)
  {
    printf("ERROR SMX\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 27: ReleaseBufferSetLength()
  //     "------------------------------------------ : --"
  printf("TEST 27: MFC::ReleaseBufferSetLength(len)  : ");
  buf1 = testMFC.GetBufferSetLength(300);
  testMFC.ReleaseBufferSetLength(200);
  res1 = testMFC.GetLength();
  if(res1 != 200)
  {
    printf("ERROR MFC\n");
    ++errors;
  }
  else printf("OK\n");

  //     "------------------------------------------ : --"
  printf("TEST 27: SMX::ReleaseBufferSetLength(len)  : ");
  buf2 = testSMX.GetBufferSetLength(300);
  testSMX.ReleaseBufferSetLength(200);
  res2 = testSMX.GetLength();
  if(res2 != 200)
  {
    printf("ERROR SMX\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 28: GetString();
  //     "------------------------------------------ : --"
  printf("TEST 28: GetString()                       : ");
  buf1 = testMFC.GetString();
  buf2 = testSMX.GetString();
  if(strcmp(buf1,buf2))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 29: Insert(index,string)
  //     "------------------------------------------ : --"
  printf("TEST 29: Insert(index,string)              : ");
  res1 = testMFC.Insert(4,"\\wow\\");
  res2 = testSMX.Insert(4,"\\wow\\");
  if(res1 != res2 || testMFC.Compare(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 30: Insert(index,char)
  //     "------------------------------------------ : --"
  printf("TEST 30: Insert(index,char)                : ");
  res1 = testMFC.Insert(20,'X');
  res2 = testSMX.Insert(20,'X');
  if(res1 != res2 || testMFC.Compare(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 31: IsEmpty()
  //     "------------------------------------------ : --"
  printf("TEST 31: IsEmpty()                         : ");
  bool filled1 = testMFC.IsEmpty();
  bool filled2 = testSMX.IsEmpty();
  testMFC.Empty();
  testSMX.Empty();
  bool empty1 = testMFC.IsEmpty();
  bool empty2 = testMFC.IsEmpty();
  if(filled1 == true || filled2 == true || empty1 == false || empty2 == false)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 32: Left()
  //     "------------------------------------------ : --"
  printf("TEST 32: Left(size)                        : ");
  res1 = testMFC.LoadString(IDS_FORMMESSAGE);
  res2 = testSMX.LoadString(IDS_FORMMESSAGE);
  CString substr1 = testMFC.Left(12);
   String substr2 = testSMX.Left(12);
  if(substr1 != CString(substr2.c_str()) || !res1 || !res2)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

//   // TEST 33: LockBuffer();
  //     "------------------------------------------ : --"
  printf("TEST 33: LockBuffer()                      : --\n");
  //   buf1 = testMFC.LockBuffer();
//   buf2 = testSMX.LockBuffer();
//   if(strcmp(buf1,buf2))
//   {
//     printf("ERROR: LockBuffer()\n");
//     ++errors;
//   }
//   testMFC.UnlockBuffer();
//   testSMX.UnlockBuffer();

  // TEST 34: MakeLower
  //     "------------------------------------------ : --"
  printf("TEST 34: MakeLower()                       : ");
  testMFC.MakeLower();
  testSMX.MakeLower();
  if(testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 35:: MakeReverse
  //     "------------------------------------------ : --"
  printf("TEST 35: MakeReverse()                     : ");
  testMFC.MakeReverse();
  testSMX.MakeReverse();
  if(testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 36: MakeUpper
  //     "------------------------------------------ : --"
  printf("TEST 36: MakeUpper()                       : ");
  testMFC.MakeUpper();
  testSMX.MakeUpper();
  if(testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 37: Mid(index)
  //     "------------------------------------------ : --"
  printf("TEST 37: Mid(pos)                          : ");
  substr1 = testMFC.Mid(3);
  substr2 = testSMX.Mid(3);
  if(substr1 != CString(substr2.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 38: Mid(index,length)
  //     "------------------------------------------ : --"
  printf("TEST 38: Mid(pos,length)                   : ");
  substr1 = testMFC.Mid(3,10);
  substr2 = testSMX.Mid(3,10);
  if(substr1 != CString(substr2.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 39: Preallocate
  //     "------------------------------------------ : --"
  printf("TEST 39: Preallocate(length)               : ");
  testMFC.Preallocate(500);
  testSMX.Preallocate(500);
  res1 = testMFC.GetAllocLength();
  res2 = testMFC.GetAllocLength();
  if(res1 != res2)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 40: Remove(char)
  //     "------------------------------------------ : --"
  printf("TEST 40: Remove(char)                      : ");
  res1 = testMFC.Remove('!');
  res2 = testSMX.Remove('!');
  if(res1 != res2 || testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 41: Replace(char,char)
  //     "------------------------------------------ : --"
  printf("TEST 41: Replace(char,char)                : ");
  res1 = testMFC.Replace('O','X');
  res2 = testSMX.Replace('O','X');
  if(res1 != res2 || testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 42: Replace(string,string)
  //     "------------------------------------------ : --"
  printf("TEST 42: Replace(string,string)            : ");
  res1 = testMFC.Replace("RE","qq");
  res2 = testSMX.Replace("RE","qq");
  if(res1 != res2 || testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 43: ReverseFind(char)
  //     "------------------------------------------ : --"
  printf("TEST 43: ReverseFind(char)                 : ");
  res1 = testMFC.ReverseFind('q');
  res2 = testSMX.ReverseFind('q');
  if(res1 != res2)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 44: Right(length)
  //     "------------------------------------------ : --"
  printf("TEST 44: Right(length)                     : ");
  substr1 = testMFC.Right(6);
  substr2 = testSMX.Right(6);
  if(substr1 != CString(substr2.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 45: SetAt(pos,char)
  //     "------------------------------------------ : --"
  printf("TEST 45: SetAt(pos,char)                   : ");
  testMFC.SetAt(3,'8');
  testSMX.SetAt(3,'8');
  if(testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 46: SetAt(pos,char) after string: Must throw
  //     "------------------------------------------ : --"
  printf("TEST 46: SetAt(pos,char) throw overflow    : ");
  bool caught1 = false;
  bool caught2 = false;
  try
  {
    testMFC.SetAt(700,'8');
  }
  catch(COleException* ex)
  {
    char buffer[1024];
    ex->GetErrorMessage(buffer,1024,nullptr);
    // printf("%s\n",buffer);
    caught1 = true;
  }
  catch(...)
  {
    caught1 = true;
  }

  try
  {
    testSMX.SetAt(700,'8');
  }
  catch(std::exception& /*ex*/)
  {
    // printf(ex.what());
    caught2 = true;
  }
  if(caught1 == false || caught2 == false)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 47: SetString
  //     "------------------------------------------ : --"
  printf("TEST 47: SetString                         : ");
  testMFC.SetString("TESTING EVERYTHING",12);
  testSMX.SetString("TESTING EVERYTHING",12);
  if(testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 48: SetSysString(BSTR)
  //     "------------------------------------------ : --"
  printf("TEST 48: SetSysString(BSTR)                : ");
  btt1 = testMFC.AllocSysString();
  btt2 = testSMX.AllocSysString();
  substr1.SetSysString(&btt1);
  substr2.SetSysString(&btt2);
  if(substr1 != CString(substr2.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 49: SpanExcluding
  //     "------------------------------------------ : --"
  printf("TEST 49: SpanExcluding(string)             : ");
  substr1 = testMFC.SpanExcluding("IXY");
  substr2 = testSMX.SpanExcluding("IXY");
  if(substr1 != CString(substr2.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 50: SpanIncluding
  //     "------------------------------------------ : --"
  printf("TEST 50: SpanIncluding(string)             : ");
  substr1 = testMFC.SpanIncluding("TES");
  substr2 = testSMX.SpanIncluding("TES");
  if(substr1 != CString(substr2.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 51: StringLength(string)
  //     "------------------------------------------ : --"
  printf("TEST 51: StringLength(string)              : ");
  res1 = testMFC.StringLength("Very much longer string than before");
  res2 = testSMX.StringLength("Very much longer string than before");
  if(res1 != res2)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 52: Tokenize(string,curpos)
  //     "------------------------------------------ : --"
  printf("TEST 52: Tokenize(string,curpos)           : ");
  int curpos1 = 0;
  int curpos2 = 0;
  testMFC.SetString("%First Second#Third");
  testSMX.SetString("%First Second#Third");
  substr1 = testMFC.Tokenize("% #",curpos1);
  substr2 = testSMX.Tokenize("% #",curpos2);
  while(!substr1.IsEmpty() && !substr2.IsEmpty())
  {
    if(substr1 != CString(substr2.c_str()))
    {
      printf("ERROR\n");
      ++errors;
      break;
    }

    substr1 = testMFC.Tokenize("% #",curpos1);
    substr2 = testSMX.Tokenize("% #",curpos2);
  }
  if(substr1.IsEmpty() && substr2.IsEmpty())
  {
    printf("OK\n");
  }

  // TEST 53: Trim([char])
  //     "------------------------------------------ : --"
  printf("TEST 53: Trim([char])                      : ");
  testMFC.SetString("   CBAABC middle part of the string BBCCAA   ");
  testSMX.SetString("   CBAABC middle part of the string BBCCAA   ");
  substr1 = testMFC.Trim();
  substr2 = testSMX.Trim();
  if(substr1 != CString(substr2.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 54: Trim(string)
  //     "------------------------------------------ : --"
  printf("TEST 54: Trim(string)                      : ");
  substr1 = testMFC.Trim("ABC");
  substr2 = testSMX.Trim("ABC");
  if(substr1 != CString(substr2.c_str()))
  {
    printf("ERROR: Trim(string)\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 55: Truncate(length)
  //     "------------------------------------------ : --"
  printf("TEST 55: Truncate(length)                  : ");
  testMFC.Truncate(11);
  testSMX.Truncate(11);
  if(testMFC != CString(testSMX.c_str()))
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 56: numbers
  //     "------------------------------------------ : --"
  printf("TEST 56: Convert string with a number      : ");

  testSMX = "23478";
  int number = testSMX.AsInt();
  printf(number == 23478 ? "OK\n" : "ERROR\n");
  errors += (number != 23478) ? 1 : 0;

  // TEST 57: numbers
  //     "------------------------------------------ : --"
  printf("TEST 57: Convert number to string          : ");

  number = 15332;
  testSMX.SetNumber(number);
  printf(testSMX.Compare("15332") == 0 ? "OK\n" : "ERROR\n");
  errors += (number != 15332) ? 1 : 0;

  // Result of all tests
  return errors;
}

int TestOperators()
{
  int errors = 0;

  //     Operator plus
  //     "------------------------------------------ : --"
  printf("TEST 01: OPERATOR: +                       : ");
  String one("One");
  String two("Two");
  String result = one + two;
  if(result != "OneTwo")
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  //     Operator larger than or equal
  //     "------------------------------------------ : --"
  printf("TEST 02: OPERATOR: >=                      : ");
  String between("PPP");
  if(one >= between)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  //     Operator smaller than or equal
  //     "------------------------------------------ : --"
  printf("TEST 03: OPERATOR: <=                      : ");
  if(two <= between)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  //     Operator array access through an index
  //     "------------------------------------------ : --"
  printf("TEST 04: OPERATOR: []                      : ");
  if (one[(const unsigned)1] != 'n' || two[(const unsigned) 2] != 'o')
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");


  return errors;
}

int CrossIntegration()
{
  int errors = 0;

  // TEST 100: Construct
  //     "------------------------------------------ : --"
  printf("TEST 100: CTOR CString from String         : ");

  String test1("This is a teststring: éèëê curaçao.");
  CString test2(test1);
  if (test2.Compare("This is a teststring: éèëê curaçao.") != 0)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 101: Construct
  //     "------------------------------------------ : --"
  printf("TEST 101: CString from String with =       : ");

  test1 = "This is a teststring: éèëê curaçao.";
  test2 = test1;
  if (test2.Compare("This is a teststring: éèëê curaçao.") != 0)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 103: Construct
  //     "------------------------------------------ : --"
  printf("TEST 103: CTOR String from CString         : ");

  CString test3("This is a teststring: éèëê curaçao.");
  String test4(test1);
  if(test4.Compare("This is a teststring: éèëê curaçao.") != 0)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

  // TEST 104: Construct
  //     "------------------------------------------ : --"
  printf("TEST 104: String from CString with =       : ");

  test3 = "This is a teststring: éèëê curaçao.";
  test4 = test3.GetString();
  if (test4.Compare("This is a teststring: éèëê curaçao.") != 0)
  {
    printf("ERROR\n");
    ++errors;
  }
  else printf("OK\n");

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
      printf("Fatal Error: MFC initialization failed\n");
      nRetCode = 1;
    }
    else
    {
      printf("STRING INTEGRATION std::string AND MFC::CString\n");
      printf("===============================================\n");
      nRetCode = TestStrings();
      printf("TOTAL number of errors: %d\n",nRetCode);
    }
  }
  else
  {
    // TODO: change error code to suit your needs
    printf("Fatal Error: GetModuleHandle failed\n");
    nRetCode = 1;
  }
  return nRetCode;
}
