#pragma once
#ifndef _SectPx_Datum_Compnt_Header
#define _SectPx_Datum_Compnt_Header

#include <SectPx_Datum.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		class Datum_Compnt
			: public SectPx_Datum
		{

			/*Private Data*/

			std::weak_ptr<SectPx_Par> theX_;
			std::weak_ptr<SectPx_Par> theY_;


			TNB_SERIALIZATION(TnbSectPx_EXPORT);

		public:

			static const char* typeName_;

			template<class... _Types>
			Datum_Compnt(_Types&&... _Args)
				: SectPx_Datum(_Args...)
			{}


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

			TnbSectPx_EXPORT Standard_Boolean IsComplete() const override;

			//- override virtual functions from parent abstract class 

			TnbSectPx_EXPORT Standard_Integer NbChildren() const override;

			TnbSectPx_EXPORT Standard_Boolean HasChildren() const override;

			TnbSectPx_EXPORT Standard_Boolean
				HasChild
				(
					const std::shared_ptr<SectPx_Child>& thePar
				) const override;

			TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Child>> RetrieveChildren() const override;

			inline Pnt2d Coord() const override;

			TnbSectPx_EXPORT void RemoveThisFromChildren() const override;

			TnbSectPx_EXPORT void AddThisToChildren() const override;

			TnbSectPx_EXPORT void AddThisToChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			TnbSectPx_EXPORT void RemoveThisFromChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;
		};
	}
}

#include <SectPx_Datum_CompntI.hxx>

#endif // !_SectPx_Datum_Compnt_Header
