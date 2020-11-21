#pragma once
#ifndef _Marine_LCG_Header
#define _Marine_LCG_Header

#include <Marine_CGCompt.hxx>

namespace tnbLib
{

	class Marine_LCG
		: public Marine_CGCompt
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Marine_CGCompt>(*this);
		}

	public:

		TnbMarine_EXPORT Marine_LCG(const Standard_Real theValue = 0);


	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_LCG);

#endif // !_Marine_LCG_Header
