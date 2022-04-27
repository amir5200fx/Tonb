#pragma once
#ifndef _Aft2d_LineNodeTemplate_Header
#define _Aft2d_LineNodeTemplate_Header

#include <Aft2d_SingularNodeTemplate.hxx>

namespace tnbLib
{

	template<class BndNodeType>
	class Aft2d_LineNodeTemplate
		: public Aft2d_SingularNodeTemplate<BndNodeType>
	{

		/*Private Data*/

	public:

		// default constructor [4/25/2022 Amir]

		Aft2d_LineNodeTemplate()
		{}

		// constructors [4/25/2022 Amir]

		Aft2d_LineNodeTemplate
		(
			const Standard_Integer theIndex, 
			const Pnt2d& theCoord
		)
			: Aft2d_SingularNodeTemplate<BndNodeType>(theIndex, theCoord)
		{}

		// override functions and operators [4/26/2022 Amir]

		Standard_Boolean IsLine() const override;

		void RemoveThis(const typename BndNodeType::metricPrcsr&) override;

		// static functions and operators [4/25/2022 Amir]

		static std::shared_ptr<BndNodeType> MergeNodes
		(
			const std::shared_ptr<BndNodeType>& theNode0,
			const std::shared_ptr<BndNodeType>& theNode1,
			const Mesh_BndMergeAlg theAlg
		);
	};
}

#include <Aft2d_LineNodeTemplateI.hxx>

#endif // !_Aft2d_LineNodeTemplate_Header
