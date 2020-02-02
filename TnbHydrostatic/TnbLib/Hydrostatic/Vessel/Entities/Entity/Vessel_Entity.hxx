#pragma once
#ifndef _Vessel_Entity_Header
#define _Vessel_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>

namespace tnbLib
{

	class Vessel_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<Vessel_Entity>
	{

		/*Private Data*/

	protected:

		Vessel_Entity()
		{}

		Vessel_Entity
		(
			const Standard_Integer theIndex
		)
			: Global_Indexed(theIndex)
		{}

		Vessel_Entity
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:

		virtual ~Vessel_Entity()
		{}
	};
}

#endif // !_Vessel_Entity_Header
