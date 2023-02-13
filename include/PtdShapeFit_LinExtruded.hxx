#pragma once
#ifndef _PtdShapeFit_LinExtruded_Header
#define _PtdShapeFit_LinExtruded_Header

#include <PtdShapeFit_Extruded.hxx>

namespace tnbLib
{

	// Forward Declarations [2/12/2023 Payvand]

	class PtdShapeFit_Section;

	class PtdShapeFit_LinExtruded
		: public PtdShapeFit_Extruded
	{

	private:

		/*Private Data*/


		// Private functions and operators [2/12/2023 Payvand]

		

	public:

		// default constructor [2/12/2023 Payvand]

		PtdShapeFit_LinExtruded()
		{}

		// constructors [2/12/2023 Payvand]

		PtdShapeFit_LinExtruded(const Standard_Integer theIndex, const word& theName)
			: PtdShapeFit_Extruded(theIndex, theName)
		{}

		// Public functions and operators [2/12/2023 Payvand]

		TnbPtdShapeFit_EXPORT std::vector<std::shared_ptr<PtdShapeFit_Section::Parameters>> 
			CalcParameters
			(
				const std::vector<std::shared_ptr<PtdShapeFit_Section>>& theSections,
				const gp_Ax1& theAxis, 
				const std::vector<Standard_Real>& theXs
			) const override;


		static TnbPtdShapeFit_EXPORT std::vector<Standard_Real> 
			CalcLS
			(
				const std::vector<std::pair<Standard_Real, Standard_Real>>&
			);
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdShapeFit_LinExtruded);

#endif // !_PtdShapeFit_LinExtruded_Header
