#pragma once
#ifndef _Marine_SectionsFwd_Header
#define _Marine_SectionsFwd_Header

namespace tnbLib
{

	class Marine_Section;
	class Marine_xSection;
	class Marine_zSection;

	namespace marineLib
	{

		class Section_Displacer;
		class Section_Dry;
		class Section_Wetted;
		class Section_Water;
		class Section_WaterLine;
		class Section_Tank;
		class Section_Sail;

		template<class SectionType> class InnerSection;
		template<class SectionType> class OuterSection;
	}
}

#endif // !_Marine_SectionsFwd_Header
