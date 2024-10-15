#pragma once
#ifndef _Entity3d_CmpConnect_Prism_Header
#define _Entity3d_CmpConnect_Prism_Header

#include <Entity3d_CmpConnect.hxx>
#include <Entity_Connectivity.hxx>

namespace tnbLib
{

	class Entity3d_CmpConnect_Prism
		: public Entity3d_CmpConnect
	{

	public:

		enum
		{
			nbCmpts = 6
		};

		typedef std::array<Standard_Integer, nbCmpts> Array6;

	private:

		/*Private Data*/

		Array6 theCmpts_;

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

		Entity3d_CmpConnect_Prism() : theCmpts_({ 0,0,0,0,0,0 }) {}

		// constructors

		Entity3d_CmpConnect_Prism(const Array6& theCmpts)
			: theCmpts_(theCmpts)
		{}

		Entity3d_CmpConnect_Prism(Array6&& theCmpts)
			: theCmpts_(std::move(theCmpts))
		{}

		TnbGeo_EXPORT Entity3d_CmpConnect_Prism(const connectivity::sextuple& theSext);

		// Public functions and operators

		TnbGeo_EXPORT Standard_Boolean IsPrism() const override;

		const auto& Array() const { return theCmpts_; }

		auto Value(const Standard_Integer theIndex) const { return theCmpts_.at(theIndex); }
		auto& Value(const Standard_Integer theIndex) { return theCmpts_.at(theIndex); }

		TnbGeo_EXPORT Standard_Integer NbCmpts() const override;
		TnbGeo_EXPORT ElmType ElementType() const override;

		TnbGeo_EXPORT std::vector<Standard_Integer> Components() const override;
		TnbGeo_EXPORT std::vector<Pnt3d> RetrievePolygon(const std::vector<Pnt3d>&) const override;
		TnbGeo_EXPORT std::vector<Face> CalcFaces() const override;

		TnbGeo_EXPORT std::shared_ptr<Entity3d_CmpConnect> Copy() const override;

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Entity3d_CmpConnect_Prism);

#endif
