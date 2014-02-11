#include <Db/DbValue.h>

using namespace Db;
using namespace Tizen::Base;
using namespace Tizen::Io;


DbValue::DbValue(DbColumnType theValueType)
{
	this->theValueType = theValueType;

	valueInt = 0;
	valueInt64 = 0;
	valueString = "";
	pValueBlob = null;
}


DbValue::DbValue(int paramInt)
{
	theValueType = DB_COLUMNTYPE_INT;
	valueInt = paramInt;

	valueInt64 = 0;
	valueString = "";
	pValueBlob = null;
}


DbValue::DbValue(long paramInt64)
{
	theValueType = DB_COLUMNTYPE_INT64;
	valueInt64 = paramInt64;

	valueInt = 0;
	valueString = "";
	pValueBlob = null;
}


DbValue::DbValue(ByteBuffer* pParamBlob)
{
	theValueType = DB_COLUMNTYPE_BLOB;
	pValueBlob = pParamBlob;

	valueInt = 0;
	valueInt64 = 0;
	valueString = "";
}


DbValue::DbValue(const String& paramString)
{
	theValueType = DB_COLUMNTYPE_TEXT;
	valueString = paramString;

	valueInt = 0;
	valueInt64 = 0;
	pValueBlob = null;
}
