#pragma once
#ifndef _Merge_PntInfo_Header
#define _Merge_PntInfo_Header

#include <Standard_TypeDef.hxx>

#include <Global_Serialization.hxx>
#include <Geo_Module.hxx>

namespace tnbLib
{

	class Merge_PntInfo
	{

		/*Private Data*/

		Standard_Real theResolution_;
		Standard_Real theRadius_;


		// private functions and operators [12/30/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theResolution_;
			ar & theRadius_;
		}

	public:

		static TnbGeo_EXPORT const Standard_Real DEFAULT_RESOLUTION;
		static TnbGeo_EXPORT const Standard_Real DEFAULT_RADIUS;

		// default constructor [12/30/2021 Amir]

		Merge_PntInfo()
			: theResolution_(DEFAULT_RESOLUTION)
			, theRadius_(DEFAULT_RADIUS)
		{}

		// constructors [12/30/2021 Amir]

		Merge_PntInfo(const Standard_Real theResolution, const Standard_Real theRadius)
			: theResolution_(theResolution)
			, theRadius_(theRadius)
		{}


		// public functions and operators [12/30/2021 Amir]

		auto Resolution() const
		{
			return theResolution_;
		}

		auto Radius() const
		{
			return theRadius_;
		}

		void SetResolution(const Standard_Real theResolution)
		{
			theResolution_ = theResolution;
		}

		void SetRadius(const Standard_Real theRadius)
		{
			theRadius_ = theRadius;
		}

	};
}

#endif // !_Merge_PntInfo_Header
