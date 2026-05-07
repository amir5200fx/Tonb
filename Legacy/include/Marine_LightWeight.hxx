#pragma once
#ifndef _Marine_LightWeight_Header
#define _Marine_LightWeight_Header

#include <Marine_Load.hxx>

namespace tnbLib
{

	class Marine_LightWeight
		: public Marine_Load
	{

		/*Private Data*/


		//- private functions and operators

		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Marine_Load>(*this);
		}

	public:

		Marine_LightWeight()
		{}

		Marine_LoadType Type() const override
		{
			return Marine_LoadType::lightWeight;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_LightWeight);

#endif // !_Marine_LightWeight_Header
