#pragma once
#ifndef _Marine_Section_Water_Header
#define _Marine_Section_Water_Header

#include <Marine_Section.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Section_Water
			: public Marine_Section
		{

			/*Private Data*/


			/*private functions and operators*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<Marine_Section>(*this);
			}

		protected:

			template<class... _Types>
			Section_Water(_Types&&... _Args)
				: Marine_Section(_Args...)
			{}

		public:

			Standard_Boolean IsWaterSection() const override
			{
				return Standard_True;
			}

			virtual Standard_Boolean IsInner() const
			{
				return Standard_False;
			}

			virtual Standard_Boolean IsOuter() const
			{
				return Standard_False;
			}

			//std::shared_ptr<Marine_Section> Copy() const override;

			Marine_SectionType Type() const override
			{
				return Marine_SectionType::water;
			}

		};
	}
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::marineLib::Section_Water);

#include <Marine_Section_Constructor.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		//- prevent to create any inner water section!
		template<>
		class InnerSection<Section_Water>
			: public Section_Water
		{};

		template<>
		class OuterSection<Section_Water>
			: public Section_Water
		{

			/*Private Data*/


			/*private functions and operators*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<Section_Water>(*this);
			}

		protected:

			OuterSection()
			{}

		public:

			TnbMarine_EXPORT explicit OuterSection
			(
				const std::shared_ptr<Pln_Wire>& theWire
			);

			TnbMarine_EXPORT OuterSection
			(
				std::shared_ptr<Pln_Wire>&& theWire
			);

			TnbMarine_EXPORT OuterSection
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pln_Wire>& theWire
			);

			TnbMarine_EXPORT OuterSection
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Pln_Wire>&& theWire
			);

			TnbMarine_EXPORT OuterSection
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<Pln_Wire>& theWire
			);

			TnbMarine_EXPORT OuterSection
			(
				const Standard_Integer theIndex,
				const word& theName,
				std::shared_ptr<Pln_Wire>&& theWire
			);

			Standard_Boolean IsOuter() const override
			{
				return Standard_True;
			}

			TnbMarine_EXPORT std::shared_ptr<Marine_Section> Copy() const override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_Water>);

#endif // !_Marine_Section_Water_Header
