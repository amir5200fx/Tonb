#pragma once
#ifndef _StbGMaker_VolumeSailCreator_Header
#define _StbGMaker_VolumeSailCreator_Header

#include <StbGMaker_GeometricSailCreator.hxx>
#include <StbGMaker_Alg.hxx>

namespace tnbLib
{

	class StbGMaker_VolumeSailCreator
		: public StbGMaker_GeometricSailCreator
		, public StbGMaker_Alg
	{

		/*Private Data*/


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<StbGMaker_GeometricSailCreator>(*this);
		}


		TnbStbGMaker_EXPORT std::shared_ptr<StbGMaker_WP> 
			MakeWP
			(
				const Standard_Real x
			) const override;

	protected:

		template<class... _Types>
		StbGMaker_VolumeSailCreator(_Types&&... _Args)
			: StbGMaker_GeometricSailCreator(_Args...)
		{}

	public:


		//- public functions and operators


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::StbGMaker_VolumeSailCreator);

#endif // !_StbGMaker_VolumeSailCreator_Header
