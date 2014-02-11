#ifndef DBQUERY_H_
#define DBQUERY_H_

#include <FBase.h>
#include <vector>

#include <Db/DbValue.h>

namespace Db {

class DbQuery
{

public:

	DbQuery();

	void
	AddParamBlob(Tizen::Base::ByteBuffer* pParamBlob);

	void
	AddParamInt(int paramInt);

	void
	AddParamInt64(long paramInt64);

	void
	AddParamString(const Tizen::Base::String& paramString);

public:

	Tizen::Base::String				queryString;

	std::vector<DbValue> 		queryParams;

};

}

#endif /* DBQUERY_H_ */
