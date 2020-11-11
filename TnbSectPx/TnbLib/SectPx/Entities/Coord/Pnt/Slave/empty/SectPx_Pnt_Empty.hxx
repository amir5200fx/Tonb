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

			std::shared_ptr<SectPx_MasterPnt> theMaster_;

			DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

		protected:

			Pnt_Empty()
			{}

			Pnt_Empty
			(
				const std::shared_ptr<SectPx_MasterPnt>& theMaster
			);

			Pnt_Empty
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<SectPx_MasterPnt>& theMaster
			);

			Pnt_Empty
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				const std::shared_ptr<SectPx_MasterPnt>& theMaster
			);

		public:

			static const char* typeName_;

			const auto& Master() const
			{
				return theMaster_;
			}

			void SetMaster
			(
				const std::shared_ptr<SectPx_MasterPnt>& theMaster
			);

			word RegObjTypeName() const override;

			//- override virtual functions from coord abstract class
			Standard_Real xCoord() const override;

			Standard_Real yCoord() const override;

			Pnt2d Coord() const override;

			Standard_Boolean IsComplete() const override;

			//- override virtual functions from pnt abstract class 
			sectPxLib::pntType PntType() const override;

			//- override virtual functions from slave abstract class 
			Standard_Boolean IsEmpty() const override;

			//- override virtual functions from parent abstract class 

			Standard_Integer NbChildMaps() const override;

			Standard_Boolean HasChildMap() const override;

			Standard_Boolean HasChild
			(
				const std::shared_ptr<SectPx_Child>& thePar
			) const override;

			std::shared_ptr<SectPx_Parent> ChildMap(const Standard_Integer theIndex) const override;

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
