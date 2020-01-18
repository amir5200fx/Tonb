#pragma once
#ifndef _Pln_Entity_Header
#define _Pln_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>

namespace tnbLib
{

	class Pln_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<Pln_Entity>
	{

		/*Private Data*/

	protected:

		Pln_Entity()
		{}

		Pln_Entity(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

		Pln_Entity
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:

		std::shared_ptr<Pln_Entity> This() const
		{
			return std::const_pointer_cast<Pln_Entity>(this->shared_from_this());
		}
	};
}

#endif // !_Pln_Entity_Header
