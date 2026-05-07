#pragma once
#ifndef _PtdModel_GlobalPars_Header
#define _PtdModel_GlobalPars_Header

#include <Global_Serialization.hxx>
#include <PtdModel_Module.hxx>

#include <memory>

namespace tnbLib
{

	class PtdModel_GlobalPars
		: public std::enable_shared_from_this<PtdModel_GlobalPars>
	{

		/*Private Data*/


		//- private functions and operators


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive&, const unsigned int /*file_version*/)
		{
			// empty body [6/9/2021 Ami]
		}

	protected:

		//- default constructor
		
		PtdModel_GlobalPars()
		{}


		//- constructors


	public:

		virtual ~PtdModel_GlobalPars()
		{}

		//- public functions and operators

		auto This() const
		{
			return std::const_pointer_cast<PtdModel_GlobalPars>(this->weak_from_this().lock());
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_GlobalPars);

#endif // !_PtdModel_GlobalPars_Header
