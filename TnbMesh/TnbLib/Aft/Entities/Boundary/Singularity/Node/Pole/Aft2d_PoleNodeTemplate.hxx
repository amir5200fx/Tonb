#pragma once
#ifndef _Aft2d_PoleNodeTemplate_Header
#define _Aft2d_PoleNodeTemplate_Header

#include <Aft2d_SingularNodeTemplate.hxx>

namespace tnbLib
{

	template<class BndNodeType>
	class Aft2d_PoleNodeTemplate
		: public Aft2d_SingularNodeTemplate<BndNodeType>
	{

		/*Private Data*/

		Standard_Boolean IsFixed_;

	public:

		typedef Aft2d_SingularNodeTemplate<BndNodeType>
			base;

		// default constructor [4/25/2022 Amir]

		Aft2d_PoleNodeTemplate()
			: IsFixed_(Standard_False)
		{}


		// constructors [4/25/2022 Amir]

		Aft2d_PoleNodeTemplate
		(
			const Standard_Integer theIndex, 
			const Pnt2d& theCoord
		)
			: Aft2d_SingularNodeTemplate<BndNodeType>(theIndex, theCoord)
		{}

		// override functions and operators [4/25/2022 Amir]

		Standard_Boolean IsPole() const override;

		void RemoveThis(const typename BndNodeType::metricPrcsr&) override;

		// public functions and operators [4/25/2022 Amir]

		auto IsFixed() const
		{
			return IsFixed_;
		}

		auto& IsFixedRef()
		{
			return IsFixed_;
		}


		// static functions and operators [4/25/2022 Amir]

		static std::shared_ptr<BndNodeType> MergeNodes
		(
			const std::shared_ptr<BndNodeType>& theNode0,
			const std::shared_ptr<BndNodeType>& theNode1,
			const Mesh_BndMergeAlg theAlg
		);
	};
}

#include <Aft2d_PoleNodeTemplateI.hxx>

#endif // !_Aft2d_PoleNodeTemplate_Header
