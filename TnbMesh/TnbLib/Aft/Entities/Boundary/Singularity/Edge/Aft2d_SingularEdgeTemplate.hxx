#pragma once
#ifndef _Aft2d_SingularEdgeTemplate_Header
#define _Aft2d_SingularEdgeTemplate_Header

#include <Global_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	template<class BndEdgeType>
	class Aft2d_SingularEdgeTemplate
		: public BndEdgeType
	{

		/*Private Data*/

	protected:

		typedef typename BndEdgeType::bndNodeType bndNodeType;
		typedef typename BndEdgeType::bndEdgeType bndEdgeType;


		// default constructor [4/25/2022 Amir]

		Aft2d_SingularEdgeTemplate()
		{}


		// constructors [4/25/2022 Amir]

		explicit Aft2d_SingularEdgeTemplate(const Standard_Integer theIndex)
			: BndEdgeType(theIndex)
		{}

		Aft2d_SingularEdgeTemplate
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<typename BndEdgeType::nodeType>& theNode0,
			const std::shared_ptr<typename BndEdgeType::nodeType>& theNode1
		)
			: BndEdgeType(theIndex, theNode0, theNode1)
		{}

	public:

		typedef BndEdgeType base;

		// public functions and operators [4/25/2022 Amir]

		Standard_Boolean IsSingular() const override
		{
			return Standard_True;
		}

		//- Static functions and operators
	};
}

#endif // !_Aft2d_SingularEdgeTemplate_Header
