#pragma once
#ifndef _StbGMaker_GeometricSailCreator_Header
#define _StbGMaker_GeometricSailCreator_Header

#include <StbGMaker_SailCreator.hxx>

namespace tnbLib
{

	class StbGMaker_GeometricSailCreator
		: public StbGMaker_SailCreator
	{

		/*Private Data*/


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<StbGMaker_SailCreator>(*this);
		}

	protected:

		template<class... _Types>
		StbGMaker_GeometricSailCreator(_Types&&... _Args)
			: StbGMaker_SailCreator(_Args...)
		{}

	public:

		TnbStbGMaker_EXPORT Standard_Boolean IsGeometric() const override;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::StbGMaker_GeometricSailCreator);

#endif // !_StbGMaker_GeometricSailCreator_Header
