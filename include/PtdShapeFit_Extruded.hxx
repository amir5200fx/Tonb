#pragma once
#ifndef _PtdShapeFit_Extruded_Header
#define _PtdShapeFit_Extruded_Header

#include <PtdShapeFit_Shape.hxx>

namespace tnbLib
{

	class PtdShapeFit_Extruded
		: public PtdShapeFit_Shape
	{

		/*Private Data*/

		// Private functions and operators [2/12/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<PtdShapeFit_Shape>(*this);
		}

	protected:

		// default constructor [2/12/2023 Payvand]

		PtdShapeFit_Extruded()
		{}

		// constructors [2/12/2023 Payvand]

		PtdShapeFit_Extruded(const Standard_Integer theIndex, const word& theName)
			: PtdShapeFit_Shape(theIndex, theName)
		{}


	public:

		

		// Public functions and operators [2/12/2023 Payvand]

		TnbPtdShapeFit_EXPORT std::shared_ptr<Cad_Shape>
			CreateShape
			(
				const std::vector<std::shared_ptr<PtdShapeFit_Section::Parameters>>&,
				const std::shared_ptr<PtdShapeFit_Section>&,
				const gp_Ax1&,
				const std::vector<Standard_Real>&
			) const override;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdShapeFit_Shape);

#endif // !_PtdShapeFit_Extruded_Header
