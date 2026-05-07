#pragma once
#ifndef _Geo_ELemConn_Triple_Header
#define _Geo_ELemConn_Triple_Header

#include <Geo_ELemConn.hxx>

namespace tnbLib
{

	class Geo_ElemConn_Triple
		: public Geo_ElemConn
	{

	public:

		enum
		{
			nbNodes = 3
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

		Geo_ElemConn_Triple()
		{}

	public:

		static TnbGeo_EXPORT const char* typeName_;


		// default constructor [8/14/2023 aamir]

		// constructors [8/14/2023 aamir]

		Geo_ElemConn_Triple(const std::array<Standard_Integer, nbNodes>& theIndices)
			: theIndices_(theIndices)
		{}

		Geo_ElemConn_Triple(std::array<Standard_Integer, nbNodes>&& theIndices)
			: theIndices_(std::move(theIndices))
		{}


		// Public functions and operators [8/14/2023 aamir]

		std::string ElementType() const override { return typeName_; }
		Standard_Integer Size() const override { return (Standard_Integer)nbNodes; }
		TnbGeo_EXPORT std::vector<Standard_Integer> IndexList() const override;

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo_ElemConn_Triple);

#endif // !_Geo_ELemConn_Triple_Header
