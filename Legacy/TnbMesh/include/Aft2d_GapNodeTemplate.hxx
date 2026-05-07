#pragma once
#ifndef _Aft2d_GapNodeTemplate_Header
#define _Aft2d_GapNodeTemplate_Header

#include <Mesh_BndMergeAlg.hxx>
#include <Pnt2d.hxx>

#include <memory>

namespace tnbLib
{

	template<class BndNodeType>
	class Aft2d_GapNodeTemplate
		: public BndNodeType
	{

		/*Private Data*/

		Standard_Boolean IsFixed_;

	public:

		// default constructor [5/13/2022 Amir]

		Aft2d_GapNodeTemplate()
			: IsFixed_(Standard_False)
		{}


		// constructors [5/13/2022 Amir]

		Aft2d_GapNodeTemplate
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: BndNodeType(theIndex, theCoord)
			, IsFixed_(Standard_False)
		{}


	public:

		typedef typename BndNodeType::edgeType edgeType;

		// override functions and operators [5/13/2022 Amir]

		Standard_Boolean IsGap() const override
		{
			return Standard_True;
		}

		Standard_Boolean IsRegular() const override
		{
			return Standard_False;
		}

		std::shared_ptr<edgeType> BlowThisUp() override;

		// public functions and operators [5/13/2022 Amir]

		auto IsFixed() const
		{
			return IsFixed_;
		}

		auto& IsFixedRef()
		{
			return IsFixed_;
		}

		// static functions and operators [5/13/2022 Amir]

		static std::shared_ptr<BndNodeType> MergeNodes
		(
			const std::shared_ptr<BndNodeType>& theNode0,
			const std::shared_ptr<BndNodeType>& theNode1,
			const Mesh_BndMergeAlg theAlg
		);
	};
}

#include <Aft2d_GapNodeTemplateI.hxx>

#endif // !_Aft2d_GapNodeTemplate_Header
