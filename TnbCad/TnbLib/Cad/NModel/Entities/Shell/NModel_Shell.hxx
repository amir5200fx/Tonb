#pragma once
#ifndef _NModel_Shell_Header
#define _NModel_Shell_Header

#include <NModel_Entity.hxx>
#include <Entity3d_BoxFwd.hxx>
#include <NModel_WaterTight.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class NModel_Surface;
	class Cad_Tools;

	class NModel_Shell
		: public NModel_Entity
	{

		typedef std::vector<std::shared_ptr<NModel_Surface>> surfaceList;

		/*Private Data*/

		surfaceList theSurfaces_;

		NModel_WaterTight theWaterTight_;

	protected:

		void Insert
		(
			const std::shared_ptr<NModel_Surface>& theSurface
		)
		{
			theSurfaces_.push_back(theSurface);
		}

		void SetWaterCondition
		(
			const NModel_WaterTight theTightness
		)
		{
			theWaterTight_ = theTightness;
		}

	public:

		NModel_Shell()
		{}

		NModel_Shell
		(
			const Standard_Integer theIndex
		)
			: NModel_Entity(theIndex)
		{}

		NModel_Shell
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: NModel_Entity(theIndex, theName)
		{}

		auto NbSurfaces() const
		{
			return (Standard_Integer)theSurfaces_.size();
		}

		const auto& Surfaces() const
		{
			return theSurfaces_;
		}

		auto WaterTightness() const
		{
			return theWaterTight_;
		}

		TnbCad_EXPORT Entity3d_Box CalcBoundingBox() const;


	};
}

#endif // !_NModel_Shell_Header
