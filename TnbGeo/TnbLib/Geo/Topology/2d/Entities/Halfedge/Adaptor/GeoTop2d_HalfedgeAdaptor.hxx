#pragma once
#ifndef _GeoTop2d_HalfedgeAdaptor_Header
#define _GeoTop2d_HalfedgeAdaptor_Header

#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [2/17/2023 Payvand]

	class GeoTop2d_Element;

	class GeoTop2d_HalfedgeAdaptor
	{

		/*Private Data*/

		std::weak_ptr<GeoTop2d_Element> theElement_;


		// Private functions and operators [2/17/2023 Payvand]

		TNB_SERIALIZATION(TnbGeo_EXPORT);


	protected:

		// default constructor [2/17/2023 Payvand]

		GeoTop2d_HalfedgeAdaptor()
		{}


		// constructors [2/17/2023 Payvand]

	public:

		// Public functions and operators [2/17/2023 Payvand]

		const auto& Element() const
		{
			return theElement_;
		}

		void SetElement(const std::shared_ptr<GeoTop2d_Element>& theElement)
		{
			theElement_ = theElement;
		}


	};

}

#endif // !_GeoTop2d_HalfedgeAdaptor_Header
