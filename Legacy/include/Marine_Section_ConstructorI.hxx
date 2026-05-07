#pragma once
#include <Pln_Wire.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		template<class SectionType>
		std::shared_ptr<Marine_Section>
			tnbLib::marineLib::InnerSection<SectionType>::Copy() const
		{
			auto wire = std::dynamic_pointer_cast<Pln_Wire>(this->Wire()->Copy());
			Debug_Null_Pointer(wire);

			auto copy = std::make_shared<InnerSection<SectionType>>(this->Index(), this->Name(), wire);
			Debug_Null_Pointer(copy);

			return std::move(copy);
		}

		template<class SectionType>
		std::shared_ptr<typename OuterSection<SectionType>::innerSection>
			OuterSection<SectionType>::RemoveFromInners
			(
				const Standard_Integer theIndex
			)
		{
			auto iter = theInners_.find(theIndex);
			if (iter IS_EQUAL theInners_.end())
			{
				FatalErrorIn
				(
					"std::shared_ptr<innerSection> RemoveFromInners(const Standard_Integer theIndex)"
				)
					<< "the item is not in the tree!" << endl
					<< " - index = " << theIndex << endl
					<< abort(FatalError);
			}
			auto item = std::move(iter->second);
			theInners_.erase(iter);
			return std::move(item);
		}

		template<class SectionType>
		std::shared_ptr<Marine_Section> OuterSection<SectionType>::Copy() const
		{
			auto wire = std::dynamic_pointer_cast<Pln_Wire>(this->Wire()->Copy());
			Debug_Null_Pointer(wire);

			auto copy = std::make_shared<OuterSection<SectionType>>(this->Index(), this->Name(), wire);
			Debug_Null_Pointer(copy);
			for (const auto& x : Inners())
			{
				Debug_Null_Pointer(x.second);
				auto c = std::dynamic_pointer_cast<InnerSection<SectionType>>(x.second->Copy());
				copy->ImportToInners(x.first, c);

				c->SetOuter(copy);
			}
			return std::move(copy);
		}

		template<class SectionType>
		void OuterSection<SectionType>::ImportToInners
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<innerSection>& theSection
		)
		{
			auto paired = std::make_pair(theIndex, theSection);
			auto insert = theInners_.insert(std::move(paired));
			if (NOT insert.second)
			{
				FatalErrorIn
				(
					"void ImportToInners(const Standard_Integer theIndex, const std::shared_ptr<innerSection>& theSection)"
				)
					<< "douplicate data!" << endl
					<< " - index = " << theIndex << endl
					<< abort(FatalError);
			}
		}


	}
}