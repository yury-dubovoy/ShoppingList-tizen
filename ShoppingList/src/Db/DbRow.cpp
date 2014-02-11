#include <Db/DbRow.h>

using namespace Db;
using namespace Tizen::Base;
using namespace Tizen::Io;


void
DbRow::AddBlobN(unsigned int columnIndex, ByteBuffer* pValue)
{
	AppLogDebug("ERROR: invalid column index! [%i]", columnIndex);
}


void
DbRow::AddInt(unsigned int columnIndex, int value)
{
	AppLogDebug("ERROR: invalid column index! [%i]", columnIndex);
}


void
DbRow::AddInt64(unsigned int columnIndex, long long value)
{
	AppLogDebug("ERROR: invalid column index! [%i]", columnIndex);
}


void
DbRow::AddText(unsigned int columnIndex, const String& value)
{
	AppLogDebug("ERROR: invalid column index! [%i]", columnIndex);
}


unsigned int
DbRow::GetColumnCount()
{
	return 0;
}


DbColumnType
DbRow::GetColumnType(unsigned int columnIndex)
{
	AppLogDebug("ERROR: invalid column index! [%i]", columnIndex);
	return DB_COLUMNTYPE_INT;
}


void
DbRow::GetBlob(unsigned int columnIndex, ByteBuffer*& value)
{
	AppLogDebug("ERROR: invalid column index! [%i]", columnIndex);
	return;
}


void
DbRow::GetInt(unsigned int columnIndex, int& value)
{
	AppLogDebug("ERROR: invalid column index! [%i]", columnIndex);
	return;
}


void
DbRow::GetInt64(unsigned int columnIndex, long long& value)
{
	AppLogDebug("ERROR: invalid column index! [%i]", columnIndex);
	return;
}


void
DbRow::GetText(unsigned int columnIndex, String*& pValue)
{
	AppLogDebug("ERROR: invalid column index! [%i]", columnIndex);
	return;
}
