#pragma once
#ifndef _PtdModel_UniformProfile_Header
#define _PtdModel_UniformProfile_Header

#include <PtdModel_Profile.hxx>

namespace tnbLib
{

	class PtdModel_UniformProfile
		: public PtdModel_Profile
	{

		/*Private Data*/

		std::shared_ptr<PtdModel_Par> theValue_;

	public:

		//- default constructor

		PtdModel_UniformProfile()
			: theValue_(0)
		{}

		//- constructors

		PtdModel_UniformProfile(const std::shared_ptr<PtdModel_Par>& x);

		PtdModel_UniformProfile(const Standard_Integer theIndex, const word& theName, const std::shared_ptr<PtdModel_Par>& x);


		//- public functions and operators

		Standard_Integer NbParameters() const override;

		std::map<word, std::shared_ptr<PtdModel_Par>> Parameters() const override;
	};
}

#endif // !_PtdModel_UniformProfile_Header
