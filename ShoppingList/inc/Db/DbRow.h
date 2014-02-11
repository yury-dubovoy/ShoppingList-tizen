#ifndef DBROW_H_
#define DBROW_H_

#include <FBase.h>
#include <FIO.h>
#include <vector>


namespace Db {

class DbRow
{

public:

	virtual void
	AddBlobN(unsigned int columnIndex, Tizen::Base::ByteBuffer* pValue);

	virtual void
	AddInt(unsigned int columnIndex, int value);

	virtual void
	AddInt64(unsigned int columnIndex, long long value);

	virtual void
	AddText(unsigned int columnIndex, const Tizen::Base::String& value);

	virtual unsigned int
	GetColumnCount();

	virtual Tizen::Io::DbColumnType
	GetColumnType(unsigned int columnIndex);

	virtual void
	GetBlob(unsigned int columnIndex, Tizen::Base::ByteBuffer*& value);

	virtual void
	GetInt(unsigned int columnIndex, int& value);

	virtual void
	GetInt64(unsigned int columnIndex, long long& value);

	virtual void
	GetText(unsigned int columnIndex, Tizen::Base::String*& pValue);

public:

	virtual ~DbRow(){};


};

}

#endif /* DBROW_H_ */
