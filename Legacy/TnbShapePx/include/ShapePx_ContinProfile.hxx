#pragma once
#ifndef _ShapePx_ContinProfile_Header
#define _ShapePx_ContinProfile_Header

#include <ShapePx_Profile.hxx>

namespace tnbLib
{

	class ShapePx_ContinProfile
		: public ShapePx_Profile
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<ShapePx_Profile>(*this);
		}

	protected:

		template<class... _Types>
		ShapePx_ContinProfile(_Types&&... _Args)
			: ShapePx_Profile(_Args...)
		{}

		TnbShapePx_EXPORT void CheckBoundary(const Standard_Real x, const char* funcName) const;

	public:

		virtual Standard_Real Value(const Standard_Real x) const = 0;

		Standard_Real LowerValue() const override
		{
			return Value(Lower());
		}

		Standard_Real UpperValue() const override
		{
			return Value(Upper());
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::ShapePx_ContinProfile);

#endif // !_ShapePx_ContinProfile_Header
