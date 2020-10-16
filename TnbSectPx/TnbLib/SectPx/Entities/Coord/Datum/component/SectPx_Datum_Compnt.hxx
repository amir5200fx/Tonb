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

			void SetX
			(
				const std::shared_ptr<SectPx_Par>& theX
			);

			void SetY
			(
				const std::shared_ptr<SectPx_Par>& theY
			);

			word RegObjTypeName() const override;

			//- override virtual functions from coord abstract class

			Standard_Real xCoord() const override;

			Standard_Real yCoord() const override;

			Standard_Boolean IsComplete() const override;

			//- override virtual functions from parent abstract class 

			Standard_Integer NbChildren() const override;

			Standard_Boolean HasChildren() const override;

			Standard_Boolean
				HasChild
				(
					const std::shared_ptr<SectPx_Child>& thePar
				) const override;

			std::vector<std::shared_ptr<SectPx_Child>> RetrieveChildren() const override;

			Pnt2d Coord() const override;

			void RemoveThisFromChildren() const override;

			void AddThisToChildren() const override;

			void AddThisToChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			void RemoveThisFromChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;
		};
	}
}

#include <SectPx_Datum_CompntI.hxx>

#endif // !_SectPx_Datum_Compnt_Header
