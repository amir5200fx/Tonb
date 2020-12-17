#pragma once
#ifndef _shapeMaker_Header
#define _shapeMaker_Header

#include <frameTunnerFwd.hxx>
#include <SectPx_Registry.hxx>

#include <vector>
#include <memory>
#include <word.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Registry;
	class ShapePx_Section;
	class SectPx_FrameRegistry;
	class SectPx_TopoSegment;
	class ShapePx_ExtrudedPatch;
	class ShapePx_ExtrudeOp;
	class ShapePx_Patch;
	class ShapePx_Profile;
	class ShapePx_Spacing;


	namespace appl
	{

		typedef std::shared_ptr<ShapePx_Section> section_t;
		typedef std::shared_ptr<SectPx_FrameRegistry> frameReg_t;
		typedef std::shared_ptr<SectPx_TopoSegment> topoSegment_t;
		typedef std::shared_ptr<ShapePx_ExtrudedPatch> extruded_t;
		typedef std::shared_ptr<ShapePx_Patch> patch_t;
		typedef std::shared_ptr<ShapePx_Profile> extrProfile_t;
		typedef std::shared_ptr<ShapePx_ExtrudeOp> extrudeOp_t;
		typedef std::shared_ptr<ShapePx_Spacing> spacing_t;

		typedef std::tuple<par_t, par_t, par_t, par_t>
			profileBnd;
		typedef std::pair<par_t, par_t>
			profileQ;

		//- memory

		extern const auto myRegistry = std::make_shared<SectPx_Registry>();
		extern const extruded_t myPatch;
		extern const extrudeOp_t myOp;
		extern spacing_t mySpacing;

		//- global functions

		const auto& getRegistry()
		{
			return myRegistry;
		}

		const auto& getParRegistry()
		{
			return getRegistry()->Parameter();
		}

		//- sections functions

		void createSection();
		const section_t& getSection();
		frame_t createSectionFrame();

		//- extrusion profiles

		profileBnd createProfileBounds(const par_t& minLow, const par_t& maxLow, const par_t& x0, const par_t& x1);

		extrProfile_t createUniformExtrudeProfile(const profileBnd& b, const par_t& v);
		extrProfile_t createLinearExtrudeProfile(const profileBnd& b, const par_t& v0, const par_t& v1);
		extrProfile_t createThreeExtrudeProfile(const profileBnd& b, const par_t& v0, const par_t& v2, const profileQ& q1);
		extrProfile_t createFiveExtrudeProfile(const profileBnd& b, const par_t& v0, const par_t& v4, const profileQ& q1, const profileQ& q2, const profileQ& q3);

		void setExtrudeProfile(int par, const extrProfile_t& t);

		void execute();
		void calcSpacing();

		void setName(const section_t& s, const std::string& name);


	}
}

#endif // !_shapeMaker_Header
