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

#include <Marine_Section_Constructor.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		template<>
		class OuterSection<Section_Water>
			: public Section_Water
		{

			/*Private Data*/

		public:

			template<class... _Types>
			OuterSection(_Types&&... _Args)
				: Section_Water(_Args...)
			{}

			Standard_Boolean IsOuter() const override
			{
				return Standard_True;
			}

			std::shared_ptr<Marine_Section> Copy() const override;
		};
	}
}

#endif // !_Marine_Section_Water_Header
