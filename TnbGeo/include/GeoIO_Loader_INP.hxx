#pragma once
#ifndef _GeoIO_Loader_INP_Header
#define _GeoIO_Loader_INP_Header

#include <Geo_Module.hxx>
#include <Global_Done.hxx>
#include <Istream.hxx>

#include <map>
#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [9/5/2023 aamir]
	class GeoIO_INPPoint;
	class GeoIO_INPElement;

	class GeoIO_Loader_INP
		: public Global_Done
	{

	public:

		struct ElemSet
		{
			std::string name;
			std::vector<std::shared_ptr<GeoIO_INPElement>> elements;

			TNB_SERIALIZATION(TnbGeo_EXPORT);
		};

		struct ElemGroup
		{
			std::string name;
			std::vector<Standard_Integer> elements;

			TNB_SERIALIZATION(TnbGeo_EXPORT);
		};

		enum class ElmType 
		{
			B31,
			CPS3
		};

	private:

		/*Private Data*/

		std::vector<std::shared_ptr<GeoIO_INPPoint>> theCoords_;
		std::vector<std::shared_ptr<ElemSet>> theElements_;

		std::map<word, std::shared_ptr<ElemGroup>> theElemSets_;

		// Private functions and operators [9/5/2023 aamir]


		TnbGeo_EXPORT void ReadNodes(std::istream&);
		TnbGeo_EXPORT std::vector<std::shared_ptr<GeoIO_INPElement>> ReadElements(std::istream&, const ElmType t);
		TnbGeo_EXPORT std::vector<Standard_Integer> ReadElementGroup(std::istream&);

		static TnbGeo_EXPORT std::vector<std::string> ParseLine(const std::string&);
		static TnbGeo_EXPORT std::string ParseElementType(const std::string&);
		static TnbGeo_EXPORT std::string ParseElementSet(const std::string&);
		static TnbGeo_EXPORT std::string ParseGroupSet(const std::string&);
		static TnbGeo_EXPORT std::string Trim(const std::string& str);

		TNB_SERIALIZATION(TnbGeo_EXPORT);

	public:

		static TnbGeo_EXPORT const std::string extension;

		// default constructor [9/5/2023 aamir]

		GeoIO_Loader_INP()
		{}

		// constructors [9/5/2023 aamir]

		TnbGeo_EXPORT GeoIO_Loader_INP(std::istream&);

		// Public functions and operators [9/5/2023 aamir]

		friend TnbGeo_EXPORT std::istream& operator>>(std::istream& is, GeoIO_Loader_INP&);

	};

}

#endif // !_GeoIO_Loader_INP_Header
