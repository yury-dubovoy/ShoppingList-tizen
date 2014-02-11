#include <Db/DbAccess.h>

#include <FApp.h>

#include <Db/DbRowValue.h>

using namespace Db;
using namespace std;
using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Io;

DbAccess::DbAccess()
{
	isConnected = false;
	isConstructed = false;
	pDatabase = null;
}


DbAccess::~DbAccess()
{
	delete pDatabase; pDatabase = null;
}


result
DbAccess::AssignParams(DbStatement* pStmt, const vector<DbValue>& params)
{
	result r = E_SUCCESS;

	unsigned int paramsCount = params.size();
	for (unsigned int i=0; i<paramsCount; i++)
	{
		switch (params[i].theValueType) {
			case DB_COLUMNTYPE_INT:
				r = pStmt->BindInt(i, params[i].valueInt);
				if (IsFailed(r))
				{
					AppLogDebug("ERROR: BindInt() failed! Int: [%i]; Index: [i]",
									params[i].valueInt, i);
					delete pStmt;
					return r;
				}
				break;
			case DB_COLUMNTYPE_INT64:
				r = pStmt->BindInt64(i, params[i].valueInt64);
				if (IsFailed(r))
				{
					AppLogDebug("ERROR: BindInt64() failed! Int64: [%li]; Index: [i]",
									params[i].valueInt64, i);
					delete pStmt;
					return r;
				}
				break;
			case DB_COLUMNTYPE_BLOB:
				r = pStmt->BindBlob(i, *(params[i].pValueBlob));
				if (IsFailed(r))
				{
					AppLogDebug("ERROR: BindBlob() failed! Index: [i]", i);
					delete pStmt;
					return r;
				}
				break;
			case DB_COLUMNTYPE_TEXT:
				r = pStmt->BindString(i, params[i].valueString);
				if (IsFailed(r))
				{
					AppLogDebug("ERROR: BindString() failed! String: [%S]; Index: [i]",
									params[i].valueString.GetPointer(), i);
					delete pStmt;
					return r;
				}
				break;
			default:
				break;
		}
	}

	return r;
}


DbRow*
DbAccess::BuildNewRowN(unsigned int tableId, unsigned int rowIndex, void* content) const
{
	DbRow* pRow = null;
	if (tableId == theDataSetIdGetValue)
	{
		pRow = new DbRowValue(theGetValueType);
	}
	else
	{
		AppLogDebug("ERROR: invalid dataset id! [%i]", tableId);
	}
	return pRow;
}


result
DbAccess::Close()
{
	if (isConnected == false)
	{
		AppLogDebug("ERROR: already closed!");
		return E_FAILURE;
	}

	delete pDatabase; pDatabase = null;
	isConnected = false;

	return E_SUCCESS;
}


result
DbAccess::Connect(const String& dbName)
{
	String strDbPath = "";

	result r = E_SUCCESS;
	strDbPath = App::GetInstance()->GetAppDataPath() + dbName;

    if (isConstructed == false)
	{
		AppLogDebug("ERROR: not constructed yet!");
		return E_FAILURE;
	}
	if (isConnected == true)
	{
		AppLogDebug("ERROR: already connected!");
		return E_FAILURE;
	}

	pDatabase = new Database;
	if (!pDatabase->Exists(strDbPath))
	{
		AppLogDebug("ERROR: database file not found! File path: [%S]", dbName.GetPointer());
		return E_FAILURE;
	}

	r = pDatabase->Construct(strDbPath, "r+");
	if (IsFailed(r))
	{
		AppLogDebug("ERROR: a Database object is not constructed! File path: [%S]", dbName.GetPointer());
		return r;
	}

	isConnected = true;
	return E_SUCCESS;
}


result
DbAccess::Construct()
{
	// по идее, здесь пока ничего вообще делать не надо, но флаг оставляем на будущее расширения
	if (isConstructed == true)
	{
		AppLogDebug("ERROR: already constructed!");
		return E_FAILURE;
	}
	isConstructed = true;
	return E_SUCCESS;
}


result
DbAccess::FillDataSet(const DbQuery& sqlQuery, DbDataSet& table)
{
	if (!isConnected)
	{
		AppLogDebug("ERROR: the database is not connected!");
		return E_FAILURE;
	}

	result r = E_SUCCESS;


	Tizen::Io::DbStatement* pStmt = null;
	Tizen::Io::DbEnumerator* pEnum = null;

	r = pDatabase->BeginTransaction();
	if (IsFailed(r))
	{
		AppLogDebug("ERROR: transaction begin failed!");
		return r;
	}

	pStmt = pDatabase->CreateStatementN(sqlQuery.queryString);
	if (pStmt == null)
	{
		AppLogDebug("ERROR: creating of statement failed! [%S]", sqlQuery.queryString.GetPointer());
		return r;
	}

	r = AssignParams(pStmt, sqlQuery.queryParams);
	if(IsFailed(r))
	{
		AppLogDebug("ERROR: cannot assign params! Query: [%S]", sqlQuery.queryString.GetPointer());
		return r;
	}

	pEnum = pDatabase->ExecuteStatementN(*pStmt);
	if (pEnum == null)
	{
		AppLogDebug("WARNING: nothing found!");
		pDatabase->RollbackTransaction();
		delete pStmt;
		return E_SUCCESS;
	}

	if (IsFailed(GetLastResult()))
	{
		AppLogDebug("ERROR: executing of statement failed!");
		delete pStmt;
		delete pEnum;
		return r;
	}
	int theValueInt = 0;
	long long theValueInt64 = 0;
	Tizen::Base::String theValueText = "";
	Tizen::Base::ByteBuffer* pValueBlob = null;
	while (pEnum->MoveNext()== E_SUCCESS)
	{
		DbRow* pRow = null;
		pRow = table.AddNewRowToEnd();
		if (pRow == null)
		{
			AppLogDebug("ERROR: newly created row is null!");
			return E_FAILURE;
		}

		int column_count = pEnum->GetColumnCount();

		for (int i=0; i<column_count; i++)
		{
			Tizen::Io::DbColumnType columnType = pEnum->GetColumnType(i);
			switch (columnType)
			{
				case DB_COLUMNTYPE_BLOB:
					pValueBlob = new ByteBuffer(); pValueBlob->Construct(65636); // 64 кб - лимит на картинку 100x100
					r = pEnum->GetBlobAt(i, *pValueBlob);
					if (IsFailed(r))
					{
						AppLog("ERROR: cannot get a BLOB value! Column index: [%i]", i);
						break;
						goto ERROR;
					}
					pValueBlob->Flip();
					pRow->AddBlobN(i, pValueBlob);
					break;
				case DB_COLUMNTYPE_INT:
					r = pEnum->GetIntAt(i, theValueInt);
					if (IsFailed(r))
					{
						AppLogDebug("ERROR: cannot get a INT value! Column index: [%i]", i);
						goto ERROR;
					}
					pRow->AddInt(i, theValueInt);
					break;
				case DB_COLUMNTYPE_INT64:
					r = pEnum->GetInt64At(i, theValueInt64);
					if (IsFailed(r))
					{
						AppLogDebug("ERROR: cannot get a INT64 value! Column index: [%i]", i);
						goto ERROR;
					}
					pRow->AddInt64(i, theValueInt);
					break;
				case DB_COLUMNTYPE_TEXT:
					r = pEnum->GetStringAt(i, theValueText);
					if (IsFailed(r))
					{
						AppLogDebug("ERROR: cannot get a TEXT value! Column index: [%i]", i);
						goto ERROR;
					}
					pRow->AddText(i, theValueText);
					break;
				case DB_COLUMNTYPE_NULL:
					break;
				default:
					AppLogDebug("ERROR: unknown column type! [%i]", columnType);
					goto ERROR;
					break;
			}
		}
	}

	r = pDatabase->CommitTransaction();
	if (IsFailed(r))
	{
		AppLogDebug("ERROR: transaction commit failed!");
		delete pStmt;
		delete pEnum;
		return r;
	}

	delete pStmt;
	delete pEnum;

	return E_SUCCESS;

	ERROR:

	pDatabase->RollbackTransaction();

	delete pStmt;
	delete pEnum;

	return r;

}


result
DbAccess::GetValue(const DbQuery& sqlQuery, DbValue& theValue)
{
	result r = E_SUCCESS;

	theGetValueType = theValue.theValueType;

	DbDataSet theDataSet;
	theDataSetIdGetValue = theDataSet.GetId();
	theDataSet.SetRowBulder(this);
	r = FillDataSet(sqlQuery, theDataSet);
	if(IsFailed(r))
	{
		AppLogDebug("ERROR: cannot fill dataSet! [%S]", sqlQuery.queryString.GetPointer());
		return r;
	}
	unsigned int count = theDataSet.GetRowCount();
	for (unsigned int i = 0; i<count; i++)
	{
		DbRowValue* pRow = dynamic_cast<DbRowValue*>(theDataSet.GetRow(i));
		theValue = pRow->theDbValue;
		break;
	}

	return r;
}


result
DbAccess::PerformRequest(const DbQuery& sqlQuery)
{
	if (!isConnected)
	{
		AppLogDebug("ERROR: the database is not connected!");
		return E_FAILURE;
	}

	result r = E_SUCCESS;

	Tizen::Io::DbStatement* pStmt = null;
	Tizen::Io::DbEnumerator* pEnum = null;

	r = pDatabase->BeginTransaction();
	if (IsFailed(r))
	{
		AppLogDebug("ERROR: transaction begin failed!");
		return r;
	}

	pStmt = pDatabase->CreateStatementN(sqlQuery.queryString);
	if (pStmt == null)
	{
		AppLogDebug("ERROR: creating of statement failed! [%S]", sqlQuery.queryString.GetPointer());
		goto ERROR;
	}

	r = AssignParams(pStmt, sqlQuery.queryParams);
	if(IsFailed(r))
	{
		AppLogDebug("ERROR: cannot assign params! Query: [%S]", sqlQuery.queryString.GetPointer());
		return r;
	}

	pEnum = pDatabase->ExecuteStatementN(*pStmt);
	if (IsFailed(GetLastResult()))
	{
		AppLogDebug("ERROR: executing of statement failed!");
		goto ERROR;
	}

	delete pStmt;
	delete pEnum;

	r = pDatabase->CommitTransaction();
	if (IsFailed(r))
	{
		AppLogDebug("ERROR: transaction commit failed!");
		return r;
	}

	return E_SUCCESS;

	ERROR:

	pDatabase->RollbackTransaction();

	delete pStmt;
	delete pEnum;

	return E_FAILURE;

}


result
DbAccess::PerformRequest(const String& strQueryString)
{
	DbQuery theQuery;
	theQuery.queryString = strQueryString;
	return PerformRequest(theQuery);
}

result
DbAccess::UploadDataSet(const String& strQueryString, DbDataSet& table)
{
	if (!isConnected)
	{
		AppLogDebug("ERROR: the database is not connected!");
		return E_FAILURE;
	}

	result r = E_SUCCESS;

	Tizen::Io::DbStatement* pStmt = null;
	Tizen::Io::DbEnumerator* pEnum = null;

	r = pDatabase->BeginTransaction();
	if (IsFailed(r))
	{
		AppLogDebug("ERROR: transaction begin failed!");
		return r;
	}

	int row_count = table.GetRowCount();
	for (int j = 0; j < row_count; j++)
	{
		pStmt = pDatabase->CreateStatementN(strQueryString);
		if (pStmt == null)
		{
			AppLogDebug("ERROR: creating of statement failed! [%S]", strQueryString.GetPointer());
			goto ERROR;
		}

		DbRow* pRow = null;
		pRow = dynamic_cast<DbRow*>(table.GetRow(j));
		if (pRow == null)
		{
			AppLogDebug("ERROR: row is null! Index: [%i]", j);
			return E_FAILURE;
		}
		unsigned int paramsCount = pRow->GetColumnCount();
		for (unsigned int i=0; i<paramsCount; i++)
		{
			int			valueInt;
			long long	valueInt64;
			ByteBuffer*	pValueBlob;
			String*		pValueText;
			Tizen::Io::DbColumnType columnType = pRow->GetColumnType(i);
			switch (columnType)
			{
				case DB_COLUMNTYPE_BLOB:
					pRow->GetBlob(i, pValueBlob);
					pValueBlob->SetPosition(0);
					r = pStmt->BindBlob(i, *pValueBlob);
					if (IsFailed(r))
					{
						AppLogDebug("ERROR: cannot bind a BLOB value! Column index: [%i]", i);
						goto ERROR;
					}
					break;
				case DB_COLUMNTYPE_INT:
					pRow->GetInt(i, valueInt);
					r = pStmt->BindInt(i, valueInt);
					if (IsFailed(r))
					{
						AppLogDebug("ERROR: cannot bind a INT value! Column index: [%i]", i);
						goto ERROR;
					}
					break;
				case DB_COLUMNTYPE_INT64:
					pRow->GetInt64(i, valueInt64);
					r = pStmt->BindInt64(i, valueInt64);
					if (IsFailed(r))
					{
						AppLogDebug("ERROR: cannot bind a INT64 value! Column index: [%i]", i);
						goto ERROR;
					}
					break;
				case DB_COLUMNTYPE_TEXT:
					pRow->GetText(i, pValueText);
					r = pStmt->BindString(i, *pValueText);
					if (IsFailed(r))
					{
						AppLogDebug("ERROR: cannot bind a TEXT value! Column index: [%i]", i);
						goto ERROR;
					}
					break;
				case DB_COLUMNTYPE_NULL:
					break;
				default:
					AppLogDebug("ERROR: unknown column type! [%i]", columnType);
					goto ERROR;
					break;
			}
		}

		pEnum = pDatabase->ExecuteStatementN(*pStmt);
		if (IsFailed(GetLastResult()))
		{
			AppLogDebug("ERROR: executing of statement failed!");
			goto ERROR;
		}

		delete pStmt;
		delete pEnum;

	}

	r = pDatabase->CommitTransaction();
	if (IsFailed(r))
	{
		AppLogDebug("ERROR: transaction commit failed!");
		return r;
	}

	return E_SUCCESS;

	ERROR:

	pDatabase->RollbackTransaction();

	delete pStmt;
	delete pEnum;

	return r;

}
