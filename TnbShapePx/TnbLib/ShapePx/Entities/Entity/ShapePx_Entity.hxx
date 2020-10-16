#pragma once
#ifndef _ShapePx_Entity_Header
#define _ShapePx_Entity_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>

namespace tnbLib
{

	class ShapePx_Entity
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<ShapePx_Entity>
	{

		/*Private Data*/

	protected:

		ShapePx_Entity()
		{}

		ShapePx_Entity(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

		ShapePx_Entity
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

	public:

		virtual ~ShapePx_Entity()
		{}

		std::shared_ptr<ShapePx_Entity> This() const
		{
			return std::const_pointer_cast<ShapePx_Entity>(this->shared_from_this());
		}

	};
}

#endif // !_ShapePx_Entity_Header
