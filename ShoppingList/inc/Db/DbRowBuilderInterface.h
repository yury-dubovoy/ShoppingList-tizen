#ifndef LISTITEMBUILDERINTERFACE_H_
#define LISTITEMBUILDERINTERFACE_H_

#include <Db/DbRow.h>

namespace Db {

class DbRowBuilderInterface
{

public:

	virtual ~DbRowBuilderInterface(){}

public:

	virtual Db::DbRow*
	BuildNewRowN(unsigned int tableId, unsigned int rowIndex, void* content = null) const = 0;

};

}

#endif /* LISTITEMBUILDERINTERFACEINTERFACE_H_ */
