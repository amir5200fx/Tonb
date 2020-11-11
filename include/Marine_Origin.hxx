#pragma once
#ifndef _Marine_Origin_Header
#define _Marine_Origin_Header

#include <Marine_CoordinatedEntity.hxx>

namespace tnbLib
{

	class Marine_Origin
		: public Marine_CoordinatedEntity
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
		}

	public:

		static const gp_Ax2& SystemOrigin();

		Marine_Origin();

		Marine_Origin(const gp_Ax2& theOrigin);

	};
}

#endif // !_Marine_Origin_Header
