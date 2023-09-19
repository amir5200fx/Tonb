#pragma once
#ifndef _Entity3d_CmpConnect_Pyramid_Header
#define _Entity3d_CmpConnect_Pyramid_Header

#include <Entity3d_CmpConnect.hxx>
#include <Entity_Connectivity.hxx>

namespace tnbLib
{

	class Entity3d_CmpConnect_Pyramid
		: public Entity3d_CmpConnect
	{

	public:

		enum
		{
			nbCmpts = 5
		};

		typedef std::array<Standard_Integer, nbCmpts> Array5;

	private:

		/*Private Data*/

		Array5 theCmpts_;

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

		Entity3d_CmpConnect_Pyramid() : theCmpts_({ 0,0,0,0,0 }) {}

		// constructors

		Entity3d_CmpConnect_Pyramid(const Array5& theCmpts)
			: theCmpts_(theCmpts)
		{}

		Entity3d_CmpConnect_Pyramid(Array5&& theCmpts)
			: theCmpts_(std::move(theCmpts))
		{}

		TnbGeo_EXPORT Entity3d_CmpConnect_Pyramid(const connectivity::quintuple& theQuin);

		// Public functions and operators

		TnbGeo_EXPORT Standard_Boolean IsPyramid() const override;

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

BOOST_CLASS_EXPORT_KEY(tnbLib::Entity3d_CmpConnect_Pyramid);

#endif
