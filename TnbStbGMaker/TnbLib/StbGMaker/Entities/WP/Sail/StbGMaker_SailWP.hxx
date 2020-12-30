#pragma once
#ifndef _StbGMaker_SailWP_Header
#define _StbGMaker_SailWP_Header

#include <StbGMaker_WP.hxx>

namespace tnbLib
{

	class StbGMaker_SailWP
		: public StbGMaker_WP
	{

		/*Private Data*/

		void MakeModeler();


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<StbGMaker_WP>(*this);
		}

	public:

		//- default constructor

		TnbStbGMaker_EXPORT StbGMaker_SailWP();


		//- constructors

		TnbStbGMaker_EXPORT explicit StbGMaker_SailWP(const Standard_Real theX);

		TnbStbGMaker_EXPORT StbGMaker_SailWP
		(
			const Standard_Integer theIndex,
			const Standard_Real theX
		);

		TnbStbGMaker_EXPORT StbGMaker_SailWP
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Standard_Real theX
		);

		//- public functions and operators

		Standard_Boolean IsSail() const override
		{
			return Standard_True;
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::StbGMaker_SailWP);

#endif // !_StbGMaker_SailWP_Header
