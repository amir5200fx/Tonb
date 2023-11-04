#pragma once
#ifndef _Voyage_RefPath_Header
#define _Voyage_RefPath_Header

#include <Voyage_Module.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Istream.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	class Voyage_RefPath
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Entity2d_Polygon>> thePath_;

		void LoadSingle(Istream&);

	public:

		// default constructor

		Voyage_RefPath()
		= default;

		// constructors


		// Public functions and operators

		[[nodiscard]] const auto& Path() const { return thePath_; }

		TnbVoyage_EXPORT void Load(Istream&);
		
	};
}

#endif
