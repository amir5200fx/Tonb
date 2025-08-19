#pragma once
#ifndef _SectPx_Pnt_Empty_Header
#define _SectPx_Pnt_Empty_Header

#include <SectPx_SlavePnt.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_MasterPnt;

	namespace sectPxLib
	{

		class Pnt_Empty
			: public SectPx_SlavePnt
		{

			/*Private Data*/

			
			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<SectPx_SlavePnt>(*this);
			}

		protected:

			Pnt_Empty()
			{}

			TnbSectPx_EXPORT Pnt_Empty
			(
				const std::shared_ptr<SectPx_MasterPnt>& theMaster
			);

			TnbSectPx_EXPORT Pnt_Empty
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<SectPx_MasterPnt>& theMaster
			);

			TnbSectPx_EXPORT Pnt_Empty
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				const std::shared_ptr<SectPx_MasterPnt>& theMaster
			);

		public:

			static TnbSectPx_EXPORT const char* typeName_;


			TnbSectPx_EXPORT word RegObjTypeName() const override;

			//- override virtual functions from coord abstract class
			TnbSectPx_EXPORT Standard_Real xCoord() const override;

			TnbSectPx_EXPORT Standard_Real yCoord() const override;

			TnbSectPx_EXPORT Pnt2d Coord() const override;

			TnbSectPx_EXPORT Standard_Boolean IsComplete() const override;

			//- override virtual functions from pnt abstract class 
			TnbSectPx_EXPORT sectPxLib::pntType PntType() const override;

			//- override virtual functions from slave abstract class 
			TnbSectPx_EXPORT Standard_Boolean IsEmpty() const override;

			//- override virtual functions from parent abstract class 

			TnbSectPx_EXPORT Standard_Integer NbChildMaps() const override;

			TnbSectPx_EXPORT Standard_Boolean HasChildMap() const override;

			TnbSectPx_EXPORT Standard_Boolean HasChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Parent> ChildMap(const Standard_Integer theIndex) const override;

			TnbSectPx_EXPORT void RemoveThisFromChildren() const override;

			TnbSectPx_EXPORT void AddThisToChildren() const override;

			TnbSectPx_EXPORT void RemoveThisFromChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			TnbSectPx_EXPORT void AddThisToChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::sectPxLib::Pnt_Empty);

#include <SectPx_PntConstructor.hxx>

namespace tnbLib
{
	namespace sectPxLib
	{

		template<>
		class InnerPnt<Pnt_Empty>
			: public Pnt_Empty
		{};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::OuterPnt<tnbLib::sectPxLib::Pnt_Empty>);

#endif // !_SectPx_Pnt_Empty_Header
