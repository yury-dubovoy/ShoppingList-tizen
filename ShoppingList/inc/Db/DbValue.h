#ifndef DBVALUE_H_
#define DBVALUE_H_

#include <FBase.h>
#include <FIo.h>
#include <vector>

namespace Db {

class DbValue
{

public:

	DbValue(Tizen::Io::DbColumnType	theValueType);
	DbValue(int paramInt);
	DbValue(long paramInt64);
	DbValue(Tizen::Base::ByteBuffer* pParamBlob);
	DbValue(const Tizen::Base::String& paramString);


public:

	int 						valueInt;
	long 						valueInt64;
	Tizen::Base::ByteBuffer*	pValueBlob;
	Tizen::Base::String			valueString;

	Tizen::Io::DbColumnType		theValueType;

};

}

#endif /* DBVALUE_H_ */
