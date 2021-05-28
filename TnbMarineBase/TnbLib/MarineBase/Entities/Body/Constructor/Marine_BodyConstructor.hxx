#pragma once
#ifndef _Marine_BodyConstructor_Header
#define _Marine_BodyConstructor_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Shape;

	namespace marineLib
	{

		template<class BodyType>
		class BodyConstructor_Shape
			: public BodyType
		{

			/*Private Data*/

			std::shared_ptr<Marine_Shape> theShape_;

			Standard_Boolean IsSymmetric_;

			/*private functions and operators*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				//- this function should never be called
				NotImplemented;
			}

		protected:

			

		public:

			/*template<class... _Types>
			BodyConstructor_Shape(_Types&&... _Args)
				: BodyType(_Args...)
			{}*/

			// default constructor

			BodyConstructor_Shape()
				: IsSymmetric_(Standard_False)
			{}

			//- constructors

			BodyConstructor_Shape
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
			)
				: BodyType(theSections)
				, IsSymmetric_(Standard_False)
			{}

			BodyConstructor_Shape
			(
				std::vector<std::shared_ptr<Marine_CmpSection>>&& theSections
			)
				: BodyType(std::move(theSections))
				, IsSymmetric_(Standard_False)
			{}

			BodyConstructor_Shape
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
			)
				: BodyType(theIndex, theName, theSections)
				, IsSymmetric_(Standard_False)
			{}

			BodyConstructor_Shape
			(
				const Standard_Integer theIndex,
				const word& theName, 
				std::vector<std::shared_ptr<Marine_CmpSection>>&& theSections
			)
				: BodyType(theIndex, theName, std::move(theSections))
				, IsSymmetric_(Standard_False)
			{}


			//- public functions and operators

			Standard_Boolean ShapeType() const override
			{
				return Standard_True;
			}

			const auto& Shape() const
			{
				return theShape_;
			}

			auto IsSymmetric() const
			{
				return IsSymmetric_;
			}

			void SetShape(const std::shared_ptr<Marine_Shape>& theShape)
			{
				theShape_ = theShape;
			}

			void SetSymmetric(const Standard_Boolean symm)
			{
				IsSymmetric_ = symm;
			}
		};

	}


	namespace marineLib
	{

		template<class BodyType>
		class BodyConstructor_noShape
			: public BodyType
		{

			/*Private Data*/


			/*private functions and operators*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<BodyType>(*this);
			}

		protected:


			

		public:

			/*template<class... _Types>
			BodyConstructor_noShape(_Types&&... _Args)
				: BodyType(_Args...)
			{}*/


			//- default constructor

			BodyConstructor_noShape()
			{}


			//- constructors

			BodyConstructor_noShape
			(
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
			)
				: BodyType(theSections)
			{}

			BodyConstructor_noShape
			(
				std::vector<std::shared_ptr<Marine_CmpSection>>&& theSections
			)
				: BodyType(std::move(theSections))
			{}

			BodyConstructor_noShape
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::vector<std::shared_ptr<Marine_CmpSection>>& theSections
			)
				: BodyType(theIndex, theName, theSections)
			{}

			BodyConstructor_noShape
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				std::vector<std::shared_ptr<Marine_CmpSection>>&& theSections
			)
				: BodyType(theIndex, theName, std::move(theSections))
			{}


			//- public functions and operators



		};
	}


}

#include <Marine_BodyConstructorI.hxx>

#endif // !_Marine_BodyConstructor_Header
