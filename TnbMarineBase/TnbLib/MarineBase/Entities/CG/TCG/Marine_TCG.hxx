#pragma once
#ifndef _Marine_TCG_Header
#define _Marine_TCG_Header

#include <Marine_CGCompt.hxx>

namespace tnbLib
{

	class Marine_TCG
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

		Marine_TCG(const Standard_Real theValue = 0);

	};
}

#endif // !_Marine_TCG_Header
