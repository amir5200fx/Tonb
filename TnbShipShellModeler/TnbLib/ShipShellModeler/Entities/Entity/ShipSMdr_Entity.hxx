#pragma once
#ifndef _ShipSMdr_Entity_Header
#define _ShipSMdr_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>

namespace tnbLib
{

	class ShipSMdr_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<ShipSMdr_Entity>
	{

		/*Private Data*/

	protected:

		ShipSMdr_Entity();

		ShipSMdr_Entity(const Standard_Integer theIndex);

		ShipSMdr_Entity(const Standard_Integer theIndex, const word& theName);

	public:

		virtual ~ShipSMdr_Entity()
		{}
	};
}

#endif // !_ShipSMdr_Entity_Header
