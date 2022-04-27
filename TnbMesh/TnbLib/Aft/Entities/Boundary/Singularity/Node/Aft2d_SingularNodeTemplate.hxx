#pragma once
#ifndef _Aft2d_SingularNodeTemplate_Header
#define _Aft2d_SingularNodeTemplate_Header

#include <Mesh_BndMergeAlg.hxx>
#include <Pnt2d.hxx>

#include <memory>

namespace tnbLib
{

	template<class BndNodeType>
	class Aft2d_SingularNodeTemplate
		: public BndNodeType
	{

		/*Private Data*/

	protected:

		// default constructor [4/25/2022 Amir]

		Aft2d_SingularNodeTemplate()
		{}


		// constructors [4/25/2022 Amir]

		Aft2d_SingularNodeTemplate
		(
			const Standard_Integer theIndex,
			const Pnt2d& theCoord
		)
			: BndNodeType(theIndex, theCoord)
		{}

	public:

		// override functions and operators [4/26/2022 Amir]

		Standard_Boolean IsSingular() const override;

		// public functions and operators [4/25/2022 Amir]

		virtual Standard_Boolean IsPole() const;
		virtual Standard_Boolean IsLine() const;

		virtual void RemoveThis(const typename BndNodeType::metricPrcsr&) = 0;
	};
}

#include <Aft2d_SingularNodeTemplateI.hxx>

#endif // !_Aft2d_SingularNodeTemplate_Header
