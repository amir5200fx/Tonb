#pragma once
#ifndef _HydroStatic_CrossCurves_Header
#define _HydroStatic_CrossCurves_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_Done.hxx>

#include <memory>

#include <gp_Ax1.hxx>

namespace tnbLib
{

	// Forward Declarations
	class CrossSection_xShapeStation;
	class Marine_SectionDistribution;

	class HydroStatic_CrossCurves
		: public Global_Indexed
		, public Global_Named
		, public Global_Done
	{

		/*Private Data*/

		gp_Ax1 theK_;

		std::shared_ptr<CrossSection_xShapeStation> theModel_;
		std::shared_ptr<Marine_SectionDistribution> theHeel_;

	public:

		HydroStatic_CrossCurves();

		HydroStatic_CrossCurves(const Standard_Integer theIndex);

		HydroStatic_CrossCurves(const Standard_Integer theIndex, const word& theName);

		const auto& K() const
		{
			return theK_;
		}

		const auto& Model() const
		{
			return theModel_;
		}

		void Perform();

		void LoadModel
		(
			const std::shared_ptr<CrossSection_xShapeStation>& theModel
		)
		{
			theModel_ = theModel;
		}

		void LoadHeel
		(
			const std::shared_ptr<Marine_SectionDistribution>& theHeel
		)
		{
			theHeel_ = theHeel;
		}
	};
}

#endif // !_HydroStatic_CrossCurves_Header
