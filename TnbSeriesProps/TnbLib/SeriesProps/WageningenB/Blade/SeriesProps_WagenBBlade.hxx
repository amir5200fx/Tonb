#pragma once
#ifndef _SeriesProps_WagenBBlade_Header
#define _SeriesProps_WagenBBlade_Header

#include <SeriesProps_Module.hxx>
#include <Global_Done.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [12/29/2022 Payvand]
	class SeriesProps_WagenB_Section;
	class SeriesProps_EdgeThick;
	class Geo_xDistb;

	class SeriesProps_WagenBBlade
		: public Global_Done
	{

	public:

		struct A
		{
			Standard_Real value;
		};

		struct B
		{
			Standard_Real value;
		};

		struct Chord
		{
			Standard_Real value;
		};

		struct Thick
		{
			Standard_Real value;
		};

	private:

		/*Private Data*/

		std::shared_ptr<Geo_xDistb> therPerR_;
		std::shared_ptr<Geo_xDistb> theSectionXs_;

		std::shared_ptr<SeriesProps_EdgeThick> theLE_;
		std::shared_ptr<SeriesProps_EdgeThick> theTE_;

		Standard_Real theDiameter_;
		Standard_Real theAEperAO_;

		Standard_Integer theNbBlades_;

		// results [12/29/2022 Payvand]

		std::vector<std::shared_ptr<SeriesProps_WagenB_Section>>
			theSections_;


		// Private functions and operators [12/29/2022 Payvand]

		auto& SectionsRef()
		{
			return theSections_;
		}

		TnbSeriesProps_EXPORT std::tuple<Chord, A, B, Thick>
			CalcThreeBladedParameters(const Standard_Real rPerR) const;

		TnbSeriesProps_EXPORT std::tuple<Chord, A, B, Thick>
			CalcParameters(const Standard_Real rPerR) const;

		TnbSeriesProps_EXPORT std::shared_ptr<SeriesProps_WagenB_Section>
			CalcSectionThreeBladed(const Standard_Real rPerR) const;

		TnbSeriesProps_EXPORT std::shared_ptr<SeriesProps_WagenB_Section>
			CalcSection(const Standard_Real rPerR) const;

	public:

		// default constructor [4/30/2022 Amir]

		SeriesProps_WagenBBlade()
		{}


		// constructors [4/30/2022 Amir]


		// public functions and operators [4/30/2022 Amir]

		const auto& rPerR() const
		{
			return therPerR_;
		}

		const auto& SectionXs() const
		{
			return theSectionXs_;
		}

		auto Diameter() const
		{
			return theDiameter_;
		}

		auto AEPerAO() const
		{
			return theAEperAO_;
		}

		auto NbBlades() const
		{
			return theNbBlades_;
		}

		const auto& Sections() const
		{
			return theSections_;
		}

		const auto& LE() const
		{
			return theLE_;
		}

		const auto& TE() const
		{
			return theTE_;
		}

		TnbSeriesProps_EXPORT void Perform();

		void SetrPerR(const std::shared_ptr<Geo_xDistb>& theR)
		{
			therPerR_ = theR;
		}

		void SetDiameter(const Standard_Real theDia)
		{
			theDiameter_ = theDia;
		}

		void SetAEPerAO(const Standard_Real theValue)
		{
			theAEperAO_ = theValue;
		}

		void SetNbBlades(const Standard_Integer theZ)
		{
			theNbBlades_ = theZ;
		}
	};
}

#endif // !_SeriesProps_WagenBBlade_Header
