#pragma once
#ifndef _Marine_CoordinatedEntity_Header
#define _Marine_CoordinatedEntity_Header

#include <Marine_Entity.hxx>
#include <Global_AccessMethod.hxx>
#include <Geo_Serialization.hxx>

#include <gp_Ax2.hxx>

namespace tnbLib
{

	class Marine_CoordinatedEntity
		: public Marine_Entity
	{

		/*Private Data*/

		gp_Ax2 theCoordinateSystem_;


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Marine_Entity>(*this);
			ar & theCoordinateSystem_;
		}

	protected:

		template<class... _Types>
		Marine_CoordinatedEntity(_Types&&... _Args)
			: Marine_Entity(_Args...)
		{}

	public:

		void SetLocation(const gp_Pnt& thePnt)
		{
			theCoordinateSystem_.SetLocation(thePnt);
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(gp_Ax2, CoordinateSystem)
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Marine_CoordinatedEntity);

#endif // !_Marine_CoordinatedEntity_Header
