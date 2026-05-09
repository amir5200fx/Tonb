#pragma once
#ifndef _PtdShapeFit2d_TypedAirfoil_S833Offsets_Header
#define _PtdShapeFit2d_TypedAirfoil_S833Offsets_Header

#include <PtdShapeFit2d_TypedAirfoil_Offsets.hxx>

namespace tnbLib
{

	namespace airfoilLib
	{

		namespace offsetsLib
		{

			class S833
				: public PtdShapeFit2d_TypedAirfoil_Offsets
			{

				/*Private Data*/

				TnbPtdShapeFit_EXPORT void SetAirfoilName();
				TnbPtdShapeFit_EXPORT void SetOffsets();

				// Private functions and operators [5/5/2023 Payvand]


				friend class boost::serialization::access;

				template<class Archive>
				void serialize(Archive& ar, const unsigned file_version)
				{
					ar& boost::serialization::base_object<PtdShapeFit2d_TypedAirfoil_Offsets>(*this);
				}

			public:

				static TnbPtdShapeFit_EXPORT const char* type_name;
				static TnbPtdShapeFit_EXPORT const char* airfoil_type_name;

				// default constructor [5/5/2023 Payvand]

				TnbPtdShapeFit_EXPORT S833();

				// constructors [5/5/2023 Payvand]


				// Public functions and operators [5/5/2023 Payvand]

				TnbPtdShapeFit_EXPORT word OffsetTypeName() const override;

			};
		}
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::airfoilLib::offsetsLib::S833);

#endif // !_PtdShapeFit2d_TypedAirfoil_S833Offsets_Header
