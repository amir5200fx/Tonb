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

		Marine_LCG(const Standard_Real theValue = 0);


	};
}

#endif // !_Marine_LCG_Header
