#pragma once
#ifndef _Cad2d_IntsctEntity_OrthSegment_Header
#define _Cad2d_IntsctEntity_OrthSegment_Header

#include <Cad2d_IntsctEntity_Segment.hxx>
#include <Pnt2d.hxx>
#include <Cad2d_Module.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve;

	class Cad2d_IntsctEntity_OrthSegment
		: public Cad2d_IntsctEntity_Segment
	{

		/*Private Data*/

		Standard_Real theParameter_;

		Pnt2d theCoord_;


		// private functions and operators [3/22/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Cad2d_IntsctEntity_Segment>(*this);
			ar& theParameter_;
			ar& theCoord_;
		}

	public:


		//- default constructor

		Cad2d_IntsctEntity_OrthSegment()
			: theParameter_(0)
			, theCoord_(Pnt2d::null)
		{}

		//- constructors

		explicit Cad2d_IntsctEntity_OrthSegment(const Standard_Integer theIndex)
			: Cad2d_IntsctEntity_Segment(theIndex)
			, theParameter_(0)
			, theCoord_(Pnt2d::null)
		{}

		Cad2d_IntsctEntity_OrthSegment(const Standard_Integer theIndex, const word& theName)
			: Cad2d_IntsctEntity_Segment(theIndex, theName)
			, theParameter_(0)
			, theCoord_(Pnt2d::null)
		{}


		//- public functions and operators

		Standard_Boolean IsOrthogonal() const override
		{
			return Standard_True;
		}

		Standard_Real CharParameter() const override
		{
			return theParameter_;
		}

		static TnbCad2d_EXPORT std::tuple<std::shared_ptr<Pln_Curve>, std::shared_ptr<Pln_Curve>>
			SubdivideCurve
			(
				const Pln_Curve& theCurve, 
				const Cad2d_IntsctEntity_OrthSegment& theEntity
			);


		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Parameter)

			GLOBAL_ACCESS_SINGLE(Pnt2d, Coord)
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Cad2d_IntsctEntity_OrthSegment);

#endif // !_Cad2d_IntsctEntity_OrthSegment_Header
