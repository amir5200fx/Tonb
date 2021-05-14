#pragma once
#ifndef _GModel_Tools_Header
#define _GModel_Tools_Header

#include <Cad_Module.hxx>

#include <memory>
#include <vector>

class TopoDS_Face;
class TopoDS_Edge;
class TopoDS_Shape;

namespace tnbLib
{

	// Forward Declarations
	class GModel_Surface;
	class GModel_Edge;

	class GModel_Tools
	{

	public:

		static TnbCad_EXPORT std::shared_ptr<GModel_Edge>
			GetEdge
			(
				const TopoDS_Edge& theEdge, 
				const TopoDS_Face& theFace
			);

		static TnbCad_EXPORT std::shared_ptr<GModel_Surface>
			GetSurface
			(
				const TopoDS_Face& theFace
			);

		static TnbCad_EXPORT std::vector<std::shared_ptr<GModel_Surface>> 
			GetSurfaces
			(
				const TopoDS_Shape& theShape
			);
	};
}

#endif // !_GModel_Tools_Header
