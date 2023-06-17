#pragma once
#ifndef _PtdShapeFit2d_TypedAirfoil_MH102Offsets_Header
#define _PtdShapeFit2d_TypedAirfoil_MH102Offsets_Header

#include <PtdShapeFit2d_TypedAirfoil_Offsets.hxx>

namespace tnbLib
{

	namespace airfoilLib
	{

		namespace offsetsLib
		{

			class MH102
				: public PtdShapeFit2d_TypedAirfoil_Offsets
			{

				/*Private Data*/

				TnbPtdShapeFit_EXPORT void SetAirfoilName();
				TnbPtdShapeFit_EXPORT void SetOffsets();


				// Private functions and operators [5/1/2023 Payvand]

				friend class boost::serialization::access;

				template<class Archive>
				void serialize(Archive& ar, const unsigned file_version)
				{
					ar& boost::serialization::base_object<PtdShapeFit2d_TypedAirfoil_Offsets>(*this);
				}

			public:

				static TnbPtdShapeFit_EXPORT const char* type_name;
				static TnbPtdShapeFit_EXPORT const char* airfoil_type_name;

				// default constructor [5/1/2023 Payvand]

				TnbPtdShapeFit_EXPORT MH102();

				// constructors [5/1/2023 Payvand]


				// Public functions and operators [5/1/2023 Payvand]

				TnbPtdShapeFit_EXPORT word OffsetTypeName() const override;

			};
		}
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::airfoilLib::offsetsLib::MH102);

#endif // !_PtdShapeFit2d_TypedAirfoil_MH102Offsets_Header
