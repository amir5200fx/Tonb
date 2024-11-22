#pragma once
#ifndef _Entity3d_CmpConnect_Header
#define _Entity3d_CmpConnect_Header

#include <Global_TypeDef.hxx>
#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>
#include <vector>
#include <map>
#include <array>

namespace tnbLib
{

	// Forward Declarations
	class Pnt3d;
	
	class Entity3d_CmpConnect
		: public std::enable_shared_from_this<Entity3d_CmpConnect>
	{
	public:
		struct Face
		{
			std::vector<Standard_Integer> ids;
		};
	private:
		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			// empty body
		}

	protected:

		// default constructor

		Entity3d_CmpConnect()
		{}

	public:
		virtual ~Entity3d_CmpConnect() = default;

		enum class ElmType
		{
			brick,
			prism,
			pyramid,
			tetrahedron,
			extruded_polygon
		};


		// Public functions and operators

		virtual Standard_Boolean IsBrick() const { return Standard_False; }
		virtual Standard_Boolean IsPrism() const { return Standard_False; }
		virtual Standard_Boolean IsPyramid() const { return Standard_False; }
		virtual Standard_Boolean IsTetrahedron() const { return Standard_False; }
		virtual Standard_Boolean IsExtrudedPolygon() const { return Standard_False; }

		virtual Standard_Integer NbCmpts() const = 0;
		virtual ElmType ElementType() const = 0;

		virtual std::vector<Standard_Integer> Components() const = 0;
		virtual std::vector<Pnt3d> RetrievePolygon(const std::vector<Pnt3d>&) const = 0;
		virtual std::vector<Face> CalcFaces() const = 0;

		virtual std::shared_ptr<Entity3d_CmpConnect> Copy() const = 0;

		virtual void Update(const std::vector<Standard_Integer>&) = 0;
		virtual void Update(const std::map<Standard_Integer, Standard_Integer>&) = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Entity3d_CmpConnect);

#endif
