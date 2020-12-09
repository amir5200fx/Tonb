#pragma once
#ifndef _HydStatic_Entity_Header
#define _HydStatic_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <HydStatic_Module.hxx>

#include <memory>

namespace tnbLib
{

	class HydStatic_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<HydStatic_Entity>
	{

		/*Private Data*/

	protected:

		TnbHydStatic_EXPORT HydStatic_Entity();

		TnbHydStatic_EXPORT HydStatic_Entity
		(
			const Standard_Integer theIndex
		);

		TnbHydStatic_EXPORT HydStatic_Entity
		(
			const Standard_Integer theIndex,
			const word& theName
		);

	public:

		virtual ~HydStatic_Entity()
		{}


	};
}

#endif // !_HydStatic_Entity_Header
