#pragma once
#ifndef _GeoTop2d_EdgeAdaptor_Header
#define _GeoTop2d_EdgeAdaptor_Header

#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [2/18/2023 Payvand]

	class GeoTop2d_Element;

	class GeoTop2d_EdgeAdaptor
	{

		/*Private Data*/

		std::weak_ptr<GeoTop2d_Element> theLeft_;
		std::weak_ptr<GeoTop2d_Element> theRight_;

		// Private functions and operators [2/18/2023 Payvand]

		TNB_SERIALIZATION(TnbGeo_EXPORT);


	protected:

		// default constructor [2/18/2023 Payvand]

		GeoTop2d_EdgeAdaptor()
		{}

		// constructors [2/18/2023 Payvand]


	public:

		// Public functions and operators [2/18/2023 Payvand]

		TnbGeo_EXPORT Standard_Boolean IsOnBoundary() const;

		TnbGeo_EXPORT std::shared_ptr<GeoTop2d_Element> LeftElement() const;
		TnbGeo_EXPORT std::shared_ptr<GeoTop2d_Element> RightElement() const;

		void SetLeftElement(const std::shared_ptr<GeoTop2d_Element>& theElement)
		{
			theLeft_ = theElement;
		}

		void SetRightElement(const std::shared_ptr<GeoTop2d_Element>& theElement)
		{
			theRight_ = theElement;
		}
		
	};
}

#endif // !_GeoTop2d_EdgeAdaptor_Header
