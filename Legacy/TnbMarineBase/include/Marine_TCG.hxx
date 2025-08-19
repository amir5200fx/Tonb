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

		TnbMarine_EXPORT Marine_TCG(const Standard_Real theValue = 0);

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_TCG);

#endif // !_Marine_TCG_Header
