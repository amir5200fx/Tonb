#pragma once
#ifndef _Geo_ElemConn_Sextuple_Header
#define _Geo_ElemConn_Sextuple_Header

#include <Geo_ElemConn.hxx>

namespace tnbLib
{

	class Geo_ElemConn_Sextuple
		: public Geo_ElemConn
	{

	public:

		enum 
		{
			nbNodes = 6
		};

	private:

		/*Private Data*/

		std::array<Standard_Integer, nbNodes> theIndices_;

		// Private functions and operators [8/14/2023 aamir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Geo_ElemConn>(*this);
			ar& theIndices_;
		}

		Geo_ElemConn_Sextuple()
		{}

	public:

		static TnbGeo_EXPORT const char* typeName_;

		// default constructor [8/14/2023 aamir]


		// constructors [8/14/2023 aamir]

		Geo_ElemConn_Sextuple(const std::array<Standard_Integer, nbNodes>& theIndices)
			: theIndices_(theIndices)
		{}

		Geo_ElemConn_Sextuple(std::array<Standard_Integer, nbNodes>&& theIndices)
			: theIndices_(std::move(theIndices))
		{}


		// Public functions and operators [8/14/2023 aamir]

		std::string ElementType() const override { return typeName_; }
		Standard_Integer Size() const override { return (Standard_Integer)nbNodes; }
		TnbGeo_EXPORT std::vector<Standard_Integer> IndexList() const override;

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo_ElemConn_Sextuple);

#endif // !_Geo_ElemConn_Sextuple_Header

