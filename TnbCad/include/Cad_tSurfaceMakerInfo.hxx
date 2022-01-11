#pragma once
#ifndef _Cad_tSurfaceMakerInfo_Header
#define _Cad_tSurfaceMakerInfo_Header

#include <Standard_TypeDef.hxx>

#include <Global_Serialization.hxx>
#include <Cad_Module.hxx>

namespace tnbLib
{

	class Cad_tSurfaceMakerInfo
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			// empty body [1/7/2022 Amir]
		}

	protected:

		// default constructor [1/7/2022 Amir]

		Cad_tSurfaceMakerInfo()
		{}

		// constructors [1/7/2022 Amir]

	public:

		virtual ~Cad_tSurfaceMakerInfo()
		{}

		// public functions and operators [1/7/2022 Amir]

		virtual Standard_Real Precision() const = 0;
		virtual Standard_Real MinTolerance() const = 0;
		virtual Standard_Real MaxTolerance() const = 0;
		virtual Standard_Real Tolerance() const = 0;

	}; 
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Cad_tSurfaceMakerInfo);

#endif // !_Cad_tSurfaceMakerInfo_Header
