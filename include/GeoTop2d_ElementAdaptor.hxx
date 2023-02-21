#pragma once
#ifndef _GeoTop2d_ElementAdaptor_Header
#define _GeoTop2d_ElementAdaptor_Header

#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [2/18/2023 Payvand]
	class GeoTop2d_Element;

	class GeoTop2d_ElementAdaptor
	{

		/*Private Data*/

		std::array<std::weak_ptr<GeoTop2d_Element>, 3> theNeighbors_;


		// Private functions and operators [2/18/2023 Payvand]

		TNB_SERIALIZATION(TnbGeo_EXPORT);

	protected:

		// default constructor [2/18/2023 Payvand]

		GeoTop2d_ElementAdaptor()
		{}


		// constructors [2/18/2023 Payvand]


	public:

		// Public functions and operators [2/18/2023 Payvand]

		const auto& Neighbors() const
		{
			return theNeighbors_;
		}

		TnbGeo_EXPORT std::shared_ptr<GeoTop2d_Element> Neighbor0() const;
		TnbGeo_EXPORT std::shared_ptr<GeoTop2d_Element> Neighbor1() const;
		TnbGeo_EXPORT std::shared_ptr<GeoTop2d_Element> Neighbor2() const;

		TnbGeo_EXPORT void SetNeighbor0(const std::shared_ptr<GeoTop2d_Element>& theElement);
		TnbGeo_EXPORT void SetNeighbor1(const std::shared_ptr<GeoTop2d_Element>& theElement);
		TnbGeo_EXPORT void SetNeighbor2(const std::shared_ptr<GeoTop2d_Element>& theElement);

	};
}

#endif // !_GeoTop2d_ElementAdaptor_Header
