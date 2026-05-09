#pragma once
#ifndef _Geo_BasicApprxCurve_Info_Header
#define _Geo_BasicApprxCurve_Info_Header

#include <Geo_Module.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	class Geo_BasicApprxCurve_Info
	{

		/*Private Data*/

		Standard_Real theApprox_;
		Standard_Real theMinSize_;

		Standard_Integer theMaxNbSubdivision_;
		Standard_Integer theInitNbSubdivision_;
		Standard_Integer theNbSamples_;


		// private functions and operators [8/25/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theApprox_;
			ar & theMinSize_;
			ar & theMaxNbSubdivision_;
			ar & theInitNbSubdivision_;
			ar & theNbSamples_;
		}

	public:

		static TnbGeo_EXPORT const Standard_Real DEFAULT_APPROX;
		static TnbGeo_EXPORT const Standard_Real DEFAULT_MIN_SIZE;

		static TnbGeo_EXPORT const Standard_Integer DEFAULT_MAX_NB_SUBDIVIDE;
		static TnbGeo_EXPORT const Standard_Integer DEFAULT_INIT_NB_SUBDIVIDE;
		static TnbGeo_EXPORT const Standard_Integer DEFAULT_NB_SAMPLES;

		// default constructor [8/25/2022 Amir]

		Geo_BasicApprxCurve_Info()
			: theApprox_(DEFAULT_APPROX)
			, theMaxNbSubdivision_(DEFAULT_MAX_NB_SUBDIVIDE)
			, theInitNbSubdivision_(DEFAULT_INIT_NB_SUBDIVIDE)
			, theNbSamples_(DEFAULT_NB_SAMPLES)
			, theMinSize_(DEFAULT_MIN_SIZE)
		{}


		// constructors [8/25/2022 Amir]


		// public functions and operators [8/25/2022 Amir]


		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Approx)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, MinSize)

			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Integer, MaxNbSubdivision)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Integer, InitNbSubdivision)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Integer, NbSamples)
	};
}

#endif // !_Geo_BasicApprxCurve_Info_Header
