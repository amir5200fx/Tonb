#pragma once
#ifndef _NModel_Wire_Header
#define _NModel_Wire_Header

#include <NModel_Entity.hxx>
#include <Entity2d_BoxFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class NModel_CmpEdge;

	class NModel_Wire
		: public NModel_Entity
	{

		/*Private Data*/

		std::shared_ptr<NModel_CmpEdge> theEdge_;

	public:

		NModel_Wire
		(
			const std::shared_ptr<NModel_CmpEdge>& theEdge
		);

		NModel_Wire
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<NModel_CmpEdge>& theEdge
		);

		NModel_Wire
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<NModel_CmpEdge>& theEdge
		);


		const auto& CmpEdge() const
		{
			return theEdge_;
		}

		Entity2d_Box CalcParametricBoundingBox() const;
	};
}

#endif // !_NModel_Wire_Header