#pragma once
#ifndef _Entity3d_TriVolume_Header
#define _Entity3d_TriVolume_Header

#include <Geo_Module.hxx>
#include <OFstream.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{
	// Forward Declarations
	class Entity3d_TriShell;

	class Entity3d_TriVolume
	{
	public:
		typedef std::shared_ptr<Entity3d_TriShell> OuterShell;
		typedef std::shared_ptr<std::vector<std::shared_ptr<Entity3d_TriShell>>> InnerShells;
	private:
		/*Private Data*/
		OuterShell theOuter_;
		InnerShells theInners_;
	public:
		// default constructor
		// Entity3d_TriVolume() = default;
		// constructors
		Entity3d_TriVolume(const OuterShell& theOuter, const InnerShells& theInners = nullptr)
			: theOuter_(theOuter)
			, theInners_(theInners)
		{}
		Entity3d_TriVolume(OuterShell&& theOuter, InnerShells&& theInners)
			: theOuter_(std::move(theOuter))
			, theInners_(std::move(theInners))
		{}
		// Public functions and operators
		const auto& Outer() const { return theOuter_; }
		const auto& Inners() const { return theInners_; }

		// io functions
		TnbGeo_EXPORT void ExportToPlt(OFstream&) const;
	};
}

#endif