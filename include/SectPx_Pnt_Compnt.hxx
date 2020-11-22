#pragma once
#ifndef _SectPx_Pnt_Compnt_Header
#define _SectPx_Pnt_Compnt_Header

#include <SectPx_MasterPnt.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		class Pnt_Compnt
			: public SectPx_MasterPnt
		{

			/*Private Data*/

			std::weak_ptr<SectPx_Par> theX_;
			std::weak_ptr<SectPx_Par> theY_;


			DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

		protected:

			template<class... _Types>
			Pnt_Compnt(_Types&&... _Args)
				: SectPx_MasterPnt(_Args...)
			{}

		public:

			static TnbSectPx_EXPORT const char* typeName_;

			const auto& X() const
			{
				return theX_;
			}

			const auto& Y() const
			{
				return theY_;
			}

			TnbSectPx_EXPORT void SetX
			(
				const std::shared_ptr<SectPx_Par>& theX
			);

			TnbSectPx_EXPORT void SetY
			(
				const std::shared_ptr<SectPx_Par>& theY
			);

			TnbSectPx_EXPORT word RegObjTypeName() const override;

			//- override virtual functions from coord abstract class
			TnbSectPx_EXPORT Standard_Real xCoord() const override;

			TnbSectPx_EXPORT Standard_Real yCoord() const override;

			inline Pnt2d Coord() const override;

			TnbSectPx_EXPORT Standard_Boolean IsComplete() const override;

			//- override virtual functions from pnt abstract class 
			TnbSectPx_EXPORT sectPxLib::pntType PntType() const override;

			TnbSectPx_EXPORT Standard_Boolean IsComponent() const override;

			//- override virtual functions from parent abstract class 
			
			TnbSectPx_EXPORT Standard_Integer NbChildren() const override;

			TnbSectPx_EXPORT Standard_Boolean HasChildren() const override;

			TnbSectPx_EXPORT Standard_Boolean HasChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Child>>
				RetrieveChildren() const override;

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

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::sectPxLib::Pnt_Compnt);

#include <SectPx_Pnt_CompntI.hxx>
#include <SectPx_PntConstructor.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::InnerPnt<tnbLib::sectPxLib::Pnt_Compnt>);
BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::OuterPnt<tnbLib::sectPxLib::Pnt_Compnt>);

#endif // !_SectPx_Pnt_Compnt_Header
