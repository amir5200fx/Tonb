#pragma once
#ifndef _Entity2d_CmpConnect_Polygon_Header
#define _Entity2d_CmpConnect_Polygon_Header

#include <Entity2d_CmpConnect.hxx>
#include <Entity_Connectivity.hxx>

#include <vector>

namespace tnbLib
{
	class Entity2d_CmpConnect_Polygon
		: public Entity2d_CmpConnect
	{
		/*Private Data*/
		std::vector<Standard_Integer> theCmpts_;

		// Private functions and operators
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Entity2d_CmpConnect>(*this);
			ar& theCmpts_;
		}
	public:
		// default constructor
		Entity2d_CmpConnect_Polygon() = default;
		// constructors
		explicit Entity2d_CmpConnect_Polygon(const std::vector<Standard_Integer>& theCmpts)
			: theCmpts_(theCmpts)
		{}
		explicit Entity2d_CmpConnect_Polygon(std::vector<Standard_Integer>&& theCmpts)
			: theCmpts_(std::move(theCmpts))
		{}
		// Public functions and operators
		TnbGeo_EXPORT Standard_Boolean IsPolygon() const override;

		const auto& Array() const { return theCmpts_; }

		auto Value(const Standard_Integer theIndex) const { return theCmpts_.at(theIndex); }
		auto& Value(const Standard_Integer theIndex) { return theCmpts_.at(theIndex); }

		TnbGeo_EXPORT Standard_Integer NbCmpts() const override;
		TnbGeo_EXPORT ElmType ElementType() const override;

		TnbGeo_EXPORT std::vector<Standard_Integer> Components() const override;
		TnbGeo_EXPORT std::vector<Pnt2d> RetrievePolygon(const std::vector<Pnt2d>&) const override;
		TnbGeo_EXPORT std::vector<Pnt3d> RetrievePolygon(const std::vector<Pnt3d>&) const override;

		TnbGeo_EXPORT std::shared_ptr<Entity2d_CmpConnect> Copy() const override;

		TnbGeo_EXPORT void Update(const std::vector<Standard_Integer>&) override;
	};
}
BOOST_CLASS_EXPORT_KEY(tnbLib::Entity2d_CmpConnect_Polygon);
#endif