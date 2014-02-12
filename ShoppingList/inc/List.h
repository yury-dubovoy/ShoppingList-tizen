#ifndef LIST_H_
#define LIST_H_

#include <FBase.h>

namespace Content {

class List
{

public:

	List();

public:

	void
	Clear();

public:						/* номер столбца в таблице */

	Tizen::Base::Long	id; 			// 0

	Tizen::Base::String	name;			// 1

};
}

#endif /* LIST_H_ */
