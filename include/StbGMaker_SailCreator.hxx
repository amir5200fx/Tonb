#pragma once
#ifndef _StbGMaker_SailCreator_Header
#define _StbGMaker_SailCreator_Header

//#include <StbGMaker_Alg.hxx>
#include <StbGMaker_EntityCreator.hxx>
#include <StbGMaker_SailCreatorType.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;

	class StbGMaker_SailCreator
		: public StbGMaker_EntityCreator
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<StbGMaker_EntityCreator>(*this);
		}

	protected:

		template<class... _Types>
		StbGMaker_SailCreator(_Types&&... _Args)
			: StbGMaker_EntityCreator(_Args...)
		{}

	public:

		virtual Standard_Boolean IsArea() const;

		virtual Standard_Boolean IsGeometric() const;

		virtual stbGmakerLib::sailCreatotType Type() const = 0;
	};
}

#endif // !_StbGMaker_SailCreator_Header
