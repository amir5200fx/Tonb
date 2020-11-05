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

			static const char* typeName_;

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

			Pnt2d Coord() const override;

			Standard_Boolean IsComplete() const override;			

			//- override virtual functions from pnt abstract class 
			sectPxLib::pntType PntType() const override;

			Standard_Boolean IsComponent() const override;

			//- override virtual functions from parent abstract class 
			
			Standard_Integer NbChildren() const override;

			Standard_Boolean HasChildren() const override;

			Standard_Boolean HasChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			std::vector<std::shared_ptr<SectPx_Child>> 
				RetrieveChildren() const override;

			void RemoveThisFromChildren() const override;

			void AddThisToChildren() const override;

			void RemoveThisFromChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			void AddThisToChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			
		};
	}
}

#include <SectPx_Pnt_CompntI.hxx>
#include <SectPx_PntConstructor.hxx>

#endif // !_SectPx_Pnt_Compnt_Header
