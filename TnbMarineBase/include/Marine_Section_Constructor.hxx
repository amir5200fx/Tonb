#pragma once
#ifndef _Marine_Section_Constructor_Header
#define _Marine_Section_Constructor_Header

#include <Standard_TypeDef.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Section;

	namespace marineLib
	{

		template<class SectionType> class OuterSection;

		template<class SectionType>
		class InnerSection
			: public SectionType
		{

			typedef OuterSection<SectionType> outerSection;

			/*Private Data*/

			std::weak_ptr<outerSection> theOuter_;

		public:

			template<class... _Types>
			InnerSection(_Types&&... _Args)
				: SectionType(_Args...)
			{}

			const auto& Outer() const
			{
				return theOuter_;
			}

			Standard_Boolean IsInner() const override
			{
				return Standard_True;
			}

			std::shared_ptr<Marine_Section> Copy() const override;

			void SetOuter(const std::shared_ptr<outerSection>& theSection)
			{
				theOuter_ = theSection;
			}
		};

	}

	namespace marineLib
	{

		template<class SectionType>
		class OuterSection
			: public SectionType
		{

			typedef InnerSection<SectionType> innerSection;
			/*Private Data*/

			std::map<Standard_Integer, std::shared_ptr<innerSection>> theInners_;

		public:

			template<class... _Types>
			OuterSection(_Types&&... _Args)
				: SectionType(_Args...)
			{}

			auto NbInners() const
			{
				return (Standard_Integer)theInners_.size();
			}

			const auto& Inners() const
			{
				return theInners_;
			}

			Standard_Boolean IsOuter() const override
			{
				return Standard_True;
			}

			std::shared_ptr<innerSection> 
				RemoveFromInners
				(
					const Standard_Integer theIndex
				);

			std::shared_ptr<Marine_Section> Copy() const override;

			void ImportToInners
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<innerSection>& theSection
			);

		};
	}
}

#include <Marine_Section_ConstructorI.hxx>

#endif // !_Marine_Section_Constructor_Header
