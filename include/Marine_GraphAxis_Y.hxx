#pragma once
#ifndef _Marine_GraphAxis_Y_Header
#define _Marine_GraphAxis_Y_Header

#include <Marine_GraphAxis.hxx>

namespace tnbLib
{

	class Marine_GraphAxis_Y
		: public Marine_GraphAxis
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Marine_GraphAxis>(*this);
		}

	public:

		//- default constructor

		Marine_GraphAxis_Y()
		{}


		//- constructors

		TnbMarine_EXPORT explicit Marine_GraphAxis_Y
		(
			const Standard_Integer theIndex
		);

		TnbMarine_EXPORT Marine_GraphAxis_Y
		(
			const Standard_Integer theIndex, 
			const word& theName
		);


		Standard_Boolean IsY() const override
		{
			return Standard_True;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_GraphAxis_Y);

#endif // !_Marine_GraphAxis_Y_Header
