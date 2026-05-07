#pragma once
#ifndef _StbGMaker_AreaSailCreator_Header
#define _StbGMaker_AreaSailCreator_Header

#include <StbGMaker_SailCreator.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	class StbGMaker_AreaSailCreator
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
		StbGMaker_AreaSailCreator(_Types&&... _Args)
			: StbGMaker_SailCreator(_Args...)
		{}

	public:

		TnbStbGMaker_EXPORT Standard_Boolean IsArea() const override;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::StbGMaker_AreaSailCreator);

#endif // !_StbGMaker_AreaSailCreator_Header

