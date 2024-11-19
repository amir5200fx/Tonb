#pragma once
#ifndef _Geo2d_NurbsPx_Header
#define _Geo2d_NurbsPx_Header

#include <Vec2d.hxx>
#include <Pnt2d.hxx>
#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [8/15/2023 aamir]
	class Geo_ProfileFun;

	class Geo2d_NurbsPx
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Geo_ProfileFun> theProfile_;

		// Private functions and operators [8/15/2023 aamir]

		TNB_SERIALIZATION(TnbGeo_EXPORT);

	protected:

		// default constructor [8/15/2023 aamir]

		Geo2d_NurbsPx()
		{}

		// constructors [8/15/2023 aamir]


		// Protected functions and operators [8/15/2023 aamir]

		void SetProfile(std::shared_ptr<Geo_ProfileFun>&& theProfile) { theProfile_ = std::move(theProfile); }

	public:

		// Public functions and operators [8/15/2023 aamir]

		const auto& Profile() const { return theProfile_; }

		virtual Standard_Real Value(const Standard_Real x) const = 0;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Geo2d_NurbsPx);

#endif // !_Geo2d_NurbsPx_Header
