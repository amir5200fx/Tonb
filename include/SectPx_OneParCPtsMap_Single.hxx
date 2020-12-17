#pragma once
#ifndef _SectPx_OneParCPtsMap_Single_Header
#define _SectPx_OneParCPtsMap_Single_Header

#include <SectPx_OneParCPtsMap.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		class OneParCPtsMap_Single
			: public SectPx_OneParCPtsMap
		{

			/*Private Data*/


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_OneParCPtsMap>(*this);
			}

		public:

			static TnbSectPx_EXPORT const char* typeName_;

			
			//- default constructor

			OneParCPtsMap_Single()
			{}


			//- constructors

			TnbSectPx_EXPORT OneParCPtsMap_Single
			(
				const Standard_Integer theIndex
			);

			TnbSectPx_EXPORT OneParCPtsMap_Single
			(
				const Standard_Integer theIndex,
				const word& theName
			);


			//- public functions and operators

			TnbSectPx_EXPORT word RegObjTypeName() const override;

			TnbSectPx_EXPORT Standard_Integer NbPts() const override;

			TnbSectPx_EXPORT std::vector<Pnt2d> Pts() const override;

			TnbSectPx_EXPORT Pnt2d CalcCoord() const;

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::OneParCPtsMap_Single);

#endif // !_SectPx_OneParCPtsMap_Single_Header
