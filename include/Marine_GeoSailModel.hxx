#pragma once
#ifndef _Marine_GeoSailModel_Header
#define _Marine_GeoSailModel_Header

#include <Marine_SailModel.hxx>

namespace tnbLib
{

	class Marine_GeoSailModel
		: public Marine_SailModel
	{

		/*Private Data*/


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Marine_SailModel>(*this);
		}

	protected:

		template<class... _Types>
		Marine_GeoSailModel(_Types&&... _Args)
			: Marine_SailModel(_Args...)
		{}

	public:

		Standard_Boolean HasGeometry() const override
		{
			return Standard_True;
		}

		virtual Standard_Boolean IsPlanar() const
		{
			return Standard_False;
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Marine_GeoSailModel);

#endif // !_Marine_GeoSailModel_Header
