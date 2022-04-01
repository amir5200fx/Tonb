#pragma once
#ifndef _Cad2d_IntsctEntity_TangSegment_Header
#define _Cad2d_IntsctEntity_TangSegment_Header

#include <Cad2d_IntsctEntity_Segment.hxx>
#include <Cad2d_Module.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve;

	class Cad2d_IntsctEntity_TangSegment
		: public Cad2d_IntsctEntity_Segment
	{

		/*Private Data*/

		Standard_Real theParameter0_;
		Standard_Real theParameter1_;

		Pnt2d theCoord0_;
		Pnt2d theCoord1_;


		// private functions and operators [3/22/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Cad2d_IntsctEntity_Segment>(*this);

			ar& theParameter0_;
			ar& theParameter1_;
			ar& theCoord0_;
			ar& theCoord1_;
		}

	public:

		//- default constructor

		Cad2d_IntsctEntity_TangSegment()
		{}

		//- constructors

		explicit Cad2d_IntsctEntity_TangSegment(const Standard_Integer theIndex)
			: Cad2d_IntsctEntity_Segment(theIndex)
		{}

		Cad2d_IntsctEntity_TangSegment(const Standard_Integer theIndex, const word& theName)
			: Cad2d_IntsctEntity_Segment(theIndex, theName)
		{}

		//- public functions and operators

		TnbCad2d_EXPORT Standard_Real CharParameter() const override;

		//- Macros

		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Parameter0)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Parameter1)

			GLOBAL_ACCESS_SINGLE(Pnt2d, Coord0)
			GLOBAL_ACCESS_SINGLE(Pnt2d, Coord1)
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Cad2d_IntsctEntity_TangSegment);

#endif // !_Cad2d_IntsctEntity_TangSegment_Header
