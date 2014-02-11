#ifndef DBROWVALUE_H_
#define DBROWVALUE_H_

#include <FBase.h>
#include <FIO.h>
#include <vector>

#include <Db/DbRow.h>
#include <Db/DbValue.h>

namespace Db {

class DbRowValue
	: public DbRow

{

public:

	/* DbRow */

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

	DbRowValue(Tizen::Io::DbColumnType	theValueType) : theDbValue(theValueType) {}
	virtual ~DbRowValue(){};

public:

	DbValue theDbValue;

};

}

#endif /* DBROWVALUE_H_ */
