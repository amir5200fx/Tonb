#pragma once
#ifndef _StbGMaker_TankCreator_Header
#define _StbGMaker_TankCreator_Header

#include <StbGMaker_Alg.hxx>
#include <StbGMaker_EntityCreator.hxx>
#include <Marine_ShapesFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;

	class StbGMaker_TankCreator
		: public StbGMaker_Alg
		, public StbGMaker_EntityCreator
	{

		/*Private Data*/


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<StbGMaker_EntityCreator>(*this);
			ar & boost::serialization::base_object<StbGMaker_Alg>(*this);
		}

	protected:

		template<class... _Types>
		StbGMaker_TankCreator(_Types&&... _Args)
			: StbGMaker_EntityCreator(_Args...)
		{}

	public:


		virtual Standard_Boolean HasShape() const = 0;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::StbGMaker_TankCreator);

#endif // !_StbGMaker_TankCreator_Header
