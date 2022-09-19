#pragma once
#ifndef _Geo3d_ApprxSurfPatch_Header
#define _Geo3d_ApprxSurfPatch_Header

#include <Mesh_Module.hxx>
#include <GeoMesh2d_DataFwd.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Pnt2d.hxx>
#include <Global_Done.hxx>

// Forward Declarations [9/1/2022 Amir]
class Geom_Surface;

#include <Standard_Handle.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [9/5/2022 Amir]
	class Geo3d_ApprxSurfPatch_FunMode;
	class Geo3d_ApprxSurfPatch_Info;

	class Geo3d_ApprxSurfPatch
		: public Global_Done
	{

	public:

		class Node
		{

			/*Private Data*/

			Pnt2d theCoord_;

		public:

			typedef Pnt2d ptType;

			// default constructor [9/5/2022 Amir]

			Node()
				: theCoord_(Pnt2d::null)
			{}

			// constructors [9/5/2022 Amir]

			Node(const Pnt2d& theCoord)
				: theCoord_(theCoord)
			{}

			Node(Pnt2d&& theCoord)
				: theCoord_(std::move(theCoord))
			{}

			// public functions and operators [9/5/2022 Amir]

			const auto& Coord() const
			{
				return theCoord_;
			}

			void SetCoord(const Pnt2d& theCoord)
			{
				theCoord_ = theCoord;
			}

			void SetCoord(Pnt2d&& theCoord)
			{
				theCoord_ = std::move(theCoord);
			}

			static const Pnt2d& GetCoord(Node* const & theNode)
			{
				return theNode->Coord();
			}
		};

		class QuadTreeObject
		{

			/*Private Data*/

			const Geo3d_ApprxSurfPatch_FunMode& theFunction_;

			const Geom_Surface& theGeometry_;

			Standard_Real theTolerance_;

		public:

			// default constructor [9/1/2022 Amir]

			

			// constructors [9/1/2022 Amir]

			QuadTreeObject
			(
				const Geo3d_ApprxSurfPatch_FunMode& theFun,
				const Geom_Surface& theGeometry,
				const Standard_Real theTolerance
			)
				: theFunction_(theFun)
				, theGeometry_(theGeometry)
				, theTolerance_(theTolerance)
			{}

			// public functions and operators [9/1/2022 Amir]


			auto Tolerance() const
			{
				return theTolerance_;
			}

			const auto& Geometry() const
			{
				return theGeometry_;
			}

			const auto& Function() const
			{
				return theFunction_;
			}

			static TnbMesh_EXPORT Standard_Boolean doSubdivide(const Entity2d_Box&, const QuadTreeObject*);
		};

	private:

		/*Private Data*/

		Handle(Geom_Surface) thePatch_;

		std::shared_ptr<GeoMesh2d_Data> theBack_;
		std::shared_ptr<Geo3d_ApprxSurfPatch_FunMode> theFunction_;

		std::shared_ptr<Entity2d_Box> theDomain_;

		std::shared_ptr<Geo3d_ApprxSurfPatch_Info> theInfo_;


		// results [9/5/2022 Amir]

		std::shared_ptr<std::vector<Pnt2d>> theCoords_;

	public:


		// default constructor [9/1/2022 Amir]

		Geo3d_ApprxSurfPatch()
		{}


		// constructors [9/1/2022 Amir]

		Geo3d_ApprxSurfPatch
		(
			const Handle(Geom_Surface)& thePatch,
			const std::shared_ptr<Entity2d_Box>& theDomain,
			const std::shared_ptr<GeoMesh2d_Data>& theBack,
			const std::shared_ptr<Geo3d_ApprxSurfPatch_FunMode>& theFun,
			const std::shared_ptr<Geo3d_ApprxSurfPatch_Info>& theInfo
		)
			: thePatch_(thePatch)
			, theDomain_(theDomain)
			, theBack_(theBack)
			, theFunction_(theFun)
			, theInfo_(theInfo)
		{}

		Geo3d_ApprxSurfPatch
		(
			Handle(Geom_Surface)&& thePatch,
			std::shared_ptr<Entity2d_Box>&& theDomain,
			std::shared_ptr<GeoMesh2d_Data>&& theBack,
			std::shared_ptr<Geo3d_ApprxSurfPatch_FunMode>&& theFun,
			std::shared_ptr<Geo3d_ApprxSurfPatch_Info>&& theInfo
		)
			: thePatch_(std::move(thePatch))
			, theDomain_(std::move(theDomain))
			, theBack_(std::move(theBack))
			, theFunction_(std::move(theFun))
			, theInfo_(std::move(theInfo))
		{}


		// public functions and operators [9/1/2022 Amir]


		const auto& Patch() const
		{
			return thePatch_;
		}

		const auto& Domain() const
		{
			return theDomain_;
		}

		const auto& Backgound() const
		{
			return theBack_;
		}

		const auto& Function() const
		{
			return theFunction_;
		}

		const auto& AlgInfo() const
		{
			return theInfo_;
		}

		TnbMesh_EXPORT const std::shared_ptr<std::vector<Pnt2d>>& Approximated() const;

		TnbMesh_EXPORT void Perform();

		void SetPatch(const Handle(Geom_Surface)& thePatch)
		{
			thePatch_ = thePatch;
		}

		void SetPatch(Handle(Geom_Surface)&& thePatch)
		{
			thePatch_ = std::move(thePatch);
		}

		void SetDomain(const std::shared_ptr<Entity2d_Box>& theDomain)
		{
			theDomain_ = theDomain;
		}

		void SetDomain(std::shared_ptr<Entity2d_Box>&& theDomain)
		{
			theDomain_ = std::move(theDomain);
		}

		void SetBackgound(const std::shared_ptr<GeoMesh2d_Data>& theBack)
		{
			theBack_ = theBack;
		}

		void SetBackgound(std::shared_ptr<GeoMesh2d_Data>&& theBack)
		{
			theBack_ = std::move(theBack);
		}

		void SetFunction(const std::shared_ptr<Geo3d_ApprxSurfPatch_FunMode>& theFun)
		{
			theFunction_ = theFun;
		}

		void SetFunction(std::shared_ptr<Geo3d_ApprxSurfPatch_FunMode>&& theFun)
		{
			theFunction_ = std::move(theFun);
		}

		void SetInfo(const std::shared_ptr<Geo3d_ApprxSurfPatch_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void SetInfo(std::shared_ptr<Geo3d_ApprxSurfPatch_Info>&& theInfo)
		{
			theInfo_ = std::move(theInfo);
		}
	};
}

#endif // !_Geo3d_ApprxSurfPatch_Header
