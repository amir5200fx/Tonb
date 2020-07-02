#pragma once
#ifndef _Marine_xCmpSection_Header
#define _Marine_xCmpSection_Header

#include <Marine_CmpSection.hxx>

namespace tnbLib
{

	class Marine_xCmpSection
		: public Marine_CmpSection
	{

		/*Private Data*/

	public:

		/*Marine_xCmpSection();

		Marine_xCmpSection
		(
			const Standard_Integer theIndex
		);

		Marine_xCmpSection
		(
			const Standard_Integer theIndex, 
			const word& theName
		);*/

		template<class... _Types>
		Marine_xCmpSection(_Types&&... _Args)
			: Marine_CmpSection(_Args...)
		{}

		Standard_Boolean IsXsection() const override
		{
			return Standard_True;
		}

		std::shared_ptr<Marine_CmpSection> Copy() const override;

		/*static std::shared_ptr<Marine_CmpSection>
			CreateCmpSection
			(
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
				const gp_Ax2& theSystem,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::shared_ptr<Marine_CmpSection>
			CreateCmpSection
			(
				const std::vector<Handle(Geom2d_Curve)>& theCurves,
				const gp_Ax2& theSystem,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);

		static std::shared_ptr<Marine_CmpSection>
			CreateCmpSection
			(
				const TopoDS_Shape& theEdges,
				const gp_Ax2& theSystem,
				const Standard_Real theMinTol,
				const Standard_Real theMaxTol
			);*/
	};
}

#endif // !_Marine_xCmpSection_Header
