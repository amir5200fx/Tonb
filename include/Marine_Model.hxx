#pragma once
#ifndef _Marine_Model_Header
#define _Marine_Model_Header

#include <Marine_CoordinatedEntity.hxx>
#include <Marine_ModelType.hxx>

namespace tnbLib
{

	class Marine_Model
		: public Marine_CoordinatedEntity
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
		}

	protected:

		template<class... _Types>
		Marine_Model(_Types&&... _Args)
			: Marine_CoordinatedEntity(_Args...)
		{}

	public:


		virtual Marine_ModelType Type() const = 0;

		virtual Standard_Boolean IsHull() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsSail() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsTank() const
		{
			return Standard_False;
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Marine_Model);

#endif // !_Marine_Model_Header
