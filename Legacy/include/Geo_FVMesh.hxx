#pragma once
#ifndef _Geo_FVMesh_Header
#define _Geo_FVMesh_Header

#include <Geo_Module.hxx>
#include <Global_Named.hxx>
#include <Global_Serialization.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <OFstream.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [8/14/2023 aamir]
	class Geo_ElemGeom;

	template<class Point>
	class Geo_FVMesh
		: public Global_Named
	{

	public:

		class Boundary
			: public Global_Named
		{

			/*Private Data*/

			word theType_;
			std::vector<std::shared_ptr<Geo_ElemGeom>> theElements_;

			// Private functions and operators [8/14/2023 aamir]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				Info << "This function is not supposed to be called." << endl;
				NotImplemented;
			}


		public:

			// default constructor [8/14/2023 aamir]

			Boundary()
			{}

			// constructors [8/14/2023 aamir]

			Boundary
			(
				const word& theName, 
				const std::vector<std::shared_ptr<Geo_ElemGeom>>& theElements
			)
				: Global_Named(theName)
				, theElements_(theElements)
			{}

			Boundary
			(
				const word& theName, 
				std::vector<std::shared_ptr<Geo_ElemGeom>>&& theElements
			)
				: Global_Named(theName)
				, theElements_(std::move(theElements))
			{}


			// Public functions and operators [8/14/2023 aamir]

			const auto& BoundaryCondition() const { return theType_; }
			const auto& Elements() const { return theElements_; }
			auto& ElementsRef() { return theElements_; }

			void SetBoundaryCondition(const word& theType) { theType_ = theType; }
			void SetElements(const std::vector<std::shared_ptr<Geo_ElemGeom>>& theElements) { theElements_ = theElements; }
			void SetElements(std::vector<std::shared_ptr<Geo_ElemGeom>>&& theElements) { theElements_ = std::move(theElements); }

		};

		class Group
		{

			/*Private Data*/

			std::vector<Standard_Integer> theElements_;


			// Private functions and operators [8/15/2023 aamir]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& theElements_;
			}

		public:

			// default constructor [8/15/2023 aamir]

			Group()
			{}

			// constructors [8/15/2023 aamir]

			Group(const std::vector<Standard_Integer>& theElements)
				: theElements_(theElements)
			{}

			Group(std::vector<Standard_Integer>&& theElements)
				: theElements_(std::move(theElements))
			{}


			// Public functions and operators [8/15/2023 aamir]

			const auto& Elements() const { return theElements_; }
			auto& ElementsRef() { return theElements_; }

			void SetElements(const std::vector<Standard_Integer>& theElements) { theElements_ = theElements; }
			void SetElements(std::vector<Standard_Integer>&& theElements) { theElements_ = std::move(theElements); }

		};

	private:

		/*Private Data*/

		std::vector<Point> theCoords_;
		std::vector<std::shared_ptr<Geo_ElemGeom>> theElements_;

		std::vector<std::shared_ptr<Boundary>> theBoundaries_;
		std::shared_ptr<std::vector<std::shared_ptr<Group>>> theGroups_;

		// Private functions and operators [8/14/2023 aamir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			Info << "This functions is not supposed to be called." << endl;
			NotImplemented;
		}

	public:

		static TnbGeo_EXPORT const std::string extension;

		// default constructor [8/14/2023 aamir]

		Geo_FVMesh()
		{}

		// constructors [8/14/2023 aamir]

		Geo_FVMesh
		(
			const word& theName, 
			const std::vector<Point>& theCoords, 
			const std::vector<std::shared_ptr<Geo_ElemGeom>>& theElements, 
			const std::vector<std::shared_ptr<Boundary>>& theBoundaries
		)
			: Global_Named(theName)
			, theCoords_(theCoords)
			, theElements_(theElements)
			, theBoundaries_(theBoundaries)
		{}

		Geo_FVMesh
		(
			const word& theName,
			std::vector<Point>&& theCoords,
			std::vector<std::shared_ptr<Geo_ElemGeom>>&& theElements,
			std::vector<std::shared_ptr<Boundary>>&& theBoundaries
		)
			: Global_Named(theName)
			, theCoords_(std::move(theCoords))
			, theElements_(std::move(theElements))
			, theBoundaries_(std::move(theBoundaries))
		{}


		// Public functions and operators [8/14/2023 aamir]

		auto NbPoints() const { return (Standard_Integer)theCoords_.size(); }
		auto NbElements() const { return (Standard_Integer)theElements_.size(); }
		auto NbBoundaries() const { return (Standard_Integer)theBoundaries_.size(); }

		auto HasGroup() const { return (Standard_Boolean)theGroups_; }

		inline Standard_Integer NbGroups() const;

		const auto& Coordinates() const { return theCoords_; }
		const auto& Elements() const { return theElements_; }
		const auto& Boundaries() const { return theBoundaries_; }
		const auto& Groups() const { return theGroups_; }

		void SetCoordinates(const std::vector<Point>& theCoords) { theCoords_ = theCoords; }
		void SetCoordinates(std::vector<Point>&& theCoords) { theCoords_ = std::move(theCoords); }

		void SetElements(const std::vector<std::shared_ptr<Geo_ElemGeom>>& theElements) { theElements_ = theElements; }
		void SetElements(std::vector<std::shared_ptr<Geo_ElemGeom>>&& theElements) { theElements_ = std::move(theElements); }

		void SetBoundaries(const std::vector<std::shared_ptr<Boundary>>& theBoundaries) { theBoundaries_ = theBoundaries; }
		void SetBoundaries(std::vector<std::shared_ptr<Boundary>>&& theBoundaries) { theBoundaries_ = std::move(theBoundaries); }

		void ExportToPlt(OFstream&) const;

	};
}

#include <Geo_FVMeshI.hxx>

#endif // !_Geo_FVMesh_Header
