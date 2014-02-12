#include "RowList.h"

using namespace Content;
using namespace Tizen::Base;
using namespace Tizen::Io;


RowList::RowList(List* pList)
{
	this->pList = pList;
}

RowList::~RowList()
{
	delete pList; pList = null;
}


void
RowList::AddInt(unsigned int columnIndex, int value)
{
	switch (columnIndex)
	{
		case 0:
			pList->id = value;
			break;
		default:
			AppLogDebug("ERROR: invalid column index! [%i]", columnIndex);
			break;
	}
}


void
RowList::AddText(unsigned int columnIndex, const Tizen::Base::String& value)
{
	switch (columnIndex)
	{
		case 1:
			pList->name = value;
			break;
		default:
			AppLogDebug("ERROR: invalid column index! [%i]", columnIndex);
			break;
	}
}


unsigned int
RowList::GetColumnCount()
{
	return 2;
}


Tizen::Io::DbColumnType
RowList::GetColumnType(unsigned int columnIndex)
{
	Tizen::Io::DbColumnType columnType;
	switch (columnIndex)
	{
		case 0:
			columnType = Tizen::Io::DB_COLUMNTYPE_INT;
			break;
		case 1:
			columnType = Tizen::Io::DB_COLUMNTYPE_TEXT;
			break;
		default:
			AppLogDebug("ERROR: invalid column index! [%i]", columnIndex);
			break;
	}
	return columnType;
}


void
RowList::GetInt(unsigned int columnIndex, int& value)
{
	switch (columnIndex) {
		case 0:
			value = pList->id.value;
			break;
		default:
			AppLogDebug("ERROR: invalid column index! [%i]", columnIndex);
			break;
	}
	return;
}


void
RowList::GetText(unsigned int columnIndex, Tizen::Base::String*& pValue)
{
	switch (columnIndex) {
		case 1:
			pValue = &pList->name;
			break;
		default:
			AppLogDebug("ERROR: invalid column index! [%i]", columnIndex);
			break;
	}
}
