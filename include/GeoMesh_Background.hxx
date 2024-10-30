#pragma once
#ifndef _GeoMesh_Background_Header
#define _GeoMesh_Background_Header

#include <GeoMesh_Background_Info.hxx>
#include <Entity_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <IFstream.hxx>

#include <memory>
#include <vector>

#ifdef TnbMesh_EXPORT_DEFINE
#define TnbGeoMesh_Background_EXPORT __declspec(dllexport)
#else
#ifdef TnbGeoMesh_Background_EXPORT_DEFINE
#define TnbGeoMesh_Background_EXPORT __declspec(dllexport)
#else
#define TnbGeoMesh_Background_EXPORT __declspec(dllimport)
#endif
#endif

//#include <GeoMesh2d_Data.hxx>

namespace tnbLib
{

	template<class MeshData, class Type>
	class GeoMesh_Background
	{

	public:

		typedef typename MeshData::elementType elementType;
		typedef typename elementType::nodeType::ptType Point;

	private:

		/*Private Data*/

		Entity_Box<Point> theBoundingBox_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar& theBoundingBox_;
		}

	protected:

		// default constructor [12/7/2022 Payvand]

		GeoMesh_Background()
		{}

		// constructors [12/7/2022 Payvand]

	public:

		static TnbGeoMesh_Background_EXPORT const std::string extension;

		// Public functions and operators [12/7/2022 Payvand]

		const auto& BoundingBox() const
		{
			return theBoundingBox_;
		}

		virtual Type InterpolateAt(const Point& theCoord) const = 0;
		virtual Type InterpolateAt(const Point& theCoord, Standard_Boolean& Sense) const = 0;

		virtual void ConnectTopology() = 0;
		virtual void ExportToPlt(OFstream& File) const = 0;
		virtual void ExportToVtk(OFstream& File) const = 0;
		virtual void ExportToVtk(std::ostream& stream) const = 0;

		void SetBoundingBox(const Entity_Box<Point>& theBox)
		{
			theBoundingBox_ = theBox;
		}

		void SetBoundingBox(Entity_Box<Point>&& theBox)
		{
			theBoundingBox_ = std::move(theBox);
		}
	};

	template<class ElementType>
	struct GeoMesh_SingleBackground_Cache
	{
		mutable std::shared_ptr<ElementType> Current;

		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & Current;
		}
	};

	template<class MeshData>
	class GeoMesh_SingleBackground_Base
		: public GeoMesh_SingleBackground_Cache<typename MeshData::elementType>
	{

		typedef typename MeshData::elementType elementType;
		typedef typename elementType::nodeType::ptType Point;

		typedef Entity_Box<Point> box;
		typedef GeoMesh_SingleBackground_Cache<typename MeshData::elementType> base;

		/*Private Data*/

		std::shared_ptr<MeshData> theMesh_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<GeoMesh_SingleBackground_Cache<typename MeshData::elementType>>(*this);
			ar & theMesh_;
		}

	public:

		GeoMesh_SingleBackground_Base()
		{}

		GeoMesh_SingleBackground_Base
		(
			const std::shared_ptr<MeshData>& theMesh
		)
			: theMesh_(theMesh)
		{}

		GeoMesh_SingleBackground_Base
		(
			std::shared_ptr<MeshData>&& theMesh
		)
			: theMesh_(std::move(theMesh))
		{}

		auto IsLoaded() const
		{
			return (Standard_Boolean)theMesh_;
		}

		const auto& Mesh() const
		{
			return theMesh_;
		}

		const std::shared_ptr<elementType>& CurrentElement() const
		{
			return base::Current;
		}

		void LoadData
		(
			const std::shared_ptr<MeshData>& theMesh
		)
		{
			theMesh_ = theMesh;
		}

		void LoadData
		(
			std::shared_ptr<MeshData>&& theMesh
		)
		{
			theMesh_ = std::move(theMesh);
		}

		void SetCurrent
		(
			const std::shared_ptr<elementType>& theElement
		)
		{
			base::Current = theElement;
		}

		void InitiateCurrentElement() const
		{
			if (!theMesh_)
			{
				FatalErrorIn("void InitiateCurrentElement() const")
					<< " Null pointer has been encountered!" << endl
					<< abort(FatalError);
			}
			base::Current = theMesh_->Elements()[0];
		}
	};


	template<class MeshData, class Type>
	class GeoMesh_SingleBackground
		: public GeoMesh_SingleBackground_Base<MeshData>
		, public GeoMesh_Background<MeshData, Type>
	{

	public:

		typedef typename MeshData::elementType elementType;
		typedef typename elementType::nodeType::ptType Point;
		typedef typename elementType::nodeType nodeType;

		typedef GeoMesh_SingleBackground_Base<MeshData> base;
		typedef GeoMesh_Background_SmoothingHvCorrection_Info hvInfo;
		//typedef GeoMesh_Background_SmoothingLaplacianInfo laplacianInfo;

	private:

		/*Private Data*/

		mutable std::vector<Type> theSources_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<GeoMesh_SingleBackground_Base<MeshData>>(*this);
			ar & boost::serialization::base_object<GeoMesh_Background<MeshData, Type>>(*this);
			ar & theSources_;
		}

		void HvCorrection
		(
			const std::vector<std::shared_ptr<nodeType>>& nodes,
			const Standard_Real Factor,
			const Standard_Integer MaxInnerIteration
		);

		/*void LaplacianSmoothing
		(
			const std::vector<std::shared_ptr<nodeType>>& nodes,
			const Standard_Integer NbIterations,
			const Standard_Real Factor
		);*/

	public:



		GeoMesh_SingleBackground()
		{}

		GeoMesh_SingleBackground
		(
			const std::shared_ptr<MeshData>& theMesh,
			const std::vector<Type>& theSources
		)
			: base(theMesh)
			, theSources_(theSources)
		{}

		GeoMesh_SingleBackground
		(
			std::shared_ptr<MeshData>&& theMesh,
			std::vector<Type>&& theSources
		)
			: base(std::move(theMesh))
			, theSources_(std::move(theSources))
		{}

		Type InterpolateAt(const Point& theCoord) const override;
		Type InterpolateAt(const Point& theCoord, Standard_Boolean& Sense) const override;

		void ConnectTopology() override;

		auto& Sources() const
		{
			return theSources_;
		}

		void HvCorrection(const std::shared_ptr<hvInfo>& theInfo);
		//void LaplacianSmoothing(const std::shared_ptr<laplacianInfo>& theInfo);

		// - IO functions and operators

		void ExportToPlt(OFstream & File) const override;
		void ExportToVtk(OFstream& FIle) const override;
		void ExportToVtk(std::ostream& stream) const override;

		void ReadBackMeshFrom(IFstream& File);

		template<class Type, class MeshData>
		friend Istream& operator>>
			(
				Istream& is,
				GeoMesh_SingleBackground& theBack
				);
	};
}

#include <GeoMesh_BackgroundI.hxx>

#endif // !_GeoMesh_Background_Header