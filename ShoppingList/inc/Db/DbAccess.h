#ifndef DBACCESS_H_
#define DBACCESS_H_

#include <FBase.h>
#include <FIO.h>

#include <Db/DbQuery.h>
#include <Db/DbRow.h>
#include <Db/DbDataSet.h>
#include <vector>

namespace Db {

class DbAccess
	: public DbRowBuilderInterface
{

	/* DbRowBuilderInterface */

	virtual Db::DbRow*
	BuildNewRowN(unsigned int tableId, unsigned int rowIndex, void* content = null) const;


public:

	DbAccess();
	virtual ~DbAccess();

	virtual result
	Construct();


public:

	result
	Connect(const Tizen::Base::String& dbName);

	result
	Close();

	result
	FillDataSet(const DbQuery& sqlQuery, DbDataSet& table);

	result
	GetValue(const DbQuery& sqlQuery, DbValue& theValue);

	result
	PerformRequest(const DbQuery& sqlQuery);

	result
	PerformRequest(const Tizen::Base::String& strQueryString);

	result
	UploadDataSet(const Tizen::Base::String& strQueryString, DbDataSet& table);

private:

	result
	AssignParams(Tizen::Io::DbStatement* pStmt, const std::vector<DbValue>& params);


protected:

	bool					isConnected;

	Tizen::Io::Database* 	pDatabase;


private:

	bool					isConstructed;

	Tizen::Io::DbColumnType	theGetValueType;
	unsigned int			theDataSetIdGetValue;

};

}

#endif /* DBACCESS_H_ */
