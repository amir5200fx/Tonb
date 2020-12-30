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
	class Marine_xSection;
	class Marine_HullSection;

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


			/*private functions and operators*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::base_object<SectionType>(*this);
				ar & theOuter_;
			}

		protected:

			InnerSection()
			{}

		public:


			//- constructors

			explicit InnerSection
			(
				const std::shared_ptr<Pln_Wire>& theWire
			)
				: SectionType(theWire)
			{}

			InnerSection
			(
				std::shared_ptr<Pln_Wire>&& theWire
			)
				: SectionType(std::move(theWire))
			{}

			InnerSection
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pln_Wire>& theWire
			)
				: SectionType(theIndex, theWire)
			{}

			InnerSection
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Pln_Wire>&& theWire
			)
				: SectionType(theIndex, std::move(theWire))
			{}

			InnerSection
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<Pln_Wire>& theWire
			)
				: SectionType(theIndex, theName, theWire)
			{}

			InnerSection
			(
				const Standard_Integer theIndex,
				const word& theName,
				std::shared_ptr<Pln_Wire>&& theWire
			)
				: SectionType(theIndex, theName, std::move(theWire))
			{}


			//- public functions and operators

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


		template<>
		class InnerSection<Marine_Section>
		{

		private:

			InnerSection()
			{}
		};

		template<>
		class InnerSection<Marine_xSection>
		{

		private:

			InnerSection()
			{}
		};

		template<>
		class InnerSection<Marine_HullSection>
		{

		private:

			InnerSection()
			{}
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


			/*private functions and operators*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::base_object<SectionType>(*this);
				ar & theInners_;
			}

		protected:

			OuterSection()
			{}

		public:

			//- constructors

			explicit OuterSection
			(
				const std::shared_ptr<Pln_Wire>& theWire
			)
				: SectionType(theWire)
			{}

			OuterSection
			(
				std::shared_ptr<Pln_Wire>&& theWire
			)
				: SectionType(std::move(theWire))
			{}

			OuterSection
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pln_Wire>& theWire
			)
				: SectionType(theIndex, theWire)
			{}

			OuterSection
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Pln_Wire>&& theWire
			)
				: SectionType(theIndex, std::move(theWire))
			{}

			OuterSection
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<Pln_Wire>& theWire
			)
				: SectionType(theIndex, theName, theWire)
			{}

			OuterSection
			(
				const Standard_Integer theIndex,
				const word& theName,
				std::shared_ptr<Pln_Wire>&& theWire
			)
				: SectionType(theIndex, theName, std::move(theWire))
			{}


			//- public functions and operators

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


		template<>
		class OuterSection<Marine_Section>
		{

		private:

			OuterSection()
			{}
		};

		template<>
		class OuterSection<Marine_xSection>
		{

		private:

			OuterSection()
			{}
		};

		template<>
		class OuterSection<Marine_HullSection>
		{

		private:

			OuterSection()
			{}
		};
	}
}

#include <Marine_Section_ConstructorI.hxx>

#endif // !_Marine_Section_Constructor_Header
