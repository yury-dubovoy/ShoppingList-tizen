#include <Db/DbDataSet.h>

using namespace Db;

int DbDataSet::tableIdIncrementor = 0;

DbDataSet::DbDataSet()
{
	tableId = ++tableIdIncrementor;
	pRowBuilder = null;
	isIndexesReversed = false;
	vRows.clear();
}

DbDataSet::~DbDataSet()
{
	int count = vRows.size();
	for (int i=0; i<count; i++)
	{
		delete vRows[i];
	}
}


Db::DbRow*
DbDataSet::AddNewRowToEnd()
{
	return AddNewRowToEndInner(null);
}


Db::DbRow*
DbDataSet::AddNewRowToEndInner(void* content)
{
	if (pRowBuilder == null)
	{
		AppLogDebug("ERROR: pRowBuilder is null!");
		return null;
	}
	Db::DbRow* pNewRow = null;
	pNewRow = pRowBuilder->BuildNewRowN(tableId, vRows.size(), content);
	if (pNewRow == null)
	{
		AppLogDebug("ERROR: pNewRow is null!");
		return null;
	}
	vRows.push_back(pNewRow);
	return pNewRow;
}


Db::DbRow*
DbDataSet::AddNewRowToEndN(void* content)
{
	return AddNewRowToEndInner(content);
}


Db::DbRow*
DbDataSet::AddNewRowToFront()
{
	if (pRowBuilder == null)
	{
		AppLogDebug("ERROR: pRowBuilder is null!");
		return null;
	}
	Db::DbRow* pNewRow = null;
	pNewRow = pRowBuilder->BuildNewRowN(tableId, vRows.size());
	if (pNewRow == null)
	{
		AppLogDebug("ERROR: pNewRow is null!");
		return null;
	}

	unsigned int count = vRows.size();
	vRows.push_back(null);
	for(unsigned int i = 0; i < count; i++)
	{
		vRows[i+1] = vRows[i];
	}
	vRows.front() = pNewRow;

	return pNewRow;
}


unsigned int
DbDataSet::GetId()
{
	return tableId;
}


Db::DbRow*
DbDataSet::GetRow(unsigned int rowIndex)
{
	unsigned int rowCount = vRows.size();
	if (rowIndex >= rowCount)
	{
		AppLogDebug("ERROR: invalid rowIndex! Index: [%i]", rowIndex);
		return null;
	}
	if (isIndexesReversed)
	{
		rowIndex = rowCount - 1 - rowIndex;
	}
	return vRows[rowIndex];
}


unsigned int
DbDataSet::GetRowCount()
{
	return vRows.size();
}


result
DbDataSet::RemoveAllRows()
{
	int rowCount = vRows.size();
	for (int i=0; i<rowCount; i++)
	{
		delete vRows[i];
	}
	vRows.clear();
	return E_SUCCESS;
}


result
DbDataSet::RemoveRow(unsigned int rowIndex)
{
	unsigned int rowCount = vRows.size();
	if (rowIndex >= rowCount)
	{
		AppLogDebug("ERROR: invalid rowIndex! Index: [%i]", rowIndex);
		return E_FAILURE;
	}
	if (isIndexesReversed)
	{
		rowIndex = rowCount - 1 - rowIndex;
	}
	vRows.erase(vRows.begin()+rowIndex);
	return E_FAILURE;
}


void
DbDataSet::SetIsIndexesReversed(bool value)
{
	isIndexesReversed = value;
}


void
DbDataSet::SetRowBulder(DbRowBuilderInterface* pRowBuilder)
{
	this->pRowBuilder = pRowBuilder;
}

