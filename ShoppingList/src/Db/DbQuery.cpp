#include <Db/DbQuery.h>

using namespace Db;
using namespace Tizen::Base;

DbQuery::DbQuery()
{
	queryString = L"";
	queryParams.clear();
}


void
DbQuery::AddParamBlob(ByteBuffer* pParamBlob)
{
	queryParams.push_back(DbValue(pParamBlob));
}


void
DbQuery::AddParamInt(int paramInt)
{
	queryParams.push_back(DbValue(paramInt));
}


void
DbQuery::AddParamInt64(long paramInt64)
{
	queryParams.push_back(DbValue(paramInt64));
}


void
DbQuery::AddParamString(const String& paramString)
{
	queryParams.push_back(DbValue(paramString));
}
