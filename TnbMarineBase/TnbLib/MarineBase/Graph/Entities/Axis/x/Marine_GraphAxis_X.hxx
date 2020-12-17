#pragma once
#ifndef _Marine_GraphAxis_X_Header
#define _Marine_GraphAxis_X_Header

#include <Marine_GraphAxis.hxx>

namespace tnbLib
{

	class Marine_GraphAxis_X
		: public Marine_GraphAxis
	{

		/*private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Marine_GraphAxis>(*this);
		}

	public:

		Marine_GraphAxis_X()
		{}

		TnbMarine_EXPORT explicit Marine_GraphAxis_X
		(
			const Standard_Integer theIndex
		);

		TnbMarine_EXPORT Marine_GraphAxis_X
		(
			const Standard_Integer theIndex,
			const word& theName
		);


		Standard_Boolean IsX() const override
		{
			return Standard_True;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_GraphAxis_X);

#endif // !_Marine_GraphAxis_X_Header
