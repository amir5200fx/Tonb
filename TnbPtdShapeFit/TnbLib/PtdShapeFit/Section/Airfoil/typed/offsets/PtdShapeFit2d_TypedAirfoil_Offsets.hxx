#pragma once
#ifndef _PtdShapeFit2d_TypedAirfoil_Offsets_Header
#define _PtdShapeFit2d_TypedAirfoil_Offsets_Header

#include <PtdShapeFit_Module.hxx>
#include <Pnt2d.hxx>
#include <Global_Named.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	class PtdShapeFit2d_TypedAirfoil_Offsets
		: public Global_Named
	{

		/*Private Data*/

		std::vector<Pnt2d> theCoords_;


		// Private functions and operators [5/1/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Global_Named>(*this);
			ar& theCoords_;
		}

	protected:

		// default constructor [5/1/2023 Payvand]

		PtdShapeFit2d_TypedAirfoil_Offsets()
		{}

		// constructors [5/1/2023 Payvand]


		// Protected functions and operators [5/1/2023 Payvand]

		auto& CoordsRef()
		{
			return theCoords_;
		}

	public:

		// Public functions and operators [5/1/2023 Payvand]

		const auto& Coords() const
		{
			return theCoords_;
		}

		virtual word OffsetTypeName() const = 0;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdShapeFit2d_TypedAirfoil_Offsets);

#endif // !_PtdShapeFit2d_TypedAirfoil_Offsets_Header
