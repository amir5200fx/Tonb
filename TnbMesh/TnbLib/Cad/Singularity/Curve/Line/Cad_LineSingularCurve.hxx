#pragma once
#ifndef _Cad_LineSingularCurve_Header
#define _Cad_LineSingularCurve_Header

#include <Cad_SingularCurve.hxx>

namespace tnbLib
{

	template<class CurveType>
	class Cad_LineSingularCurve
		: public Cad_SingularCurve<CurveType>
	{

		/*Private Data*/


		// private functions and operators [12/31/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Cad_SingularCurve<CurveType>>(*this);
		}

	public:

		//typedef typename Cad_SingularCurve<CurveType>::geomType geomType;

		// default constructor [12/31/2021 Amir]


		// constructors [12/31/2021 Amir]

		explicit Cad_LineSingularCurve(const Handle(Geom2d_Curve)& theGeometry)
			: Cad_SingularCurve<CurveType>(theGeometry)
		{}

		Cad_LineSingularCurve(Handle(Geom2d_Curve)&& theGeometry)
			: Cad_SingularCurve<CurveType>(std::move(theGeometry))
		{}


		// public functions and operators [12/31/2021 Amir]

		Standard_Boolean IsLine() const override
		{
			return Standard_True;
		}

	};
}

#endif // !_Cad_LineSingularCurve_Header
