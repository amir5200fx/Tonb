#pragma once
#ifndef _Cad_SingularCurve_Header
#define _Cad_SingularCurve_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>

class Geom2d_Curve;

namespace tnbLib
{

	template<class CurveType>
	class Cad_SingularCurve
		: public CurveType
	{

	public:

		//typedef typename CurveType::geomType geomType;

	private:

		/*Private Data*/


		// private functions and operators [12/31/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<CurveType>(*this);
		}

	protected:

		// default constructor [12/31/2021 Amir]


		// constructors [12/31/2021 Amir]

		Cad_SingularCurve(const Handle(Geom2d_Curve)& theGeometry)
			: CurveType(theGeometry)
		{}

		Cad_SingularCurve(Handle(Geom2d_Curve)&& theGeometry)
			: CurveType(std::move(theGeometry))
		{}


	public:

		// public functions and operators [12/31/2021 Amir]

		virtual Standard_Boolean IsPole() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsLine() const
		{
			return Standard_False;
		}

	};
}

#endif // !_Cad_SingularCurve_Header

