#pragma once
#ifndef _Geo_xDistb_Header
#define _Geo_xDistb_Header

#include <Global_Done.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Bound.hxx>
#include <Geo_Module.hxx>

#include <vector>

namespace tnbLib
{

	class Geo_xDistb
		: public Global_Done
		, public Global_Bound<Standard_Real>
	{

		/*Private Data*/

		std::vector<Standard_Real> theValues_;


		//- Private function and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Global_Done>(*this);
			ar & boost::serialization::base_object<Global_Bound<Standard_Real>>(*this);

			ar & theValues_;
		}

	protected:

		// default constructor
		Geo_xDistb() = default;

		// constructors
		Geo_xDistb(const Standard_Real lower, const Standard_Real upper)
			: Global_Bound(lower, upper)
		{}

		// Protected functions and operators
		auto& ChangeValues()
		{
			return theValues_;
		}
	public:

		// Public function and operators

		[[nodiscard]] auto Size() const
		{
			return static_cast<Standard_Integer>(theValues_.size());
		}

		[[nodiscard]] const auto& Values() const
		{
			return theValues_;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo_xDistb);

#endif // !_Geo_xDistb_Header
