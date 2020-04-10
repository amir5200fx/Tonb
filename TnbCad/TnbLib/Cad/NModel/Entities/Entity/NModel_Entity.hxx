#pragma once
#ifndef _NModel_Entity_Header
#define _NModel_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>

namespace tnbLib
{

	class NModel_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<NModel_Entity>
	{

		/*Private Data*/

	protected:

		NModel_Entity();

		NModel_Entity(const Standard_Integer theIndex);

		NModel_Entity(const Standard_Integer theIndex, const word& theName);

	public:

		virtual ~NModel_Entity()
		{}
	};
}

#endif // !_NModel_Entity_Header
