#pragma once
#ifndef _Marine_zCmpSection_Header
#define _Marine_zCmpSection_Header

#include <Marine_CmpSection.hxx>

namespace tnbLib
{

	class Marine_zCmpSection
		: public Marine_CmpSection
	{

		/*Private Data*/

	public:

		Marine_zCmpSection();

		Marine_zCmpSection
		(
			const Standard_Integer theIndex
		);

		Marine_zCmpSection
		(
			const Standard_Integer theIndex,
			const word& theName
		);


		Standard_Boolean IsZsection() const override
		{
			return Standard_True;
		}

		Standard_Real X() const override;

		std::shared_ptr<Marine_CmpSection> Copy() const override;

		static std::shared_ptr<Marine_CmpSection>
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
			);
	};
}

#endif // !_Marine_zCmpSection_Header
