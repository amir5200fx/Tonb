#pragma once
#ifndef _GeoMesh_Data_Header
#define _GeoMesh_Data_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	template<class Point, class Connectivity, bool NeighbData>
	class Entity_StaticData;

	struct GeoMesh_DataInfo
	{
		static TnbMesh_EXPORT const int DEFAULT_MAX_CYCLES;
	};

	template<class ElementType>
	class GeoMesh_Data
		: public GeoMesh_DataInfo
	{

	public:

		typedef ElementType elementType;
		typedef std::vector<std::shared_ptr<elementType>> elementList;

		typedef typename elementType::nodeType nodeType;
		typedef typename nodeType::ptType Point;
		typedef typename elementType::connectType connectType;
		typedef typename elementType::edgeType edgeType;
		typedef typename elementType::facetType facetType;

		typedef Entity_StaticData<Point, connectType, false>
			triangulation;

	private:

		/*Private Data*/

		elementList theElements_;



		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			//- this function should never be called
			NotImplemented;
		}


	public:

		// default constructor [4/8/2022 Amir]

		GeoMesh_Data()
		{}

		// constructors [4/8/2022 Amir]

		explicit GeoMesh_Data(const elementList& theElements)
			: theElements_(theElements)
		{}

		GeoMesh_Data(elementList&& theElements)
			: theElements_(std::move(theElements))
		{}


		// public functions and operators [4/8/2022 Amir]

		void Construct(const triangulation& theTriangulation);

		const elementList& Elements() const
		{
			return theElements_;
		}

		const std::shared_ptr<elementType>& FirstElement() const
		{
			Debug_If_Condition_Message(theElements_.empty(), "the elements list is empty");
			return theElements_[0];
		}

		std::shared_ptr<elementType> TriangleLocation
		(
			const std::shared_ptr<elementType>& theStart,
			const Point& theCoord
		) const;

		std::shared_ptr<triangulation> StaticData() const;

		void RetrieveNodesTo
		(
			std::vector<std::shared_ptr<nodeType>>& theNodes
		) const;

		void ExportToPlt(OFstream&) const;
	};
}

#include <GeoMesh_DataI.hxx>

#endif // !_GeoMesh_Data_Header