#pragma once
#ifndef _Marine_CGCompt_Header
#define _Marine_CGCompt_Header

#include <Marine_Entity.hxx>
#include <Global_AccessMethod.hxx>

namespace tnbLib
{

	class Marine_CGCompt
		: public Marine_Entity
	{

		/*Private Data*/

		Standard_Real theValue_;


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Marine_Entity>(*this);
			ar & theValue_;
		}

	protected:

		TnbMarine_EXPORT Marine_CGCompt
		(
			const Standard_Real theValue = 0
		);

		TnbMarine_EXPORT Marine_CGCompt
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const Standard_Real theValue
		);

	public:

		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Value)
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Marine_CGCompt);

#endif // !_Marine_CGCompt_Header
