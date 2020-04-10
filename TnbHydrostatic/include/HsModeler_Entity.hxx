#pragma once
#ifndef _HsModeler_Entity_Header
#define _HsModeler_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>

namespace tnbLib
{

	class HsModeler_Entity
		: public std::enable_shared_from_this<HsModeler_Entity>
	{

		/*Private Data*/

	protected:

		HsModeler_Entity();

		HsModeler_Entity(const Standard_Integer theIndex);

		HsModeler_Entity(const Standard_Integer theIndex, const word& theName);

	public:

		virtual ~HsModeler_Entity()
		{}
	};
}

#endif // !_HsModeler_Entity_Header
