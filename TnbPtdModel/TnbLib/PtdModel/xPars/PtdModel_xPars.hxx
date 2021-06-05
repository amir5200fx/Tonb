#pragma once
#ifndef _PtdModel_xPars_Header
#define _PtdModel_xPars_Header

#include <Standard_TypeDef.hxx>
#include <word.hxx>
#include <Global_Serialization.hxx>
#include <PtdModel_Module.hxx>

#include <vector>
#include <map>

namespace tnbLib
{

	class PtdModel_xPars
	{

	public:

		typedef std::vector<Standard_Real> realList;

	private:

		/*Private Data*/

		realList theX_;

		std::map<word, std::shared_ptr<realList>> theParameters_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:

		//- default constructor

		PtdModel_xPars()
		{}

		//- constructor


		//- public functions and operators

		inline Standard_Integer NbParameters() const;
		inline Standard_Integer NbSections() const;

		const auto& Xs() const
		{
			return theX_;
		}

		const auto& Parameters() const
		{
			return theParameters_;
		}

		inline std::shared_ptr<realList> SelectParameter(const word&) const;

		inline void SetXs(realList&& xs);
		inline void SetParameter(const word& theName, std::shared_ptr<realList>&&);


	};
}

#include <PtdModel_xParsI.hxx>

#endif // !_PtdModel_xPars_Header
