#pragma once
#ifndef _Geo_ElemGeom_Triangle_Header
#define _Geo_ElemGeom_Triangle_Header

#include <Geo_ElemGeom.hxx>

namespace tnbLib
{

	class Geo_ElemGeom_Triangle
		: public Geo_ElemGeom
	{

	public:

		enum 
		{
			nbNodes = 3
		};

	private:

		/*Private Data*/

		std::array<Standard_Integer, nbNodes> theIndices_;

		// Private functions and operators [8/15/2023 aamir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Geo_ElemGeom>(*this);
			ar& theIndices_;
		}

		// default constructor [8/15/2023 aamir]

		Geo_ElemGeom_Triangle()
		{}

	public:

		static TnbGeo_EXPORT const char* typeName_;

		// constructors [8/15/2023 aamir]

		Geo_ElemGeom_Triangle(const std::array<Standard_Integer, nbNodes>& theIndices)
			: theIndices_(theIndices)
		{}

		Geo_ElemGeom_Triangle(std::array<Standard_Integer, nbNodes>&& theIndices)
			: theIndices_(std::move(theIndices))
		{}

		// Public functions and operators [8/15/2023 aamir]

		std::string ElementType() const override { return typeName_; }
		Standard_Integer Size() const override { return (Standard_Integer)nbNodes; }
		TnbGeo_EXPORT std::vector<Standard_Integer> IndexList() const override;

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo_ElemGeom_Triangle);

#endif // !_Geo_ElemGeom_Triangle_Header
