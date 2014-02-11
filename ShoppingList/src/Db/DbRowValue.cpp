#include <Db/DbRowValue.h>

using namespace Db;
using namespace Tizen::Base;
using namespace Tizen::Io;


void
DbRowValue::AddBlobN(unsigned int columnIndex, ByteBuffer* pValue)
{
	theDbValue.pValueBlob = pValue;
}


void
DbRowValue::AddInt(unsigned int columnIndex, int value)
{
	theDbValue.valueInt = value;
}


void
DbRowValue::AddInt64(unsigned int columnIndex, long long value)
{
	theDbValue.valueInt64 = value;
}


void
DbRowValue::AddText(unsigned int columnIndex, const String& value)
{
	theDbValue.valueString = value;
}


unsigned int
DbRowValue::GetColumnCount()
{
	return 1;
}


DbColumnType
DbRowValue::GetColumnType(unsigned int columnIndex)
{
	return theDbValue.theValueType;
}


void
DbRowValue::GetBlob(unsigned int columnIndex, ByteBuffer*& value)
{
	value = theDbValue.pValueBlob;
	return;
}


void
DbRowValue::GetInt(unsigned int columnIndex, int& value)
{
	value = theDbValue.valueInt;
	return;
}


void
DbRowValue::GetInt64(unsigned int columnIndex, long long& value)
{
	value = theDbValue.valueInt64;
	return;
}


void
DbRowValue::GetText(unsigned int columnIndex, String*& pValue)
{
	pValue = &theDbValue.valueString;
	return;
}
