#pragma once
#ifndef _Geo_ElemConn_Header
#define _Geo_ElemConn_Header

#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>

#include <array>
#include <vector>
#include <string>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class Geo_ElemConn
	{

		/*Private Data*/


		// Private functions and operators [8/14/2023 aamir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			// empty body [8/14/2023 aamir]
		}

	protected:

		// default constructor [8/14/2023 aamir]

		Geo_ElemConn()
		{}

	public:

		// Public functions and operators [8/14/2023 aamir]

		virtual std::string ElementType() const = 0;
		virtual Standard_Integer Size() const = 0;
		virtual std::vector<Standard_Integer> IndexList() const = 0;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Geo_ElemConn);

#endif // !_Geo_ElemConn_Header
