#pragma once
#ifndef _Cad_tEdgeMakerInfo_Header
#define _Cad_tEdgeMakerInfo_Header

#include <Standard_TypeDef.hxx>

#include <Global_Serialization.hxx>
#include <Cad_Module.hxx>

namespace tnbLib
{

	class Cad_tEdgeMakerInfo
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

		// default constructor [1/6/2022 Amir]

		Cad_tEdgeMakerInfo()
		{}

		// constructors [1/6/2022 Amir]

	public:

		virtual ~Cad_tEdgeMakerInfo()
		{}

		// public functions and operators [1/6/2022 Amir]

		virtual Standard_Real Tolerance() const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Cad_tEdgeMakerInfo);

#endif // !_Cad_tEdgeMakerInfo_Header
