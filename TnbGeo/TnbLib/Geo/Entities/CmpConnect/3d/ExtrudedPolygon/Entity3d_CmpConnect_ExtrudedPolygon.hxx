#pragma once
#ifndef _Entity3d_CmpConnect_ExtrudedPolygon_Header
#define _Entity3d_CmpConnect_ExtrudedPolygon_Header

#include <Entity3d_CmpConnect.hxx>
#include <Entity_Connectivity.hxx>

namespace tnbLib
{
	class Entity3d_CmpConnect_ExtrudedPolygon
		: public Entity3d_CmpConnect
	{
		/*Private Data*/
		std::vector<Standard_Integer> theCmpts_;

		// Private functions and operators
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Entity3d_CmpConnect>(*this);
			ar& theCmpts_;
		}

	public:

		// default constructor
		Entity3d_CmpConnect_ExtrudedPolygon() = default;

		// constructors
		Entity3d_CmpConnect_ExtrudedPolygon(const std::vector<Standard_Integer>& theCmpts)
			: theCmpts_(theCmpts)
		{}
		Entity3d_CmpConnect_ExtrudedPolygon(std::vector<Standard_Integer>&& theCmpts)
			: theCmpts_(std::move(theCmpts))
		{}

		// Public functions and operators
		TnbGeo_EXPORT Standard_Boolean IsExtrudedPolygon() const override;

		const auto& Array() const { return theCmpts_; }

		auto Value(const Standard_Integer theIndex) const { return theCmpts_.at(theIndex); }
		auto& Value(const Standard_Integer theIndex) { return theCmpts_.at(theIndex); }

		TnbGeo_EXPORT Standard_Integer NbCmpts() const override;
		TnbGeo_EXPORT ElmType ElementType() const override;

		TnbGeo_EXPORT std::vector<Standard_Integer> Components() const override;
		TnbGeo_EXPORT std::vector<Pnt3d> RetrievePolygon(const std::vector<Pnt3d>&) const override;

		TnbGeo_EXPORT std::shared_ptr<Entity3d_CmpConnect> Copy() const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Entity3d_CmpConnect_ExtrudedPolygon);

#endif // !_Entity3d_CmpConnect_ExtrudedPolygon_Header
