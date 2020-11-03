#pragma once
#ifndef _Marine_VCG_Header
#define _Marine_VCG_Header

#include <Marine_CGCompt.hxx>

namespace tnbLib
{

	class Marine_VCG
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

		Marine_VCG(const Standard_Real theValue = 0);


	};
}

#endif // !_Marine_VCG_Header
