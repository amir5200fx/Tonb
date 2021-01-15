#pragma once
#ifndef _Marine_GraphTitle_Header
#define _Marine_GraphTitle_Header

#include <Marine_GraphEntity.hxx>

namespace tnbLib
{

	class Marine_GraphTitle
		: public Marine_GraphEntity
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Marine_GraphEntity>(*this);
		}

	public:


		//- default constructor

		Marine_GraphTitle()
		{}


		//- constructor

		TnbMarine_EXPORT explicit Marine_GraphTitle(const word& theName);
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_GraphTitle);

#endif // !_Marine_GraphTitle_Header
