#pragma once
#ifndef _Geo_ElemConn_Dual_Header
#define _Geo_ElemConn_Dual_Header

#include <Geo_ELemConn.hxx>

namespace tnbLib
{

	class Geo_ElemConn_Dual
		: public Geo_ElemConn
	{

	public:

		enum
		{
			nbNodes = 2
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

		Geo_ElemConn_Dual()
		{}

	public:

		static TnbGeo_EXPORT const char* typeName_;
		

		// default constructor [8/14/2023 aamir]

		// constructors [8/14/2023 aamir]

		Geo_ElemConn_Dual(const std::array<Standard_Integer, 2>& theIndices)
			: theIndices_(theIndices)
		{}

		Geo_ElemConn_Dual(std::array<Standard_Integer, 2>&& theIndices)
			: theIndices_(std::move(theIndices))
		{}


		// Public functions and operators [8/14/2023 aamir]

		std::string ElementType() const override { return typeName_; }
		Standard_Integer Size() const override { return (Standard_Integer)nbNodes; }
		TnbGeo_EXPORT std::vector<Standard_Integer> IndexList() const override;

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo_ElemConn_Dual);

#endif // !_Geo_ElemConn_Dual_Header
