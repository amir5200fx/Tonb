#include <GeoIO_Loader_STL.hxx>

#include <Geo_AdTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Pnt3d.hxx>
#define STLLOADER_IMPLEMENTATION
#include "stlloader-master/stlloader.h"

void tnbLib::ioLib::Loader_STL::Perform(const std::string& file_name)
{
    struct Node
    {
        typedef Pnt3d ptType;
        Pnt3d coord;
        Standard_Integer id;
    };
    stlloader::Mesh mesh;
    std::ifstream input(file_name, std::ios::binary);
    if (!input)
    {
        FatalErrorIn(FunctionSIG) << endl
            << " Cannot open file: " << file_name << endl
            << abort(FatalError);
    }
    stlloader::parse_stream(input, mesh);
    Entity3d_Box b;
    {
        std::vector<Pnt3d> coords;
        for (const stlloader::Facet& facet : mesh.facets)
        {
            for (int vi = 0; vi < 3; ++vi)
            {
                Pnt3d pt{ facet.vertices[vi].x, facet.vertices[vi].y, facet.vertices[vi].z };
                coords.emplace_back(pt);
            }
        }
        b = Geo_BoxTools::GetBox(coords, 0);
    }
    Geo_AdTree<std::shared_ptr<Node>> engine;
    engine.SetGeometryRegion(b.Expanded(b.Diameter()*1.e-3));
    engine.SetGeometryCoordFunc([](const std::shared_ptr<Node>& node)->const Pnt3d& {return node->coord; });
    std::vector<connectivity::triple> elements;
    for (const stlloader::Facet& facet : mesh.facets) 
    {
        connectivity::triple t;
        for (int vi = 0; vi < 3; ++vi) 
        {
            Pnt3d pt{ facet.vertices[vi].x, facet.vertices[vi].y, facet.vertices[vi].z };
            std::vector<std::shared_ptr<Node>> items;
            engine.GeometrySearch(1.e-6, pt, items);
            if (items.empty())
            {
                auto node = std::make_shared<Node>();
                node->coord = pt;
                node->id = engine.Size() + 1;
                engine.InsertToGeometry(node);
                t.Value(vi) = node->id;
            }
            else
            {
                auto min_dis = RealLast();
                std::shared_ptr<Node> found;
                for (const auto& x: items)
                {
	                const auto dis = x->coord.Distance(pt);
                    if (dis <= min_dis)
                    {
                        min_dis = dis;
                        found = x;
                    }
                }
                if (gp::Resolution() <= min_dis)
                {
                    auto node = std::make_shared<Node>();
                    node->coord = pt;
                    node->id = engine.Size() + 1;
                    engine.InsertToGeometry(node);
                    t.Value(vi) = node->id;
                }
                else
                {
                    t.Value(vi) = found->id;
                }
            }
        }
        elements.emplace_back(t);
    }
    std::vector<std::shared_ptr<Node>> nodes;
    engine.RetrieveFromGeometryTo(nodes);
    std::sort(nodes.begin(), nodes.end(), [](const std::shared_ptr<Node>& n0, const std::shared_ptr<Node>& n1)
    {
	    return n0->id < n1->id;
    });
    std::vector<Pnt3d> coords;
    coords.reserve(nodes.size());
    std::for_each(nodes.begin(), nodes.end(), [&coords](const std::shared_ptr<Node>& node)
        {
            coords.emplace_back(node->coord);
        });
    theMesh_ = std::make_shared<Entity3d_Triangulation>(std::move(coords), std::move(elements));
    Change_IsDone() = Standard_True;
}
