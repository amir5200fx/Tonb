#pragma once
#ifndef _SectPx_FieldFun_readX_Header
#define _SectPx_FieldFun_readX_Header

#include <SectPx_nonParFieldFun.hxx>
#include <SectPx_Coord.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Coord;


	namespace sectPxLib
	{

		class FieldFun_readX
			: public SectPx_nonParFieldFun
		{

			/*Private Data*/

			std::shared_ptr<SectPx_Coord> theCoord_;


			friend boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_nonParFieldFun>(*this);
				ar & theCoord_;
			}

		protected:

			FieldFun_readX()
			{}

		public:

			static const char* typeName_;

			FieldFun_readX
			(
				const std::shared_ptr<SectPx_Coord>& theCoord
			);

			FieldFun_readX
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<SectPx_Coord>& theCoord
			);

			FieldFun_readX
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<SectPx_Coord>& theCoord
			);


			const auto& Coord() const
			{
				return theCoord_;
			}

			word RegObjTypeName() const override;

			Standard_Real Value() const override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::FieldFun_readX);

#endif // !_SectPx_FieldFun_readX_Header
