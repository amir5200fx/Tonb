#pragma once
#ifndef _Marine_Water_Header
#define _Marine_Water_Header

#include <Marine_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Section;

	namespace marineLib { class Section_Water; }

	class Marine_Water
		: public Marine_Entity
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Marine_Section>> theSections_;

	public:

		Marine_Water
		(
			const std::vector<std::shared_ptr<marineLib::Section_Water>>& theSections
		);

		Marine_Water
		(
			std::vector<std::shared_ptr<marineLib::Section_Water>>&& theSections
		);

		Marine_Water
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::vector<std::shared_ptr<marineLib::Section_Water>>& theSections
		);

		Marine_Water
		(
			const Standard_Integer theIndex,
			const word& theName, 
			std::vector<std::shared_ptr<marineLib::Section_Water>>&& theSections
		);


		auto NbSections() const
		{
			return (Standard_Integer)theSections_.size();
		}

		const auto& Sections() const
		{
			return theSections_;
		}
	};
}

#endif // !_Marine_Water_Header
