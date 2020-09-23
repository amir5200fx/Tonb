#pragma once
#ifndef _SectPx_Entity_Header
#define _SectPx_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>

namespace tnbLib
{

	class SectPx_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<SectPx_Entity>
	{

		/*Private Data*/

	protected:

		SectPx_Entity()
		{}

		SectPx_Entity
		(
			const Standard_Integer theIndex
		)
			: Global_Indexed(theIndex)
		{}

		SectPx_Entity
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:


		virtual ~SectPx_Entity()
		{}

		std::shared_ptr<SectPx_Entity> This() const
		{
			return std::const_pointer_cast<SectPx_Entity>(this->shared_from_this());
		}
	};
}

#endif // !_SectPx_Entity_Header
