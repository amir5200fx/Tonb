#include <Marine_PlnCurves.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_Section.hxx>
#include <Marine_SectionType.hxx>
#include <Marine_CmpSection.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Marine_TankModeler.hxx>
#include <Marine_SailModeler.hxx>
#include <Marine_DisplacerModeler.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>


#include <vector>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

namespace tnbLib
{
	static std::vector<std::shared_ptr<Marine_CmpSection>> sections;
	static size_t nbSections = 0;

	static Marine_SectionType bodyType;


	void loadSections(const std::string& name)
	{
		sections.reserve(nbSections);
		for (size_t i = 0; i < nbSections; i++)
		{
			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			std::fstream file;
			file.open(address, ios::in);

			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "file was not found" << endl
					<< abort(FatalError);
			}

			boost::archive::polymorphic_text_iarchive oa(file);

			std::shared_ptr<Marine_CmpSection> section;

			oa >> section;
			auto mSection = std::dynamic_pointer_cast<Marine_CmpSection>(section);
			if (!mSection)
			{
				FatalErrorIn(FunctionSIG)
					<< "the section is not marine type" << endl
					<< abort(FatalError);
			}

			sections.push_back(section);
		}

		if (sections.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no section has been loaded" << endl
				<< abort(FatalError);
		}

		const auto section = sections[0];

		switch (section->Type())
		{
		case Marine_SectionType::displacer:
			bodyType = Marine_SectionType::displacer;
			break;

		case Marine_SectionType::sail:
			bodyType = Marine_SectionType::sail;
			break;

		case Marine_SectionType::tank:
			bodyType = Marine_SectionType::tank;
			break;

		default:
			FatalErrorIn(FunctionSIG)
				<< "the section type is not supported" << endl
				<< abort(FatalError);
			break;
		}

		for (const auto x : sections)
		{
			if (x->Type() NOT_EQUAL bodyType)
			{
				FatalErrorIn(FunctionSIG)
					<< "section types must be the same." << endl
					<< abort(FatalError);
			}
		}

	}
}