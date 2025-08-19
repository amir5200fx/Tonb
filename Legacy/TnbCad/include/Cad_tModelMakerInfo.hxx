#pragma once
#ifndef _Cad_tModelMakerInfo_Header
#define _Cad_tModelMakerInfo_Header

#include <Cad_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	class Cad_tModelMakerInfo
	{

		/*Private Data*/


		// private functions and operators [1/7/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			// empty body [1/7/2022 Amir]
		}

	protected:

		// default constructor [1/7/2022 Amir]

		Cad_tModelMakerInfo()
		{}

		// constructors [1/7/2022 Amir]


	public:

		virtual ~Cad_tModelMakerInfo()
		{}

		// public functions and operators [1/7/2022 Amir]

		virtual Standard_Real Radius() const = 0;
		virtual Standard_Real Tolerance() const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Cad_tModelMakerInfo);

#endif // !_Cad_tModelMakerInfo_Header
