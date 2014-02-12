#ifndef DBDATASET_H_
#define DBDATASET_H_

#include <FBase.h>
#include <vector>

#include <Db/DbRowBuilderInterface.h>

namespace Db {

class DbDataSet
{


public:

	DbDataSet();
	virtual ~DbDataSet();


public:

	Db::DbRow*
	AddNewRowToEnd();

	Db::DbRow*
	AddNewRowToEndN(void* content);

	Db::DbRow*
	AddNewRowToFront();

	unsigned int
	GetId() const;

	Db::DbRow*
	GetRow(unsigned int rowIndex);

	unsigned int
	GetRowCount();

	result
	RemoveAllRows();

	result
	RemoveRow(unsigned int rowIndex);

	void
	SetIsIndexesReversed(bool value);

	void
	SetRowBulder(DbRowBuilderInterface* pRowBuilder);


private:

	Db::DbRow*
	AddNewRowToEndInner(void* content);


private:

	bool						isIndexesReversed;

	DbRowBuilderInterface*		pRowBuilder;

	int							tableId;

	std::vector<Db::DbRow*> 	vRows;

	static int					tableIdIncrementor;

};


}

#endif /* DBDATASET_H_ */
