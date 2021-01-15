#pragma once
#ifndef _Marine_GraphAxis_Header
#define _Marine_GraphAxis_Header

#include <Marine_GraphEntity.hxx>
#include <Global_Bound.hxx>

namespace tnbLib
{

	class Marine_GraphAxis
		: public Marine_GraphEntity
		, public Global_Bound<Standard_Real>
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Marine_GraphEntity>(*this);
			ar & boost::serialization::base_object<Global_Bound<Standard_Real>>(*this);
		}

	protected:

		template<class... _Types>
		Marine_GraphAxis(_Types&&... _Args)
			: Marine_GraphEntity(_Args...)
		{}

	public:

		virtual Standard_Boolean IsX() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsY() const
		{
			return Standard_False;
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Marine_GraphAxis);

#endif // !_Marine_GraphAxis_Header
