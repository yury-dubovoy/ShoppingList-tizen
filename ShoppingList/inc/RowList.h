#ifndef ROWLIST_H_
#define ROWLIST_H_

#include <FBase.h>
#include <FIo.h>

#include <Db/DbRow.h>

#include "List.h"

namespace Content {

class RowList
	: public Db::DbRow
{

public:

	virtual void
	AddInt(unsigned int columnIndex, int value);

	virtual void
	AddText(unsigned int columnIndex, const Tizen::Base::String& value);

	virtual unsigned int
	GetColumnCount();

	virtual Tizen::Io::DbColumnType
	GetColumnType(unsigned int columnIndex);

	virtual void
	GetInt(unsigned int columnIndex, int& value);

	virtual void
	GetText(unsigned int columnIndex, Tizen::Base::String*& pValue);

public:

	RowList(List* pList);
	virtual ~RowList();

public:

	List* pList;

};
}

#endif /* ROWLIST_H_ */
