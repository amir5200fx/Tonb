#pragma once
#ifndef _HydStatic_SailShape_Header
#define _HydStatic_SailShape_Header

#include <HydStatic_Shape.hxx>

namespace tnbLib
{

	class HydStatic_SailShape
		: public HydStatic_Shape
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			boost::serialization::base_object<HydStatic_Shape>(*this);
		}

	public:

		HydStatic_SailShape()
		{}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_SailShape);

#endif // !_HydStatic_SailShape_Header
