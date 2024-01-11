#pragma once
#ifndef _GeoSizeFun2d_Multi_Header
#define _GeoSizeFun2d_Multi_Header

#include <Geo2d_SizeFunction.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	class GeoSizeFun2d_Multi
		: public Geo2d_SizeFunction
	{

		/*Private Date*/

		std::vector<std::shared_ptr<Geo2d_SizeFunction>> theFunctions_;

		// Private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		// default constructors

		GeoSizeFun2d_Multi()
		{}

		GeoSizeFun2d_Multi(const std::vector<std::shared_ptr<Geo_SizeFunction>>& theFuns)
			: theFunctions_(theFuns)
		{}

		GeoSizeFun2d_Multi(std::vector<std::shared_ptr<Geo2d_SizeFunction>>&& theFuns)
			: theFunctions_(std::move(theFuns))
		{}

		// Public fuctions and operators

		const auto& Functions() const { return theFunctions_; }

		TnbMesh_EXPORT Standard_Real Value(const Pnt2d& theCoord) const override;

		void SetFunctions(const std::vector<std::shared_ptr<Geo_SizeFunction>>& theFuns)
		{
			theFunctions_ = theFuns;
		}

		void SetFunctions(std::vector<std::shared_ptr<Geo2d_SizeFunction>>&& theFuns)
		{
			theFunctions_ = std::move(theFuns);
		}
		
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoSizeFun2d_Multi);

#endif
