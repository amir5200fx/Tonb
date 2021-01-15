#pragma once
#ifndef _StbGMaker_TankWP_Header
#define _StbGMaker_TankWP_Header

#include <StbGMaker_WP.hxx>

namespace tnbLib
{

	class StbGMaker_TankWP
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

		TnbStbGMaker_EXPORT StbGMaker_TankWP();


		//- constructors

		TnbStbGMaker_EXPORT explicit StbGMaker_TankWP(const Standard_Real theX);

		TnbStbGMaker_EXPORT StbGMaker_TankWP
		(
			const Standard_Integer theIndex,
			const Standard_Real theX
		);

		TnbStbGMaker_EXPORT StbGMaker_TankWP
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Standard_Real theX
		);

		//- public functions and operators

		Standard_Boolean IsTank() const override
		{
			return Standard_True;
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::StbGMaker_TankWP);

#endif // !_StbGMaker_TankWP_Header
