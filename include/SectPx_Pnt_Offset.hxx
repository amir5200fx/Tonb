#pragma once
#ifndef _SectPx_Pnt_Offset_Header
#define _SectPx_Pnt_Offset_Header

#include <SectPx_MasterPnt.hxx>

namespace tnbLib
{

	namespace sectPxLib
	{

		class Pnt_Offset
			: public SectPx_MasterPnt
		{

			/*Private Data*/

			Standard_Real theX_;
			Standard_Real theY_;


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<SectPx_MasterPnt>(*this);
				ar & theX_;
				ar & theY_;
			}

		protected:

			Pnt_Offset()
				: theX_(0)
				, theY_(0)
			{}

			Pnt_Offset
			(
				const Standard_Real x, 
				const Standard_Real y
			)
				: theX_(x)
				, theY_(y)
			{}

			Pnt_Offset
			(
				const Standard_Integer theIndex, 
				const Standard_Real x, 
				const Standard_Real y
			);

			Pnt_Offset
			(
				const Standard_Integer theIndex,
				const word& theName,
				const Standard_Real x,
				const Standard_Real y
			);

		public:

			static const char* typeName_;

			auto X() const
			{
				return theX_;
			}

			auto Y() const
			{
				return theY_;
			}

			void SetX(const Standard_Real theX)
			{
				theX_ = theX;
			}

			void SetY(const Standard_Real theY)
			{
				theY_ = theY;
			}

			word RegObjTypeName() const override;

			//- override virtual functions from coord abstract class
			Standard_Real xCoord() const override
			{
				return X();
			}

			Standard_Real yCoord() const override
			{
				return Y();
			}

			Pnt2d Coord() const override;

			Standard_Boolean IsComplete() const override;

			//- override virtual functions from pnt abstract class 
			sectPxLib::pntType PntType() const override;

			Standard_Boolean IsOffset() const override;

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

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::sectPxLib::Pnt_Offset);

#include <SectPx_Pnt_OffsetI.hxx>
#include <SectPx_PntConstructor.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::InnerPnt<tnbLib::sectPxLib::Pnt_Offset>);
BOOST_CLASS_EXPORT_KEY(tnbLib::sectPxLib::OuterPnt<tnbLib::sectPxLib::Pnt_Offset>);

#endif // !_SectPx_Pnt_Offset_Header
