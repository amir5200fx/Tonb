#pragma once
#ifndef _PtdModel_Curve_Header
#define _PtdModel_Curve_Header

#include <PtdModel_Entity.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Standard_Handle.hxx>

namespace tnbLib
{

	template<class GeomCurve>
	class PtdModel_Curve
		: public PtdModel_Entity
	{

		/*Private Data*/

		Handle(GeomCurve) theGeometry_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			//- this function is not supposed to be called
			NotImplemented;
		}

	public:

		//- default constructor

		PtdModel_Curve()
		{}


		//- constructors

		PtdModel_Curve(const Handle(GeomCurve)& theGeometry)
			: theGeometry_(theGeometry)
		{}

		PtdModel_Curve(Handle(GeomCurve)&& theGeometry)
			: theGeometry_(std::move(theGeometry))
		{}


		//- public functions and operators

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		void SetGeometry(const Handle(GeomCurve)& theGeometry)
		{
			theGeometry_ = theGeometry;
		}

		void SetGeometry(Handle(GeomCurve)&& theGeometry)
		{
			theGeometry_ = std::move(theGeometry);
		}

	};
}

#endif // !_PtdModel_Curve_Header
