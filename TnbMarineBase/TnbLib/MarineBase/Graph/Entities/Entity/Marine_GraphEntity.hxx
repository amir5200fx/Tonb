#pragma once
#ifndef _Marine_GraphEntity_Header
#define _Marine_GraphEntity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Marine_Module.hxx>

#include <memory>

namespace tnbLib
{

	class Marine_GraphEntity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<Marine_GraphEntity>
	{

		/*Private Data*/

	protected:

		TnbMarine_EXPORT Marine_GraphEntity();

		TnbMarine_EXPORT Marine_GraphEntity
		(
			const Standard_Integer theIndex
		);

		TnbMarine_EXPORT Marine_GraphEntity
		(
			const Standard_Integer theIndex, 
			const word& theName
		);

	public:

		virtual ~Marine_GraphEntity()
		{}
	};
}

#endif // !_Marine_GraphEntity_Header
