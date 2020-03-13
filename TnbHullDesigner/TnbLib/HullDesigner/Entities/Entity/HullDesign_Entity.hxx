#pragma once
#ifndef _HullDesign_Entity_Header
#define _HullDesign_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>

namespace tnbLib
{

	class HullDesign_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<HullDesign_Entity>
	{

		/*Private Data*/

	protected:

		HullDesign_Entity();

		HullDesign_Entity(const Standard_Integer theIndex);

		HullDesign_Entity(const Standard_Integer theIndex, const word& theName);

	public:

		virtual ~HullDesign_Entity()
		{}
	};
}

#endif // !_HullDesign_Entity_Header
