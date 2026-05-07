#pragma once
#ifndef _PtdModel_PropHubPars_Header
#define _PtdModel_PropHubPars_Header

#include <Global_Serialization.hxx>

namespace tnbLib
{

	class PtdModel_PropHubPars
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			//- empty body
		}

	protected:

		//- default constructor

		PtdModel_PropHubPars()
		{}

	public:


		virtual ~PtdModel_PropHubPars()
		{}

		//- public functions and operators


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_PropHubPars);

#endif // !_PtdModel_PropHubPars_Header
